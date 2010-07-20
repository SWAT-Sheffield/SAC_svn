#include "cudapars.h"
#include "paramssteeringtest1.h"

/////////////////////////////////////
// standard imports
/////////////////////////////////////
#include <stdio.h>
#include <math.h>
#include "step.h"

/////////////////////////////////////
// kernel function (CUDA device)
/////////////////////////////////////
__device__ __host__
int encode_u (struct params *dp,int ix, int iy) {

  //int kSizeX=(dp)->ni;
  //int kSizeY=(dp)->nj;
  
  return ( iy * ((dp)->ni) + ix);
}

__device__ __host__
int fencode_u (struct params *dp,int ix, int iy, int field) {

  //int kSizeX=(dp)->ni;
  //int kSizeY=(dp)->nj;
  
  return ( (iy * ((dp)->ni) + ix)+(field*((dp)->ni)*((dp)->nj)));
}

__device__ __host__
int updatestate (struct params *p, struct state *s, float *w ,int i, int j, int field) {

  int status=0;
                      // atomicExch(&(p->cmax),(wd[fencode_pre(p,i,j,soundspeed)]));
                    switch(field)
                    {
                      case rho:
                    	s->rho=s->rho+(w[fencode_u(p,i,j,field)]);
		      break;
                      case mom1:
                    	s->m1=s->m1+(w[fencode_u(p,i,j,field)]);
		      break;
                      case mom2:
                    	s->m2=s->m2+(w[fencode_u(p,i,j,field)]);
		      break;
                      case mom3:
                    	s->m3=s->m3+(w[fencode_u(p,i,j,field)]);
		      break;
                      case energy:
                    	s->e=s->e+(w[fencode_u(p,i,j,field)]);
		      break;
                      case b1:
                    	s->b1=s->b1+(w[fencode_u(p,i,j,field)]);
		      break;
                      case b2:
                    	s->b2=s->b2+(w[fencode_u(p,i,j,field)]);
		      break;
                      case b3:
                    	s->b3=s->b3+(w[fencode_u(p,i,j,field)]);
		      break;
                    };
  return status;
}



__global__ void update_parallel(struct params *p, struct state *s, float *b, float *w, float *wnew)
{
  // compute the global index in the vector from
  // the number of the current block, blockIdx,
  // the number of threads per block, blockDim,
  // and the number of the current thread within the block, threadIdx
   int iindex = blockIdx.x * blockDim.x + threadIdx.x;
  int i,j;
  int index,k;
  __shared__ int ntot;

  int ni=p->ni;
  int nj=p->nj;
  float dt=p->dt;
  float dy=p->dy;
  float dx=p->dx;
  float g=p->g;
  float *u,  *v,  *h;
//enum vars rho, mom1, mom2, mom3, energy, b1, b2, b3;
  h=w+(p->ni)*(p->nj)*rho;
  u=w+(p->ni)*(p->nj)*mom1;
  v=w+(p->ni)*(p->nj)*mom2;

  float *un,  *vn,  *hn;
//enum vars rho, mom1, mom2, mom3, energy, b1, b2, b3;
  hn=wnew+(p->ni)*(p->nj)*rho;
  un=wnew+(p->ni)*(p->nj)*mom1;
  vn=wnew+(p->ni)*(p->nj)*mom2;
     j=iindex/ni;
   //i=iindex-j*(iindex/ni);
   i=iindex-(j*ni);
  //if(i>2 && j >2 && i<((p->ni)-3) && j<((p->nj)-3))

if (threadIdx.x == 0) 
{
 ntot=(p->ni)*(p->nj);
 for(int f=rho; f<=b3; f++) 
 {
                    switch(f)
                    {
                      case rho:
                    	s->rho=0;
		      break;
                      case mom1:
                    	s->m1=0;
		      break;
                      case mom2:
                    	s->m2=0;
		      break;
                      case mom3:
                    	s->m3=0;
		      break;
                      case energy:
                    	s->e=0;
		      break;
                      case b1:
                    	s->b1=0;
		      break;
                      case b2:
                    	s->b2=0;
		      break;
                      case b3:
                    	s->b3=0;
		      break;
                    };

  }              
                 
}
__syncthreads();
  if(i<p->ni && j<p->nj)
	{
             for(int f=rho; f<=b3; f++)
             {               
                  w[fencode_u(p,i,j,f)]=wnew[fencode_u(p,i,j,f)];
                  updatestate (p, s, w ,i, j, f);
              }
            // u[i+j*ni]=un[i+j*ni];
           // v[i+j*ni]=vn[i+j*ni];
	   // h[i+j*ni]=hn[i+j*ni];
	}
 __syncthreads();

if (threadIdx.x == 0) 
{
 for(int f=rho; f<=b3; f++) 
 {
                    switch(f)
                    {
                      case rho:
                    	s->rho=(s->rho)/ntot;
		      break;
                      case mom1:
                    	s->m1=(s->m1)/ntot;
		      break;
                      case mom2:
                    	s->m2=(s->m2)/ntot;
		      break;
                      case mom3:
                    	s->m3=(s->m3)/ntot;
		      break;
                      case energy:
                    	s->e=(s->e)/ntot;
		      break;
                      case b1:
                    	s->b1=(s->b1)/ntot;
		      break;
                      case b2:
                    	s->b2=(s->b2)/ntot;
		      break;
                      case b3:
                    	s->b3=(s->b3)/ntot;
		      break;
                    };

  }              
                 
}
__syncthreads();
  
}


