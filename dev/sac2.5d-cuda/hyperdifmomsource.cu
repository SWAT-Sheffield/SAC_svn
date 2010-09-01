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
int encode_hdm (struct params *dp,int ix, int iy) {

  //int kSizeX=(dp)->n[0];
  //int kSizeY=(dp)->n[1];
  
  return ( iy * ((dp)->n[0]) + ix);
}

__device__ __host__
int fencode_hdm (struct params *dp,int ix, int iy, int field) {

  //int kSizeX=(dp)->n[0];
  //int kSizeY=(dp)->n[1];
  
  return ( (iy * ((dp)->n[0]) + ix)+(field*((dp)->n[0])*((dp)->n[1])));
}

__device__ __host__
real evalgrad_hdm(real fi, real fim1, real fip2, real fim2,struct params *p,int dir)
{
 //real valgrad_hdm;

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
real evalgrad1_hdm(real fi, real fim1, struct params *p,int dir)
{
 //real valgrad_hdm;

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
real grad1l_hdm(real *wmod,struct params *p,int i,int j,int field,int dir)
{
  if(dir == 0)
 {
    return(  ( wmod[fencode_hdm(p,i,j,field)]-wmod[fencode_hdm(p,i-1,j,field)]) /((p->dx[0]))    );
 }
 else if(dir == 1)
 {
    return(  ( wmod[fencode_hdm(p,i,j,field)]-wmod[fencode_hdm(p,i,j-1,field)])/((p->dx[1]))    );
  }
 return 0;

}

__device__ __host__
real grad1r_hdm(real *wmod,struct params *p,int i,int j,int field,int dir)
{
  if(dir == 0)
 {
    return(  ( wmod[fencode_hdm(p,i+1,j,field)]-wmod[fencode_hdm(p,i,j,field)]) /((p->dx[0]))    );
 }
 else if(dir == 1)
 {
    return(  ( wmod[fencode_hdm(p,i,j+1,field)]-wmod[fencode_hdm(p,i,j,field)])/((p->dx[1]))    );
  }
 return 0;

}



__device__ __host__
real grad1_hdm(real *wmod,struct params *p,int i,int j,int field,int dir)
{
 //real valgrad_hdm;

  if(dir == 0)
 {

 return(  (wmod[fencode_hdm(p,i+1,j,field)]-wmod[fencode_hdm(p,i-1,j,field)])/(2.0*(p->dx[0]))    );
 }
 else if(dir == 1)
 {

 return(  (wmod[fencode_hdm(p,i,j+1,field)]-wmod[fencode_hdm(p,i,j-1,field)])/(2.0*(p->dx[1]))    );
  }
 return 0;
}

__device__ __host__
real grad2_hdm(real *wmod,struct params *p,int i,int j,int field,int dir)
{
 //real valgrad_hdm;

  if(dir == 0)
 {
    // valgrad=(2.0/(3.0*(p->dx[0])))*(wmod[fencode(p,i,j,field)]-wmod[fencode(p,i-1,j,field)])-(1.0/(12.0*(p->dx[0])))*(wmod[fencode(p,i+2,j,field)]-wmod[fencode(p,i-2,j,field)]);
//return((1.0/(2.0*(p->dx[0])))*(wmod[fencode_hdm(p,i+1,j,field)]-wmod[fencode_hdm(p,i-1,j,field)]));
 return(  ( (p->sodifon)?((16*wmod[fencode_hdm(p,i+1,j,field)]+16*wmod[fencode_hdm(p,i-1,j,field)]-wmod[fencode_hdm(p,i-2,j,field)]-wmod[fencode_hdm(p,i+2,j,field)]-30*wmod[fencode_hdm(p,i,j,field)])/6.0):2.0*(wmod[fencode_hdm(p,i+1,j,field)]-2*wmod[fencode_hdm(p,i,j,field)]-wmod[fencode_hdm(p,i-1,j,field)]))/(2.0*(p->dx[0])*(p->dx[0]))    );
 }
 else if(dir == 1)
 {
    // valgrad=(2.0/(3.0*(p->dx[1])))*(wmod[fencode(p,i,j,field)]-wmod[fencode(p,i,j-1,field)])-(1.0/(12.0*(p->dx[1])))*(wmod[fencode(p,i,j+2,field)]-wmod[fencode(p,i,j-2,field)]);
// return((1.0/(2.0*(p->dx[1])))*(wmod[fencode_hdm(p,i,j+1,field)]-wmod[fencode_hdm(p,i,j-1,field)]));
 return(  ( (p->sodifon)?((16*wmod[fencode_hdm(p,i,j+1,field)]+16*wmod[fencode_hdm(p,i,j,field)]-wmod[fencode_hdm(p,i,j-2,field)]-wmod[fencode_hdm(p,i,j+2,field)]-30*wmod[fencode_hdm(p,i,j,field)])/6.0):2.0*(wmod[fencode_hdm(p,i,j+1,field)]-2.0*wmod[fencode_hdm(p,i,j+1,field)]-wmod[fencode_hdm(p,i,j-1,field)]))/(2.0*(p->dx[1])*(p->dx[1]))    );
  }
 return 0;
}

__device__ __host__
real grad_hdm(real *wmod,struct params *p,int i,int j,int field,int dir)
{
 //real valgrad_hdm;

  if(dir == 0)
 {
    // valgrad=(2.0/(3.0*(p->dx[0])))*(wmod[fencode(p,i,j,field)]-wmod[fencode(p,i-1,j,field)])-(1.0/(12.0*(p->dx[0])))*(wmod[fencode(p,i+2,j,field)]-wmod[fencode(p,i-2,j,field)]);
//return((1.0/(2.0*(p->dx[0])))*(wmod[fencode_hdm(p,i+1,j,field)]-wmod[fencode_hdm(p,i-1,j,field)]));
 return(  ( (p->sodifon)?((NVAR*wmod[fencode_hdm(p,i+1,j,field)]-NVAR*wmod[fencode_hdm(p,i-1,j,field)]+wmod[fencode_hdm(p,i-2,j,field)]-wmod[fencode_hdm(p,i+2,j,field)])/6.0):wmod[fencode_hdm(p,i+1,j,field)]-wmod[fencode_hdm(p,i-1,j,field)])/(2.0*(p->dx[0]))    );
 }
 else if(dir == 1)
 {
    // valgrad=(2.0/(3.0*(p->dx[1])))*(wmod[fencode(p,i,j,field)]-wmod[fencode(p,i,j-1,field)])-(1.0/(12.0*(p->dx[1])))*(wmod[fencode(p,i,j+2,field)]-wmod[fencode(p,i,j-2,field)]);
// return((1.0/(2.0*(p->dx[1])))*(wmod[fencode_hdm(p,i,j+1,field)]-wmod[fencode_hdm(p,i,j-1,field)]));
 return(  ( (p->sodifon)?((NVAR*wmod[fencode_hdm(p,i,j+1,field)]-NVAR*wmod[fencode_hdm(p,i,j-1,field)]+wmod[fencode_hdm(p,i,j-2,field)]-wmod[fencode_hdm(p,i,j+2,field)])/6.0):wmod[fencode_hdm(p,i,j+1,field)]-wmod[fencode_hdm(p,i,j-1,field)])/(2.0*(p->dx[1]))    );
  }
 return 0;
}














__global__ void hyperdifmomsource_parallel(struct params *p, real *w, real *wnew, real *wmod, 
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
        wtemp[fencode_hdm(p,i,j,f)]=0.0;

 __syncthreads();

  if(i>1 && j >1 && i<((p->n[0])-2) && j<((p->n[1])-2))
  {
       wtemp[fencode_hdm(p,i,j,tmprhor)]=(wmod[fencode_hdm(p,i,j,rho)]+wmod[fencode_hdm(p,i+(field==0),j+(field==1),rho)])/2;
       wtemp[fencode_hdm(p,i,j,tmprhol)]=(wmod[fencode_hdm(p,i,j,rho)]+wmod[fencode_hdm(p,i-(field==0),j+(field==1),rho)])/2;

   }
__syncthreads();


  if(i>1 && j >1 && i<((p->n[0])-2) && j<((p->n[1])-2))
  {
     wtemp[fencode_hdm(p,i,j,tmp1)]=wmod[fencode_hdm(p,i,j,mom1+field)]/wmod[fencode_hdm(p,i,j,rho)];
     wtemp[fencode_hdm(p,i,j,tmp2)]=grad1_hdm(wtemp,p,i,j,tmp1,0);
     wtemp[fencode_hdm(p,i,j,tmp3)]=grad1_hdm(wtemp,p,i,j,tmp1,1);
  }

__syncthreads();



  if(i>1 && j >1 && i<((p->n[0])-2) && j<((p->n[1])-2))
	{		               
             //ii1=0
             //case i=k, ii0=l

                        ii0=field;
                        ii=dim;
                     fip=wmod[fencode_hdm(p,i+(field==0),j+(field==1),rho)]*((field==0)*wtemp[fencode_hdm(p,i+(field==0),j+(field==1),tmp2)] + (field==1)*wtemp[fencode_hdm(p,i+(field==0),j+(field==1),tmp3)])*(wtemp[fencode_hdm(p,i+(field==0),j+(field==1),hdnur)]+wtemp[fencode_hdm(p,i+(field==0),j+(field==1),hdnul)])/4.0;




                     fim1=wmod[fencode_hdm(p,i-(field==0),j-(field==1),rho)]*((field==0)*wtemp[fencode_hdm(p,i-(field==0),j-(field==1),tmp2)] + (field==1)*wtemp[fencode_hdm(p,i-(field==0),j-(field==1),tmp3)])*(wtemp[fencode_hdm(p,i-(field==0),j-(field==1),hdnur)]+wtemp[fencode_hdm(p,i-(field==0),j-(field==1),hdnul)]);
                     
		     //dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]+(evalgrad1_hdm(fip, fim1, p,field))/(((p->dx[0])*(field==0))+(p->dx[1])*(field==1));
                      //dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+field)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]-(p->chyp)*grad2_hdm(wmod,p,i,i,mom1+field,dim);

//dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1)]-(p->chyp)*grad2_hdm(wmod,p,i,i,mom1+field,dim);

wtemp[fencode_hdm(p,i,j,tmp4)]=(wmod[fencode_hdm(p,i,j,mom1+ii0)]+wmod[fencode_hdm(p,i+(field==0),j+(field==1),mom1+ii0)])/2;
wtemp[fencode_hdm(p,i,j,tmp5)]=(wmod[fencode_hdm(p,i,j,mom1+ii0)]+wmod[fencode_hdm(p,i-(field==0),j-(field==1),mom1+ii0)])/2;

//grad1l_hdm()

dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,energy)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,energy)]-(p->chyp)*(wtemp[fencode_hdm(p,i,j,tmp4)]-wtemp[fencode_hdm(p,i,j,tmp5)])/(((p->dx[0])*(field==0))+(p->dx[1])*(field==1))/2;


			ii=field;
                        ii0=dim;

		     //dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]+( wtemp[fencode_hdm(p,i,j,tmprhor)]*(wd[fencode_hdm(p,i,j,hdnur)]*grad1r_hdm(wtemp,p,i,j,tmp1,field))-wtemp[fencode_hdm(p,i,j,tmprhol)]*(wd[fencode_hdm(p,i,j,hdnul)]*grad1l_hdm(wtemp,p,i,j,tmp1,field)) )/(((p->dx[0])*(field==0))+(p->dx[1])*(field==1));

dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,field)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,field)]+(evalgrad1_hdm(fip, fim1, p,field))/(((p->dx[0])*(field==0))+(p->dx[1])*(field==1));



         /*    for(ii1=0; ii1<2; i++)
             {
		     if(ii1==0)
                     {
                        ii0=field;
                        ii=dim;
                     }
                     else
                     {
			ii=field;
                        ii0=dim;
                     }

		     if(ii==field)
		     {
		     ;//dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]+( wtemp[fencode_hdm(p,i,j,tmprhor)]*(wd[fencode_hdm(p,i,j,hdnur)]*grad1r_hdm(wtemp,p,i,j,tmp1,field))-wtemp[fencode_hdm(p,i,j,tmprhol)]*(wd[fencode_hdm(p,i,j,hdnul)]*grad1l_hdm(wtemp,p,i,j,tmp1,field)) )/(((p->dx[0])*(field==0))+(p->dx[1])*(field==1));
		     }
		     else
		     {

                     fip=wmod[fencode_hdm(p,i+(field==0),j+(field==1),rho)]*((field==0)*wtemp[fencode_hdm(p,i+(field==0),j+(field==1),tmp2)] + (field==1)*wtemp[fencode_hdm(p,i+(field==0),j+(field==1),tmp3)])*(wtemp[fencode_hdm(p,i+(field==0),j+(field==1),hdnur)]+wtemp[fencode_hdm(p,i+(field==0),j+(field==1),hdnul)])/4.0;




                     fim1=wmod[fencode_hdm(p,i-(field==0),j-(field==1),rho)]*((field==0)*wtemp[fencode_hdm(p,i-(field==0),j-(field==1),tmp2)] + (field==1)*wtemp[fencode_hdm(p,i-(field==0),j-(field==1),tmp3)])*(wtemp[fencode_hdm(p,i-(field==0),j-(field==1),hdnur)]+wtemp[fencode_hdm(p,i-(field==0),j-(field==1),hdnul)]);
                     
		     ;//dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]=dwn1[(NVAR*(p->n[0])*(p->n[1])*order)+fencode_hdm(p,i,j,mom1+ii0)]+(evalgrad1_hdm(fip, fim1, p,field))/(((p->dx[0])*(field==0))+(p->dx[1])*(field==1));
		     
}
             }*/


 
               
 


	}
 __syncthreads();
  
}


/////////////////////////////////////
// error checking routine
/////////////////////////////////////
void checkErrors_hdm(char *label)
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





int cuhyperdifmomsource(struct params **p, real **w, real **wnew, struct params **d_p, real **d_w, real **d_wnew,  real **d_wmod, real **d_dwn1, real **d_wd, int order, real **d_wtemp, int field, int dim)
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
     hyperdifmomsource_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_w,*d_wnew, *d_wmod, *d_dwn1,  *d_wd, order,*d_wtemp, field, dim);
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






