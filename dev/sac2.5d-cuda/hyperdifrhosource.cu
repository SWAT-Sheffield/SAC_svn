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
int encode_hdr (struct params *dp,int ix, int iy) {

  //int kSizeX=(dp)->n[0];
  //int kSizeY=(dp)->n[1];
  
  return ( iy * ((dp)->n[0]) + ix);
}

__device__ __host__
int fencode_hdr (struct params *dp,int ix, int iy, int field) {

  //int kSizeX=(dp)->n[0];
  //int kSizeY=(dp)->n[1];
  
  return ( (iy * ((dp)->n[0]) + ix)+(field*((dp)->n[0])*((dp)->n[1])));
}

__device__ __host__
real evalgrad_hdr(real fi, real fim1, real fip2, real fim2,struct params *p,int dir)
{
 //real valgrad_hdr;

 if(dir == 0)
 {
     //valgrad=(2.0/(3.0*(p->dx[0])))*(fi-fim1)-(1.0/(12.0*(p->dx[0])))*(fip2-fim2);
   //return((1.0/(2.0*(p->dx[0])))*(fi-fim1));
   return(p->sodifon?((1.0/(2.0*(p->dx[0])))*(fi-fim1)):((1.0/(12.0*(p->dx[0])))*((NVAR*fi-NVAR*fim1+fim2-fip2))));
 }
 else if(dir == 1)
 {
    // valgrad=(2.0/(3.0*(p->dx[1])))*(fi-fim1)-(1.0/(12.0*(p->dx[1])))*(fip2-fim2);
     // return((2.0/(1.0*(p->dx[1])))*(fi-fim1));
   return(p->sodifon?((1.0/(2.0*(p->dx[1])))*(fi-fim1)):((1.0/(12.0*(p->dx[1])))*((NVAR*fi-NVAR*fim1+fim2-fip2))));
 }

 return -1;
}

__device__ __host__
real evalgrad1_hdr(real fi, real fim1, struct params *p,int dir)
{
 //real valgrad_hdr;

 if(dir == 0)
 {

   return(((1.0/(2*(p->dx[0])))*(fi-fim1)));
 }
 else if(dir == 1)
 {

   return(((1.0/(2*(p->dx[1])))*(fi-fim1)));
 }

 return -1;
}
__device__ __host__
real grad1l_hdr(real *wmod,struct params *p,int i,int j,int field,int dir)
{
  if(dir == 0)
 {
    return(  ( wmod[fencode_hdr(p,i,j,field)]-wmod[fencode_hdr(p,i-1,j,field)]) /((p->dx[0]))    );
 }
 else if(dir == 1)
 {
    return(  ( wmod[fencode_hdr(p,i,j,field)]-wmod[fencode_hdr(p,i,j-1,field)])/((p->dx[1]))    );
  }
 return 0;

}

__device__ __host__
real grad1r_hdr(real *wmod,struct params *p,int i,int j,int field,int dir)
{
  if(dir == 0)
 {
    return(  ( wmod[fencode_hdr(p,i+1,j,field)]-wmod[fencode_hdr(p,i,j,field)]) /((p->dx[0]))    );
 }
 else if(dir == 1)
 {
    return(  ( wmod[fencode_hdr(p,i,j+1,field)]-wmod[fencode_hdr(p,i,j,field)])/((p->dx[1]))    );
  }
 return 0;

}



__device__ __host__
real grad1_hdr(real *wmod,struct params *p,int i,int j,int field,int dir)
{
 //real valgrad_hdr;

  if(dir == 0)
 {

 return(  (wmod[fencode_hdr(p,i+1,j,field)]-wmod[fencode_hdr(p,i-1,j,field)])/(2.0*(p->dx[0]))    );
 }
 else if(dir == 1)
 {

 return(  (wmod[fencode_hdr(p,i,j+1,field)]-wmod[fencode_hdr(p,i,j-1,field)])/(2.0*(p->dx[1]))    );
  }
 return 0;
}