/////////////////////////////////////
// error checking routine
/////////////////////////////////////
void checkErrors_u(char *label)
{
  // we need to synchronise first to catch errors due to
  // asynchroneous operations that would otherwise
  // potentially go unnoticed

  cudaError_t err;

  err = cudaThreadSynchronize();
  if (err != cudaSuccess)
  {
    char *e = (char*) cudaGetErrorString(err);
    fprintf(stderr, "CUDA Error: %s (at %s)", e, label);
  }

  err = cudaGetLastError();
  if (err != cudaSuccess)
  {
    char *e = (char*) cudaGetErrorString(err);
    fprintf(stderr, "CUDA Error: %s (at %s)", e, label);
  }
}


int cuupdate(struct params **p, float **w, float **wnew, float **b, struct state **state,struct params **d_p, float **d_w, float **d_wnew, float **d_b, float **d_wmod, float **d_dwn1, float **d_wd, struct state **d_state)
{


//printf("calling propagate solution\n");

    //dim3 dimBlock(blocksize, blocksize);
    //dim3 dimGrid(((*p)->ni)/dimBlock.x,((*p)->nj)/dimBlock.y);
 dim3 dimBlock(dimblock, 1);
    //dim3 dimGrid(((*p)->ni)/dimBlock.x,((*p)->nj)/dimBlock.y);
    dim3 dimGrid(((*p)->ni)/dimBlock.x,((*p)->nj)/dimBlock.y);
   int numBlocks = (((*p)->ni)*((*p)->nj)+numThreadsPerBlock-1) / numThreadsPerBlock;

//__global__ void prop_parallel(struct params *p, float *b, float *w, float *wnew, float *wmod, 
  //  float *dwn1, float *dwn2, float *dwn3, float *dwn4, float *wd)
     //init_parallel(struct params *p, float *b, float *u, float *v, float *h)
    // prop_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_b,*d_w,*d_wnew, *d_wmod, *d_dwn1,  *d_wd);
     //prop_parallel<<<dimGrid,dimBlock>>>(*d_p,*d_b,*d_u,*d_v,*d_h);
	    //printf("called prop\n"); 
     //cudaThreadSynchronize();
     //boundary_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_b,*d_w,*d_wnew);
	    //printf("called boundary\n");  
     //cudaThreadSynchronize();
     update_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_state, *d_b,*d_w,*d_wnew);
	    //printf("called update\n"); 
    cudaThreadSynchronize();
    cudaMemcpy(*w, *d_w, 8*((*p)->ni)* ((*p)->nj)*sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(*state, *d_state, sizeof(struct state), cudaMemcpyDeviceToHost);

//cudaMemcpy(*wnew, *d_wnew, 8*((*p)->ni)* ((*p)->nj)*sizeof(float), cudaMemcpyDeviceToHost);
//cudaMemcpy(*b, *d_b, (((*p)->ni)* ((*p)->nj))*sizeof(float), cudaMemcpyDeviceToHost);

  //checkErrors("copy data from device");


 


}


int cufinish(struct params **p, float **w, float **wnew, float **b, struct params **d_p, float **d_w, float **d_wnew, float **d_b, float **d_wmod, float **d_dwn1, float **d_wd)
{
  

 cudaMemcpy(*w, *d_w, 8*((*p)->ni)* ((*p)->nj)*sizeof(float), cudaMemcpyDeviceToHost);
//cudaMemcpy(*wnew, *d_wnew, 8*((*p)->ni)* ((*p)->nj)*sizeof(float), cudaMemcpyDeviceToHost);
//cudaMemcpy(*b, *d_b, (((*p)->ni)* ((*p)->nj))*sizeof(float), cudaMemcpyDeviceToHost);

  checkErrors_u("copy data from device");


  cudaFree(*d_p);
//  cudaFree(*d_state);

  cudaFree(*d_w);
  cudaFree(*d_wnew);
  cudaFree(*d_b);

  cudaFree(*d_wmod);
  cudaFree(*d_dwn1);
  cudaFree(*d_wd);



}
