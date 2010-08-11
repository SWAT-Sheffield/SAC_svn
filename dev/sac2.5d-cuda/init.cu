#include "cudapars.h"
#include "iotypes.h"

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
int encode_i (struct params *dp,int ix, int iy) {

  //int kSizeX=(dp)->ni;
  //int kSizeY=(dp)->nj;
  
  return ( iy * ((dp)->ni) + ix);
}

__device__ __host__
int fencode_i (struct params *dp,int ix, int iy, int field) {

  //int kSizeX=(dp)->ni;
  //int kSizeY=(dp)->nj;
  
  return ( (iy * ((dp)->ni) + ix)+(field*((dp)->ni)*((dp)->nj)));
}

//*d_p,*d_w, *d_wnew, *d_wmod, *d_dwn1,  *d_wd

__global__ void init_parallel(struct params *p, real *w, real *wnew, real *wmod, 
    real *dwn1, real *wd)
{
  // compute the global index in the vector from
  // the number of the current block, blockIdx,
  // the number of threads per block, blockDim,
  // and the number of the current thread within the block, threadIdx
  // int i = blockIdx.x * blockDim.x + threadIdx.x;
  // int j = blockIdx.y * blockDim.y + threadIdx.y;

 int iindex = blockIdx.x * blockDim.x + threadIdx.x;
  int index,k;
int ni=p->ni;
  int nj=p->nj;

// Block index
    int bx = blockIdx.x;
   // int by = blockIdx.y;
    // Thread index
    int tx = threadIdx.x;
   // int ty = threadIdx.y;
    
  real *u,  *v,  *h;

  int seg1,seg2,seg3,seg4;
  int width=10;
  real m2max=0.001;
  real start=((p->ni)-width)/2;
  seg1=((p->ni)/3)-1;
  seg2=((p->ni)/3);
  seg3=(2*(p->ni)/3)-1;
  seg4=(2*(p->ni)/3)-1;
//enum vars rho, mom1, mom2, mom3, energy, b1, b2, b3;


  int i,j;

   
   j=iindex/ni;
   //i=iindex-j*(iindex/ni);
   i=iindex-(j*ni);
  if(i<p->ni && j<p->nj)
	{
		//b[i+j*(p->ni)]=0;

                 //Define b	

 


	//apply this special condition
	//initiate alfven wave propagtion 
	//if no initial config read
	if(p->readini==0)
	{
	    for(int f=0; f<=6; f++)
            { 
		          w[fencode_i(p,i,j,f)]=0;
	    }
            w[fencode_i(p,i,j,rho)]=1.0;
            #ifdef ADIABHYDRO
		    if(i>73 && i<77 && j>73 && j<77 ) 
				w[fencode_i(p,i,j,rho)]=1.3;
            #else

		    w[fencode_i(p,i,j,rho)]=1.0;
		    w[fencode_i(p,i,j,b2)]=1.0;
		    w[fencode_i(p,i,j,energy)]=0.0001;

		    //w[fencode_i(p,i,j,b1)]=15*j;
		    //w[fencode_i(p,i,j,b3)]=150*j;
		    
		   if (i > seg2)
		    if (i < seg3)
		      w[fencode_i(p,i,j,mom2)]=m2max;


		   if (i > seg2)
		    if (i < seg3)
		      w[fencode_i(p,i,j,mom2)]=m2max*(i-seg2)/(seg3-seg2);

		   if (i > seg3)
		    if (i < seg4)
		      w[fencode_i(p,i,j,mom2)]=m2max*(seg4-i)/(seg4-seg3);
           #endif

	}


//	 __syncthreads();

			}	
	 __syncthreads();

  if(i<p->ni && j<p->nj)
	{
        for(int f=rho; f<=b3; f++)
        {               
                  wnew[fencode_i(p,i,j,f)]=w[fencode_i(p,i,j,f)];
                  dwn1[fencode_i(p,i,j,f)]=0;
                  //dwn2[fencode(p,i,j,f)]=0;
                 // dwn3[fencode(p,i,j,f)]=0;
                  //dwn4[fencode(p,i,j,f)]=0;
                 
        }
}

 __syncthreads();
        if(i<p->ni && j<p->nj)
               for(int f=current1; f<=divb; f++)
                    wd[fencode_i(p,i,j,f)]=0.0;

 __syncthreads(); 
}

/////////////////////////////////////
// error checking routine
/////////////////////////////////////
void checkErrors_i(char *label)
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