__device__ __host__
real grad2_hdr(real *wmod,struct params *p,int i,int j,int field,int dir)
{
 //real valgrad_hdr;

  if(dir == 0)
 {
    // valgrad=(2.0/(3.0*(p->dx[0])))*(wmod[fencode(p,i,j,field)]-wmod[fencode(p,i-1,j,field)])-(1.0/(12.0*(p->dx[0])))*(wmod[fencode(p,i+2,j,field)]-wmod[fencode(p,i-2,j,field)]);
//return((1.0/(2.0*(p->dx[0])))*(wmod[fencode_hdr(p,i+1,j,field)]-wmod[fencode_hdr(p,i-1,j,field)]));
 return(  ( (p->sodifon)?((16*wmod[fencode_hdr(p,i+1,j,field)]+16*wmod[fencode_hdr(p,i-1,j,field)]-wmod[fencode_hdr(p,i-2,j,field)]-wmod[fencode_hdr(p,i+2,j,field)]-30*wmod[fencode_hdr(p,i,j,field)])/6.0):2.0*(wmod[fencode_hdr(p,i+1,j,field)]-2*wmod[fencode_hdr(p,i,j,field)]-wmod[fencode_hdr(p,i-1,j,field)]))/(2.0*(p->dx[0])*(p->dx[0]))    );
 }
 else if(dir == 1)
 {
    // valgrad=(2.0/(3.0*(p->dx[1])))*(wmod[fencode(p,i,j,field)]-wmod[fencode(p,i,j-1,field)])-(1.0/(12.0*(p->dx[1])))*(wmod[fencode(p,i,j+2,field)]-wmod[fencode(p,i,j-2,field)]);
// return((1.0/(2.0*(p->dx[1])))*(wmod[fencode_hdr(p,i,j+1,field)]-wmod[fencode_hdr(p,i,j-1,field)]));
 return(  ( (p->sodifon)?((16*wmod[fencode_hdr(p,i,j+1,field)]+16*wmod[fencode_hdr(p,i,j,field)]-wmod[fencode_hdr(p,i,j-2,field)]-wmod[fencode_hdr(p,i,j+2,field)]-30*wmod[fencode_hdr(p,i,j,field)])/6.0):2.0*(wmod[fencode_hdr(p,i,j+1,field)]-2.0*wmod[fencode_hdr(p,i,j+1,field)]-wmod[fencode_hdr(p,i,j-1,field)]))/(2.0*(p->dx[1])*(p->dx[1]))    );
  }
 return 0;
}

__device__ __host__
real grad_hdr(real *wmod,struct params *p,int i,int j,int field,int dir)
{
 //real valgrad_hdr;

  if(dir == 0)
 {
    // valgrad=(2.0/(3.0*(p->dx[0])))*(wmod[fencode(p,i,j,field)]-wmod[fencode(p,i-1,j,field)])-(1.0/(12.0*(p->dx[0])))*(wmod[fencode(p,i+2,j,field)]-wmod[fencode(p,i-2,j,field)]);
//return((1.0/(2.0*(p->dx[0])))*(wmod[fencode_hdr(p,i+1,j,field)]-wmod[fencode_hdr(p,i-1,j,field)]));
 return(  ( (p->sodifon)?((NVAR*wmod[fencode_hdr(p,i+1,j,field)]-NVAR*wmod[fencode_hdr(p,i-1,j,field)]+wmod[fencode_hdr(p,i-2,j,field)]-wmod[fencode_hdr(p,i+2,j,field)])/6.0):wmod[fencode_hdr(p,i+1,j,field)]-wmod[fencode_hdr(p,i-1,j,field)])/(2.0*(p->dx[0]))    );
 }
 else if(dir == 1)
 {
    // valgrad=(2.0/(3.0*(p->dx[1])))*(wmod[fencode(p,i,j,field)]-wmod[fencode(p,i,j-1,field)])-(1.0/(12.0*(p->dx[1])))*(wmod[fencode(p,i,j+2,field)]-wmod[fencode(p,i,j-2,field)]);
// return((1.0/(2.0*(p->dx[1])))*(wmod[fencode_hdr(p,i,j+1,field)]-wmod[fencode_hdr(p,i,j-1,field)]));
 return(  ( (p->sodifon)?((NVAR*wmod[fencode_hdr(p,i,j+1,field)]-NVAR*wmod[fencode_hdr(p,i,j-1,field)]+wmod[fencode_hdr(p,i,j-2,field)]-wmod[fencode_hdr(p,i,j+2,field)])/6.0):wmod[fencode_hdr(p,i,j+1,field)]-wmod[fencode_hdr(p,i,j-1,field)])/(2.0*(p->dx[1]))    );
  }
 return 0;
}














