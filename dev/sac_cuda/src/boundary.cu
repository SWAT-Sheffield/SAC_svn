#include "../include/cudapars.h"
#include "../include/paramssteeringtest1.h"

/////////////////////////////////////
// standard imports
/////////////////////////////////////
#include <stdio.h>
#include <math.h>
#include "../include/step.h"

/////////////////////////////////////
// kernel function (CUDA device)
/////////////////////////////////////
#include "../include/gradops_b.cuh"

__global__ void boundary_parallel(struct params *p,  struct state *s,  real *wmod, int order)
{

  int iindex = blockIdx.x * blockDim.x + threadIdx.x;
  int i,j;
  int index,k;
  int f;

  int ni=p->n[0];
  int nj=p->n[1];
  real dt=p->dt;
  real dy=p->dx[0];
  real dx=p->dx[1];
                real val=0;
  
   int ip,jp,ipg,jpg;
  int iia[NDIM];
  int dimp=((p->n[0]))*((p->n[1]));
 #ifdef USE_SAC_3D
   int kp,kpg;
   real dz=p->dx[2];
   dimp=((p->n[0]))*((p->n[1]))*((p->n[2]));
#endif  
   //int ip,jp,ipg,jpg;

  #ifdef USE_SAC_3D
   kp=iindex/(nj*ni/((p->npgp[1])*(p->npgp[0])));
   jp=(iindex-(kp*(nj*ni/((p->npgp[1])*(p->npgp[0])))))/(ni/(p->npgp[0]));
   ip=iindex-(kp*nj*ni/((p->npgp[1])*(p->npgp[0])))-(jp*(ni/(p->npgp[0])));
#endif
 #if defined USE_SAC || defined ADIABHYDRO
    jp=iindex/(ni/(p->npgp[0]));
   ip=iindex-(jp*(ni/(p->npgp[0])));
#endif  


int shift=order*NVAR*dimp;

   for(ipg=0;ipg<(p->npgp[0]);ipg++)
   for(jpg=0;jpg<(p->npgp[1]);jpg++)
   #ifdef USE_SAC_3D
     for(kpg=0;kpg<(p->npgp[2]);kpg++)
   #endif
   {

     iia[0]=ip*(p->npgp[0])+ipg;
     iia[1]=jp*(p->npgp[1])+jpg;
     i=iia[0];
     j=iia[1];
     k=0;
     #ifdef USE_SAC_3D
	   iia[2]=kp*(p->npgp[2])+kpg;
           k=iia[2];
           for( f=rho; f<=b3; f++)
     #else
           for( f=rho; f<=b2; f++)
     #endif
             {  
         #ifdef USE_SAC_3D
      if(i<((p->n[0])) && j<((p->n[1]))  && k<((p->n[2])))
     #else
       if(i<((p->n[0])) && j<((p->n[1])))
     #endif           
	{

 
#ifdef ADIABHYDRO
                  bc3_cont_b(wmod+order*NVAR*dimp,p,iia,f);
#else
               bc3_periodic1_b(wmod+order*NVAR*dimp,p,iia,f);  //for OZT
               //  bc3_cont_cd4_b(wmod+order*NVAR*dimp,p,iia,f);  //for BW
#endif                

                //  bc3_fixed_b(wmod+order*NVAR*dimp,p,iia,f,0.0);

	}

               }
}
 __syncthreads();

#ifdef ADIABHYDRO
;
#else
  //This second call makes sure corners are set correctly
   for(ipg=0;ipg<(p->npgp[0]);ipg++)
   for(jpg=0;jpg<(p->npgp[1]);jpg++)
   #ifdef USE_SAC_3D
     for(kpg=0;kpg<(p->npgp[2]);kpg++)
   #endif
   {

     iia[0]=ip*(p->npgp[0])+ipg;
     iia[1]=jp*(p->npgp[1])+jpg;
     i=iia[0];
     j=iia[1];
     k=0;
     #ifdef USE_SAC_3D
	   iia[2]=kp*(p->npgp[2])+kpg;
           k=iia[2];
           for( f=rho; f<=b3; f++)
     #else
           for( f=rho; f<=b2; f++)
     #endif
             {  
         #ifdef USE_SAC_3D
      if(i<((p->n[0])) && j<((p->n[1]))  && k<((p->n[2])))
     #else
       if(i<((p->n[0])) && j<((p->n[1])))
     #endif    

                  bc3_periodic2_b(wmod+order*NVAR*dimp,p,iia,f);


   } 
}
 __syncthreads();
#endif



  
}

int cuboundary(struct params **p, struct params **d_p,  struct state **d_s,  real **d_wmod,  int order)
{


 dim3 dimBlock(dimblock, 1);

int numBlocks = ((dimproduct_b(*p)+numThreadsPerBlock-1)) / numThreadsPerBlock;

    boundary_parallel<<<numBlocks, numThreadsPerBlock>>>(*d_p,*d_s, *d_wmod, order);

    cudaThreadSynchronize();

}