int cuinit(struct params **p, real **w, real **wnew, struct state **state, struct params **d_p, real **d_w, real **d_wnew, real **d_wmod, real **d_dwn1, real **d_wd, struct state **d_state)
{



/////////////////////////////////////
  // (1) initialisations:
  //     - perform basic sanity checks
  //     - set device
  /////////////////////////////////////
  int deviceCount;
  cudaGetDeviceCount(&deviceCount);
   
 // if (deviceCount == 0)
 // {
 //   fprintf(stderr, "Sorry, no CUDA device fount");
 //   return 1;
//  }
  if (selectedDevice >= deviceCount)
  {
    fprintf(stderr, "Choose device ID between 0 and %d\n", deviceCount-1);
    return 1;
  }
  //cudaSetDevice(selectedDevice);
  printf("device count %d selected %d\n", deviceCount,selectedDevice);
  checkErrors_i("initialisations");
  
	// Build empty u, v, b matrices

  printf("in cuinit\n");
 // real *adb;
  real *adw, *adwnew;
  struct params *adp;
  struct state *ads;


  cudaMalloc((void**)d_wmod, 8*((*p)->ni)* ((*p)->nj)*sizeof(real));
  cudaMalloc((void**)d_dwn1, 8*((*p)->ni)* ((*p)->nj)*sizeof(real));
  cudaMalloc((void**)d_wd, 8*((*p)->ni)* ((*p)->nj)*sizeof(real));

  cudaMalloc((void**)&adw, 8*((*p)->ni)* ((*p)->nj)*sizeof(real));
  cudaMalloc((void**)&adwnew, 8*((*p)->ni)* ((*p)->nj)*sizeof(real));
  
  cudaMalloc((void**)&adp, sizeof(struct params));
  cudaMalloc((void**)&ads, sizeof(struct state));
  checkErrors_i("memory allocation");

printf("ni is %d\n",(*p)->nj);

   // *d_b=adb;
    *d_p=adp;
    *d_w=adw;
    *d_wnew=adwnew;
    *d_state=ads;


    cudaMemcpy(*d_w, *w, 8*((*p)->ni)* ((*p)->nj)*sizeof(real), cudaMemcpyHostToDevice);
   // cudaMemcpy(*d_wnew, *wnew, 8*((*p)->ni)* ((*p)->nj)*sizeof(real), cudaMemcpyHostToDevice);
    
    cudaMemcpy(*d_p, *p, sizeof(struct params), cudaMemcpyHostToDevice);
    cudaMemcpy(*d_state, *state, sizeof(struct state), cudaMemcpyHostToDevice);
    
    dim3 dimBlock(16, 1);
    //dim3 dimGrid(((*p)->ni)/dimBlock.x,((*p)->nj)/dimBlock.y);
    dim3 dimGrid(((*p)->ni)/dimBlock.x,((*p)->nj)/dimBlock.y);
   int numBlocks = (((*p)->ni)*((*p)->nj)+numThreadsPerBlock-1) / numThreadsPerBlock;
   

    printf("calling initialiser\n");
     //init_parallel(struct params *p, real *b, real *u, real *v, real *h)
    // init_parallel<<<dimGrid,dimBlock>>>(*d_p,*d_b,*d_u,*d_v,*d_h);
    // init_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_w, *d_wnew, *d_b);
     init_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_w, *d_wnew, *d_wmod, *d_dwn1,  *d_wd);
     cudaThreadSynchronize();
	    printf("called initialiser\n");
	cudaMemcpy(*w, *d_w, 8*((*p)->ni)* ((*p)->nj)*sizeof(real), cudaMemcpyDeviceToHost);

	cudaMemcpy(*state, *d_state, sizeof(struct state), cudaMemcpyDeviceToHost);
        cudaMemcpy(*p, *d_p, sizeof(struct params), cudaMemcpyDeviceToHost);
	cudaMemcpy(*wnew, *d_wnew, 8*((*p)->ni)* ((*p)->nj)*sizeof(real), cudaMemcpyDeviceToHost);
	//cudaMemcpy(*b, *d_b, (((*p)->ni)* ((*p)->nj))*sizeof(real), cudaMemcpyDeviceToHost);

         printf("mod times step %f %f\n",(*p)->dt, ((*wnew)[10+16*((*p)->ni)+((*p)->ni)*((*p)->nj)*b1]));



  return 0;



}