__global__ void hyperdifrhosource_parallel(struct params *p, real *w, real *wnew, real *wmod, 
    real *dwn1, real *wd, int order, real *wtemp, int field, int dim)
{
  // compute the global index in the vector from
  // the number of the current block, blockIdx,
  // the number of threads per block, blockDim,
  // and the number of the current thread within the block, threadIdx
  //int i = blockIdx.x * blockDim.x + threadIdx.x;
  //int j = blockIdx.y * blockDim.y + threadIdx.y;

  int iindex = blockIdx.x * blockDim.x + threadIdx.x;
  int i,j;
  int ii,ii1,ii0;
  real fip,fim1,tmp2,tmpc;
  int index,k;
  int ni=p->n[0];
  int nj=p->n[1];
  real dt=p->dt;
  real dy=p->dx[1];
  real dx=p->dx[0];
  //real g=p->g;
 //  dt=1.0;
//dt=0.05;
//enum vars rho, mom1, mom2, mom3, energy, b1, b2, b3;


  

   j=iindex/ni;
   //i=iindex-j*(iindex/ni);
   i=iindex-(j*ni);

  //init rhol and rhor
  if(i<((p->n[0])) && j<((p->n[1])))
    for(int f=tmp1; f<=tmprhor; f++)	
        wtemp[fencode_hdr(p,i,j,f)]=0.0;

 __syncthreads();

  

  if(i>1 && j >1 && i<((p->n[0])-2) && j<((p->n[1])-2))
  {
     wtemp[fencode_hdr(p,i,j,tmp1)]=grad1l_hdr(wmod,p,i,j,rho,dim);
     wtemp[fencode_hdr(p,i,j,tmp2)]=grad1r_hdr(wmod,p,i,j,rho,dim);
     
dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdr(p,i,j,field)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdr(p,i,j,field)]+( wtemp[fencode_hdr(p,i,j,hdnur)] * wtemp[fencode_hdr(p,i,j,tmp2)] - wtemp[fencode_hdr(p,i,j,hdnul)] *wtemp[fencode_hdr(p,i,j,tmp1)]             )/(((p->dx[0])*(dim==0))+(p->dx[1])*(dim==1));
  }

__syncthreads();

 
}


/////////////////////////////////////
// error checking routine
/////////////////////////////////////
void checkErrors_hdr(char *label)
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





int cuhyperdifrhosource(struct params **p, real **w, real **wnew, struct params **d_p, real **d_w, real **d_wnew,  real **d_wmod, real **d_dwn1, real **d_wd, int order, real **d_wtemp, int field, int dim)
{


//printf("calling propagate solution\n");

    //dim3 dimBlock(blocksize, blocksize);
    //dim3 dimGrid(((*p)->n[0])/dimBlock.x,((*p)->n[1])/dimBlock.y);
 dim3 dimBlock(dimblock, 1);
    //dim3 dimGrid(((*p)->n[0])/dimBlock.x,((*p)->n[1])/dimBlock.y);
    dim3 dimGrid(((*p)->n[0])/dimBlock.x,((*p)->n[1])/dimBlock.y);
   int numBlocks = (((*p)->n[0])*((*p)->n[1])+numThreadsPerBlock-1) / numThreadsPerBlock;

//__global__ void prop_parallel(struct params *p, real *b, real *w, real *wnew, real *wmod, 
  //  real *dwn1, real *dwn2, real *dwn3, real *dwn4, real *wd)
     //init_parallel(struct params *p, real *b, real *u, real *v, real *h)
     hyperdifrhosource_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_w,*d_wnew, *d_wmod, *d_dwn1,  *d_wd, order,*d_wtemp, field, dim);
     //prop_parallel<<<dimGrid,dimBlock>>>(*d_p,*d_b,*d_u,*d_v,*d_h);
	    //printf("called prop\n"); 
     cudaThreadSynchronize();
     //boundary_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_b,*d_w,*d_wnew);
	    //printf("called boundary\n");  
     //cudaThreadSynchronize();
     //update_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_b,*d_w,*d_wnew);
	    //printf("called update\n"); 
   // cudaThreadSynchronize();
// cudaMemcpy(*w, *d_w, NVAR*((*p)->n[0])* ((*p)->n[1])*sizeof(real), cudaMemcpyDeviceToHost);
//cudaMemcpy(*wnew, *d_wnew, NVAR*((*p)->n[0])* ((*p)->n[1])*sizeof(real), cudaMemcpyDeviceToHost);
//cudaMemcpy(*b, *d_b, (((*p)->n[0])* ((*p)->n[1]))*sizeof(real), cudaMemcpyDeviceToHost);

  //checkErrors("copy data from device");


 


}






