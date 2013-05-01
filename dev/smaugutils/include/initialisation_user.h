#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned long int encode3_uin(params *dp,int ix, int iy, int iz, int field) {
  #ifdef USE_SAC_3D
    return ( (iz*((dp)->n[0])*((dp)->n[1])  + iy * ((dp)->n[0]) + ix)+(field*((dp)->n[0])*((dp)->n[1])*((dp)->n[2])));
  #else
    return ( (iy * ((dp)->n[0]) + ix)+(field*((dp)->n[0])*((dp)->n[1])));
  #endif
}

unsigned long int fencode3_uin (struct params *dp,int *ii, int field) {
#ifdef USE_SAC_3D
   return (ii[2]*((dp)->n[0])*((dp)->n[1])  + ii[1] * ((dp)->n[0]) + ii[0]+(field*((dp)->n[0])*((dp)->n[1])*((dp)->n[2])));
#else
   return ( ii[1] * ((dp)->n[0]) + ii[0]+(field*((dp)->n[0])*((dp)->n[1])));
#endif
}




real grad1d_uin(real *wmod, real *wd,struct params *p,int *ii,int dir)
{

 real grad=0;

 switch(dir)
 {
   case 0:

if(ii[0]>1 && ii[0]<((p->n[0])-2) )
 grad=(  ( ((8*wmod[ii[0]+1]-8*wmod[ii[0]-1]+wmod[ii[0]-2]-wmod[ii[0]+2])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx1)]))    );



  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[0]==(p->n[0])-3) || (ii[0]==(p->n[0])-4)  && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
   else if(ii[0]==2 || ii[0]==3  && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
  #endif
   break;
}



 return grad;


}











#ifdef USE_SAC_3D
real grad3dngen_uin(real ***wmod, real *wd,struct params *p,int *ii,int dir)
#else
real grad3dngen_uin(real **wmod, real *wd,struct params *p,int *ii,int dir)
#endif
{


 real grad=0;

 

 switch(dir)
 {
   case 0:
#ifdef USE_SAC_3D

if(ii[0]>1 && ii[0]<((p->n[0])-2) )
 grad=(  ( ((8*wmod[ii[0]+1][ii[1]][ii[2]]-8*wmod[ii[0]-1][ii[1]][ii[2]]+wmod[ii[0]-2][ii[1]][ii[2]]-wmod[ii[0]+2][ii[1]][ii[2]])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx1)]))    );




  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[0]==(p->n[0])-3) || (ii[0]==(p->n[0])-4)  && ii[1]>1   && ii[1]<(p->n[1])-2 && ii[2]>1   && ii[2]<(p->n[2])-2  )
       grad=0;
   else if(ii[0]==2 || ii[0]==3  && ii[1]>1   && ii[1]<(p->n[1])-2 && ii[2]>1   && ii[2]<(p->n[2])-2  )
       grad=0;
  #endif

#else  


if(ii[0]>1 && ii[0]<((p->n[0])-2) )
 grad=(  ( ((8*wmod[ii[0]+1][ii[1]]-8*wmod[ii[0]-1][ii[1]]+wmod[ii[0]-2][ii[1]]-wmod[ii[0]+2][ii[1]])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx1)]))    );



  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[0]==(p->n[0])-3) || (ii[0]==(p->n[0])-4)  && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
   else if(ii[0]==2 || ii[0]==3  && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
  #endif
#endif


   break;

   case 1:


#ifdef USE_SAC_3D


if( ii[1] >1 &&  ii[1]<((p->n[1])-2))
	grad=(  ( ((8*wmod[ii[0]][ii[1]+1][ii[2]]-8*wmod[ii[0]][ii[1]-1][ii[2]]+wmod[ii[0]][ii[1]-2][ii[2]]-wmod[ii[0]][ii[1]+2][ii[2]])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx2)]))    );


  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[1]==(p->n[1])-3) || (ii[1]==(p->n[1])-4)  && ii[0]>1   && ii[0]<(p->n[0])-2  && ii[2]>1   && ii[2]<(p->n[2])-2  )
       grad=0;
   else if(ii[1]==2 || ii[1]==3  && ii[0]>1   && ii[0]<(p->n[0])-2  && ii[2]>1   && ii[2]<(p->n[2])-2  )
       grad=0;
  #endif
#else

 
if( ii[1] >1 &&  ii[1]<((p->n[1])-2))
	grad=(  ( ((8*wmod[ii[0]][ii[1]+1]-8*wmod[ii[0]][ii[1]-1]+wmod[ii[0]][ii[1]-2]-wmod[ii[0]][ii[1]+2])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx2)]))    );



  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[1]==(p->n[1])-3) || (ii[1]==(p->n[1])-4)  && ii[0]>1   && ii[0]<(p->n[0])-2  )
       grad=0;
   else if(ii[1]==2 || ii[1]==3  && ii[0]>1   && ii[0]<(p->n[0])-2  )
       grad=0;
  #endif
#endif


   break;


   case 2:
#ifdef USE_SAC_3D
 
if( ii[2] >1 &&  ii[2]<((p->n[2])-2))
	grad=(  ( ((8*wmod[ii[0]][ii[1]][ii[2]+1]-8*wmod[ii[0]][ii[1]][ii[2]-1]+wmod[ii[0]][ii[1]][ii[2]-2]-wmod[ii[0]][ii[1]][ii[2]+2])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx3)]))    );




  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[2]==(p->n[2])-3) || (ii[2]==(p->n[2])-4)  && ii[0]>1   && ii[0]<(p->n[0])-2 && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
   else if(ii[2]==2 || ii[2]==3  && ii[0]>1   && ii[0]<(p->n[0])-2 && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
  #endif
#endif

   break;


}



 return grad;


}



real grad3dn_uin(real *wmod, real *wd,struct params *p,int *ii,int field,int dir)
{


 real grad=0;

 

 switch(dir)
 {
   case 0:
 
#ifdef USE_SAC_3D
  #ifdef USE_DORDER3
 if(ii[0]>2 && ii[0]<((p->n[0])-3) )
  grad=(  ( ((3*wmod[encode3_uin(p,ii[0]+1,ii[1],ii[2],field)]-3*wmod[encode3_uin(p,ii[0]-1,ii[1],ii[2],field)]+3.0*(wmod[encode3_uin(p,ii[0]-2,ii[1],ii[2],field)]-wmod[encode3_uin(p,ii[0]+2,ii[1],ii[2],field)])/5.0-(wmod[encode3_uin(p,ii[0]-3,ii[1],ii[2],field)]-wmod[encode3_uin(p,ii[0]+3,ii[1],ii[2],field)])/15.0)/2.0))/(2.0*(wd[fencode3_uin(p,ii,delx1)]))    );

  #else
if(ii[0]>1 && ii[0]<((p->n[0])-2) )
 grad=(  ( ((8*wmod[encode3_uin(p,ii[0]+1,ii[1],ii[2],field)]-8*wmod[encode3_uin(p,ii[0]-1,ii[1],ii[2],field)]+wmod[encode3_uin(p,ii[0]-2,ii[1],ii[2],field)]-wmod[encode3_uin(p,ii[0]+2,ii[1],ii[2],field)])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx1)]))    );
 #endif

#ifdef USE_MPI
if(p->boundtype[field][dir][0] !=1  )
  if(p->mpiupperb[dir]==1  )
#else
if(p->boundtype[field][dir][0] !=0  )
#endif
{

  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[0]==(p->n[0])-3) || (ii[0]==(p->n[0])-4)  && ii[1]>1   && ii[1]<(p->n[1])-2 && ii[2]>1   && ii[2]<(p->n[2])-2  )
       grad=0;
   else if(ii[0]==2 || ii[0]==3  && ii[1]>1   && ii[1]<(p->n[1])-2 && ii[2]>1   && ii[2]<(p->n[2])-2  )
       grad=0;
  #endif
}
#else  

  #ifdef USE_DORDER3
if(ii[0]>2 && ii[0]<((p->n[0])-3) )
 grad=(  ( ((3*wmod[encode3_uin(p,ii[0]+1,ii[1],0,field)]-3*wmod[encode3_uin(p,ii[0]-1,ii[1],0,field)]+3.0*(wmod[encode3_uin(p,ii[0]-2,ii[1],0,field)]-wmod[encode3_uin(p,ii[0]+2,ii[1],0,field)])/5.0-(wmod[encode3_uin(p,ii[0]-3,ii[1],0,field)]-wmod[encode3_uin(p,ii[0]+3,ii[1],0,field)])/15.0)/2.0))/(2.0*(wd[fencode3_uin(p,ii,delx1)]))    );

  #else
if(ii[0]>1 && ii[0]<((p->n[0])-2) )
 grad=(  ( ((8*wmod[encode3_uin(p,ii[0]+1,ii[1],0,field)]-8*wmod[encode3_uin(p,ii[0]-1,ii[1],0,field)]+wmod[encode3_uin(p,ii[0]-2,ii[1],0,field)]-wmod[encode3_uin(p,ii[0]+2,ii[1],0,field)])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx1)]))    );
 #endif
#ifdef USE_MPI
if(p->boundtype[field][dir][0] !=1  )
  if(p->mpiupperb[dir]==1  )
#else
if(p->boundtype[field][dir][0] !=0  )
#endif
{

  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[0]==(p->n[0])-3) || (ii[0]==(p->n[0])-4)  && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
   else if(ii[0]==2 || ii[0]==3  && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
  #endif
}
#endif



   break;

   case 1:

#ifdef USE_SAC_3D

  #ifdef USE_DORDER3
 if(ii[1]>2 && ii[1]<((p->n[1])-3) )
  grad=(  ( ((3*wmod[encode3_uin(p,ii[0],ii[1]+1,ii[2],field)]-3*wmod[encode3_uin(p,ii[0],ii[1]-1,ii[2],field)]+3.0*(wmod[encode3_uin(p,ii[0],ii[1]-2,ii[2],field)]-wmod[encode3_uin(p,ii[0],ii[1]+2,ii[2],field)])/5.0-(wmod[encode3_uin(p,ii[0],ii[1]-3,ii[2],field)]-wmod[encode3_uin(p,ii[0],ii[1]+3,ii[2],field)])/15.0)/2.0))/(2.0*(wd[fencode3_uin(p,ii,delx2)]))    );

#else
if( ii[1] >1 &&  ii[1]<((p->n[1])-2))
	grad=(  ( ((8*wmod[encode3_uin(p,ii[0],ii[1]+1,ii[2],field)]-8*wmod[encode3_uin(p,ii[0],ii[1]-1,ii[2],field)]+wmod[encode3_uin(p,ii[0],ii[1]-2,ii[2],field)]-wmod[encode3_uin(p,ii[0],ii[1]+2,ii[2],field)])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx2)]))    );
 #endif
#ifdef USE_MPI
if(p->boundtype[field][dir][0] !=1  )
  if(p->mpiupperb[dir]==1  )
#else
if(p->boundtype[field][dir][0] !=0  )
#endif
{
  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[1]==(p->n[1])-3) || (ii[1]==(p->n[1])-4)  && ii[0]>1   && ii[0]<(p->n[0])-2  && ii[2]>1   && ii[2]<(p->n[2])-2  )
       grad=0;
   else if(ii[1]==2 || ii[1]==3  && ii[0]>1   && ii[0]<(p->n[0])-2  && ii[2]>1   && ii[2]<(p->n[2])-2  )
       grad=0;
  #endif
}
#else

  #ifdef USE_DORDER3
if(ii[1]>2 && ii[1]<((p->n[1])-3) )
 grad=(  ( ((3*wmod[encode3_uin(p,ii[0],ii[1]+1,0,field)]-3*wmod[encode3_uin(p,ii[0],ii[1]-1,0,field)]+3.0*(wmod[encode3_uin(p,ii[0],ii[1]-2,0,field)]-wmod[encode3_uin(p,ii[0],ii[1]+2,0,field)])/5.0-(wmod[encode3_uin(p,ii[0],ii[1]-3,0,field)]-wmod[encode3_uin(p,ii[0],ii[1]+3,0,field)])/15.0)/2.0))/(2.0*(wd[fencode3_uin(p,ii,delx2)]))    );

#endif
if( ii[1] >1 &&  ii[1]<((p->n[1])-2))
	grad=(  ( ((8*wmod[encode3_uin(p,ii[0],ii[1]+1,0,field)]-8*wmod[encode3_uin(p,ii[0],ii[1]-1,0,field)]+wmod[encode3_uin(p,ii[0],ii[1]-2,0,field)]-wmod[encode3_uin(p,ii[0],ii[1]+2,0,field)])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx2)]))    );

#ifdef USE_MPI
if(p->boundtype[field][dir][0] !=1  )
  if(p->mpiupperb[dir]==1  )
#else
if(p->boundtype[field][dir][0] !=0  )
#endif
{

  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[1]==(p->n[1])-3) || (ii[1]==(p->n[1])-4)  && ii[0]>1   && ii[0]<(p->n[0])-2  )
       grad=0;
   else if(ii[1]==2 || ii[1]==3  && ii[0]>1   && ii[0]<(p->n[0])-2  )
       grad=0;
  #endif
}
#endif
   break;


   case 2:

#ifdef USE_SAC_3D
  #ifdef USE_DORDER3
 if(ii[2]>2 && ii[2]<((p->n[2])-3) )
  grad=(  ( ((3*wmod[encode3_uin(p,ii[0],ii[1],ii[2]+1,field)]-3*wmod[encode3_uin(p,ii[0],ii[1],ii[2]-1,field)]+3.0*(wmod[encode3_uin(p,ii[0],ii[1],ii[2]-2,field)]-wmod[encode3_uin(p,ii[0],ii[1],ii[2]+2,field)])/5.0-(wmod[encode3_uin(p,ii[0],ii[1],ii[2]-3,field)]-wmod[encode3_uin(p,ii[0],ii[1],ii[2]+3,field)])/15.0)/2.0))/(2.0*(wd[fencode3_uin(p,ii,delx3)]))    );

#else
if( ii[2] >1 &&  ii[2]<((p->n[2])-2))
	grad=(  ( ((8*wmod[encode3_uin(p,ii[0],ii[1],ii[2]+1,field)]-8*wmod[encode3_uin(p,ii[0],ii[1],ii[2]-1,field)]+wmod[encode3_uin(p,ii[0],ii[1],ii[2]-2,field)]-wmod[encode3_uin(p,ii[0],ii[1],ii[2]+2,field)])/6.0))/(2.0*(wd[fencode3_uin(p,ii,delx3)]))    );
#endif

#ifdef USE_MPI
if(p->boundtype[field][dir][0] !=1  )
  if(p->mpiupperb[dir]==1  )
#else
if(p->boundtype[field][dir][0] !=0  )
#endif
{

  ;//for OZT test using MPI use this directive further clarification needed
  #ifndef USE_MPI
   if((ii[2]==(p->n[2])-3) || (ii[2]==(p->n[2])-4)  && ii[0]>1   && ii[0]<(p->n[0])-2 && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
   else if(ii[2]==2 || ii[2]==3  && ii[0]>1   && ii[0]<(p->n[0])-2 && ii[1]>1   && ii[1]<(p->n[1])-2  )
       grad=0;
  #endif
}
#endif
   break;

}



 return grad;


}









//sum=inte(dpdz,i,j,p->dx[0]);

real inte(real **w,int i, int j, real dx, real dir, int n, int lu, int ll)
{

	real res=0.0;

if(dir==0)
{
	if (n == 2) 
	  res=dx*0.5*(w[0][j]+w[1][j]);
	else if (n>2) 
	{
	  if(i==0) i++;
	  for( int ii=ll;ii<=lu; ii++)
	      res=res+0.5*(w[ii-1][j]+w[ii][j])*dx;


	}
}
if(dir==1)
{
	if (n == 2) 
	  res=dx*0.5*(w[i][0]+w[i][1]);
	else if (n>2) 
	{
	  if(j==0) j++;
	  for( int jj=ll;jj<=lu; jj++)
	      res=res+0.5*(w[i][jj-1]+w[i][jj])*dx;


	}
}
	return res;
}

void temp(real *w, real *wd,int *ii, struct params *p, real *T)
{

	real yt=2.0e6; // m
	real yw=200.0e3;//  m
	real yr=4.0e6;//m

	real tch=15.0e3;//temp chromosphere K
	real tc=3.0e6;//temp corona K

	real dt=tch/tc;

	for( int i=0;i<p->n[0];i++) 
		T[i]=0.5*tc*( 1+dt+(1.0-dt)*tanh((wd[encode3_uin(p,i,ii[1],ii[2],pos1)]-yt)/yw));
}

void maxminb0z(real *b0z,int n1, real *bnmin, real *bnmax)
{
     real tmax;
     real tmin;
 
     tmax=-9.9e99;
     tmin=9.9e99;

     for(int i=0; i<n1; i++)
     {
        if(b0z[i]>tmax)
	   tmax=b0z[i];
        if(b0z[i]<tmin)
           tmin=b0z[i];

        *bnmax=tmax;
        *bnmin=tmin;
     }
}

//bach3d

void initialisation_user1(real *w, real *wd, struct params *p) {
                    
int ntt=-1;
int count;
int nh;	
        real h,rho0, TT0,p0;
        int i,j,k;
        int n1,n2,n3;
        int ip,ipp;
        int ii[3];
        char st1[200],st2[200],st3[200],st4[200];

        real x,y,z;
        //FILE *fatmos;
        char *inbuf;
        k=0;

       real R=8.31e3;//US standard atmosphere
       real gamma=1.66666667;
	real ggg=-274.0;
       real mu=4.0*PI/1.0e7;
printf("mu and PI %g %g\n",mu,PI);
       real mut=1.2;  //maybe mut = 0.6?
	real bzero=1.0e0;// bfield in tesla
	real bscale=0.5e6;
	real zr=0.5e6;


	real Bmax=0.250e0  ;// mag field Tesla
	//real Bmin=0.0006d0  ;// mag field Tesla
	real Bmin=0.0005e0  ;// mag field Tesla
	real bnmin,bnmax;

	real d_z=1.0e0 ;// width of Gaussian in Mm
	real z_shift=0.e0 ;// shift in Mm
	//real A=1.0e0 ;// amplitude
       real scale=1.0e6 ;
	//real xr=0.15e5;
        real xr=0.1e5;
        real yr=0.1e5;
	//real yr=0.15e5;
	//real yr=0.0;

	real R2=(xr*xr+yr*yr);

	real A=R2/2.e0;
//R2=1.0;



	real iniene;
        
//iniene=731191.34d0*8.31e3*(1.1806882e-11)/0.6d0/(eqpar(gamma_)-1.0)

//iniene=731191.34d0*8.31e3*(1.1790001e-11)/0.6d0/(eqpar(gamma_)-1.0)

// 1.6Mm

iniene=6840.e0*8.31e3*(2.3409724e-09)/0.6e0/((gamma)-1.0);

//iniene=6840.d0*8.31e3*(2.2139002e-09)/0.6d0/(eqpar(gamma_)-1.0)

//iniene=731191.34d0*8.31e3*(4.5335481e-12)/0.6d0/(eqpar(gamma_)-1.0)


//inbuf=(char *)calloc(500,sizeof(char));
	  /*i=ii[0];
	  j=ii[1];
	  k=ii[2];

          x=i*(p->dx[0]);
          y=i*(p->dx[1]);
          z=i*(p->dx[2]);*/

          n1=(p->n[0]);///(p->pnpe[0]);
          n2=p->n[1];///(p->pnpe[1]);
          ii[0]=n1/2;
          ii[1]=n2/2;
	  ii[2]=0;


          real *T, *lambda, *presval;
          real **pres,**prese,**dbzdx,**dbxdx,**dbzdz,**dbxdz,**bsq,**dbsq,**dpdz;
	  real **bvari, **bvarix, **dbxbzdz,**dbxbzdx, **dbxbxdx, **rho1,**bxbz;
          //real **dbydx,**dbydy, **dbydz, **dbxdy, **dbzdy, **bvariy

	  real *b0z, *db0z;
	  real **xf;    //opening function
          
	  b0z=(real *)calloc(n1,sizeof(real));
	  db0z=(real *)calloc(n1,sizeof(real));

          xf=(real **)calloc(n1,sizeof(real *));
          for(i=0;i<n1;i++)
          {
            xf[i]=(real *)calloc(n2,sizeof(real));
          }






          T=(real *)calloc(n1,sizeof(real));
          lambda=(real *)calloc(n1,sizeof(real));
          presval=(real *)calloc(n1,sizeof(real));

	  pres=(real **)calloc(n1,sizeof(real *));
          prese=(real **)calloc(n1,sizeof(real *));
          dpdz=(real **)calloc(n1,sizeof(real *));

          bxbz=(real **)calloc(n1,sizeof(real *));
	  dbzdx=(real **)calloc(n1,sizeof(real *));
          dbxdx=(real **)calloc(n1,sizeof(real *));
          dbzdz=(real **)calloc(n1,sizeof(real *));
	  dbxdz=(real **)calloc(n1,sizeof(real *));
          bsq=(real **)calloc(n1,sizeof(real *));
          dbsq=(real **)calloc(n1,sizeof(real *));
          bvari=(real **)calloc(n1,sizeof(real *));
          bvarix=(real **)calloc(n1,sizeof(real *));
         dbxbzdz=(real **)calloc(n1,sizeof(real *));
         dbxbzdx=(real **)calloc(n1,sizeof(real *));
         rho1=(real **)calloc(n1,sizeof(real *));


          for(i=0;i<n1;i++)
          {
            prese[i]=(real *)calloc(n2,sizeof(real));
	    pres[i]=(real *)calloc(n2,sizeof(real));
            dpdz[i]=(real *)calloc(n2,sizeof(real));
          bxbz[i]=(real *)calloc(n2,sizeof(real ));
	  dbzdx[i]=(real *)calloc(n2,sizeof(real ));
          dbxdx[i]=(real *)calloc(n2,sizeof(real ));
          dbzdz[i]=(real *)calloc(n2,sizeof(real ));
	  dbxdz[i]=(real *)calloc(n2,sizeof(real ));
          bsq[i]=(real *)calloc(n2,sizeof(real ));
          dbsq[i]=(real *)calloc(n2,sizeof(real ));
          bvari[i]=(real *)calloc(n2,sizeof(real ));
          bvarix[i]=(real *)calloc(n2,sizeof(real ));
          dbxbzdz[i]=(real *)calloc(n2,sizeof(real ));
          dbxbzdx[i]=(real *)calloc(n2,sizeof(real ));
          rho1[i]=(real *)calloc(n2,sizeof(real ));



          }
          printf("open atmosphere file");

          //read the atmosphere file
          //FILE *fatmos=fopen("/data/cs1mkg/smaug_spicule1/atmosphere/VALMc_rho_8184.dat","r");
          FILE *fatmos=fopen("/data/cs1mkg/smaugutils/atmosphere/VALMc_rho_2048_test.dat","r");

h=atof(st1);
rho0=atof(st3);
TT0=atof(st2);
p0=atof(st4);
printf("vars %g %g %g\n",h,TT0,rho0);


#ifdef USE_MULTIGPU

        ipe2iped(p);
        ip=1+(p->pipe[0]);



		 //atmosphere stored from top of corona to photosphere!
		  //skip the first few fields 
                printf("%d %d %d\n",p->ipe,p->pipe[0],ip);
		  for(ipp=1; ipp<ip; ipp++)
		       for(i=0; i<n1; i++)
                          fscanf(fatmos, " %s %s %s %s %n", st1, st2,st3,st4,&ntt);


#endif



          for(i=0; i<((n1)); i++)
          {
            ii[0]=i;
            //fscanf(fatmos, "%g %g", &h, &rho0);
            fscanf(fatmos, " %s %s %s %s %n", st1, st2, st3, st4,&ntt);
		h=atof(st1);
		rho0=atof(st3);
                TT0=atof(st2);
                T[i]=TT0;
                presval[i]=atof(st4);
                
//if(p->ipe==1)
//       printf("%d %g %g \n",i, h,rho0);
		 for(j=0; j<n2; j++)
		#ifdef USE_SAC_3D
		 for(k=0; k<n3; k++)
                #endif
                 {
                     ii[1]=j;
                     ii[2]=k;
                     w[encode3_uin(p,ii[0],ii[1],ii[2],rhob)]=rho0;
                 }
          }

          fclose(fatmos);







        j=0;
        k=0;
	for(i=0;i<n1;i++)
		b0z[i]=exp(-((wd[encode3_uin(p,i,j,k,pos1)]/(scale-z_shift))/d_z)); 


	maxminb0z(b0z,n1, &bnmin, &bnmax);



        printf("%g %g %g %g\n",Bmin,Bmax,bnmin,bnmax);
	for(i=0;i<n1;i++)
         {
		b0z[i]=Bmin+((Bmax-Bmin)/(bnmax-bnmin))*(b0z[i]-bnmin);
              //printf("boz[%i] %g \n",i,b0z[i]);
         }


 printf("\n\n");

           ii[1]=0;
	   for(i=0;i<=n1-1;i++)
           {	
                ii[0]=i;	
		db0z[i]= grad1d_uin(b0z, wd,p,ii,0);
                //printf("dboz[%i] %g \n",i,db0z[i]);

           } 
           printf("\n\n");

        k=0;
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)	
           {
		xf[i][j]=exp(-(wd[encode3_uin(p,i,j,k,pos2)]*wd[encode3_uin(p,i,j,k,pos2)])*b0z[i]/R2);
                if(i==0)
                  printf("xf %d %g %g\n",j,xf[i][j],(wd[encode3_uin(p,i,j,k,pos2)]*wd[encode3_uin(p,i,j,k,pos2)])*b0z[i]/R2);
            }


	printf("compute fields\n");
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {		
		w[encode3_uin(p,i,j,ii[2],b1b)]=(b0z[i]*xf[i][j])/sqrt(mu);
                w[encode3_uin(p,i,j,ii[2],b2b)]=-(wd[encode3_uin(p,i,j,k,pos2)]*db0z[j]*xf[i][j]/2)/sqrt(mu);
           } 


printf("compute bsq\n");
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {
		bsq[i][j]=w[encode3_uin(p,i,j,ii[2],b1b)]*w[encode3_uin(p,i,j,ii[2],b1b)]+w[encode3_uin(p,i,j,ii[2],b2b)]*w[encode3_uin(p,i,j,ii[2],b2b)];
		w[encode3_uin(p,i,j,ii[2],rho)]=0.0;
		w[encode3_uin(p,i,j,ii[2],energyb)]=iniene;
		w[encode3_uin(p,i,j,ii[2],mom1)]=0.0;
		w[encode3_uin(p,i,j,ii[2],mom2)]=0.0;
                dpdz[i][j]=0.0;
                dbsq[i][j]=0.0;
		dbzdx[i][j]=0.0;
		dbzdz[i][j]=0.0;
		dbxdx[i][j]=0.0;
		dbxdz[i][j]=0.0;
                pres[i][j]=0.0;
		bvari[i][j]=0.0;
		bvarix[i][j]=0.0;
		dbxbzdz[i][j]=0.0;
		dbxbzdx[i][j]=0.0;
		rho1[i][j]=0.0;
            }


printf("compute derivative\n");
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {
		  ii[0]=i;
		  ii[1]=j;
		  dbsq[i][j]=grad3dngen_uin(bsq, wd,p,ii,0);

                  dbzdz[i][j]=grad3dn_uin(w, wd,p,ii,b1b,0);
                  dbzdx[i][j]=grad3dn_uin(w, wd,p,ii,b1b,1);
                  dbxdz[i][j]=grad3dn_uin(w, wd,p,ii,b2b,0);
                  dbxdx[i][j]=grad3dn_uin(w, wd,p,ii,b2b,1);
                  bxbz[i][j]=w[encode3_uin(p,i,j,ii[2],b1b)]*w[encode3_uin(p,i,j,ii[2],b2b)];
                 // dpdz[i][j]=ggg*w[encode3_uin(p,i,j,ii[2],rho)]-w[encode3_uin(p,i,j,ii[2],b1b)]*dbzdz[i][j]-w[encode3_uin(p,i,j,ii[2],b2b)]*dbzdx[i][j]-dbsq[i][j]/2;
                 // dpdz[i][j]=-ggg*w[encode3_uin(p,i,j,ii[2],rhob)];
	   }


printf("compute dbxbzdz dbxbzdx\n");
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {
		  ii[0]=i;
		  ii[1]=j;

		  dbxbzdz[i][j]=grad3dngen_uin(bxbz, wd,p,ii,0);
		  dbxbzdx[i][j]=grad3dngen_uin(bxbz, wd,p,ii,1);
	   }

printf("bvarix\n");

	for(i=0;i<=n1-1;i++)
	for(j=0;j<=n2-1;j++)
           {
		  ii[0]=i;
		  ii[1]=j;

		  bvarix[i][j]=inte(dbxbzdz,i,j,p->dx[1],1,p->n[1],j,0);
	   }

printf("bvari\n");

	for(i=0;i<=n1-1;i++)
	for(j=0;j<=n2-1;j++)
           {
		  ii[0]=i;
		  ii[1]=j;

		  bvari[i][j]=((bvarix[i][j])/2.0)-(w[encode3_uin(p,i,j,ii[2],b1b)]*w[encode3_uin(p,i,j,ii[2],b1b)])/2.0;
	   }

printf("dpdz\n");

	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {
		  ii[0]=i;
		  ii[1]=j;

		  dpdz[i][j]=grad3dngen_uin(bvari, wd,p,ii,0);
	   }

printf("rho1\n");

	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {
		  ii[0]=i;
		  ii[1]=j;

		  rho1[i][j]=(-dbxbzdx[i][j]+dpdz[i][j])/ggg;
	   }

printf("pres\n");

	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {
		  ii[0]=i;
		  ii[1]=j;
		  if((w[encode3_uin(p,i,j,ii[2],rhob)]+rho1[i][j])>0) w[encode3_uin(p,i,j,ii[2],rhob)]+=rho1[i][j];
		  pres[i][j]=bvari[i][j]+w[encode3_uin(p,i,j,ii[2],energyb)]*(gamma-1);

                if(((pres[i][j])/(gamma-1))+0.5*((w[encode3_uin(p,i,j,ii[2],b1b)]*w[encode3_uin(p,i,j,ii[2],b1b)])+(w[encode3_uin(p,i,j,ii[2],b2b)]*w[encode3_uin(p,i,j,ii[2],b2b)]))>0)
                  w[encode3_uin(p,i,j,ii[2],energyb)]=((pres[i][j])/(gamma-1))+0.5*((w[encode3_uin(p,i,j,ii[2],b1b)]*w[encode3_uin(p,i,j,ii[2],b1b)])+(w[encode3_uin(p,i,j,ii[2],b2b)]*w[encode3_uin(p,i,j,ii[2],b2b)]));

	   }



//compute upper and lower biundary terms
/*;lower boundary

for ix_1=3,2,-1 do begin
  for ix_2=0,n2-1 do begin
;  for ix_3=0,n3-1 do begin  
         p_2=rho1(ix_1,ix_2)*ggg
         p(ix_1-1,ix_2) = (z(1)-z(0))*p_2+p(ix_1,ix_2)
;  endfor  
  endfor
 endfor


;upper boundary

for ix_1=n1-3,n1-2 do begin
   for ix_2=0,n2-1 do begin
;   for ix_3=0,n3-1 do begin   
           p_2=rho1(ix_1,ix_2)*ggg
           p(ix_1+1,ix_2) = -(z(1)-z(0))*p_2+p(ix_1,ix_2)
;   endfor	   
   endfor
endfor*/
printf("free memory\n");

         free(T);
         free(lambda);
         free(prese);
         free(pres);
         free(presval);
	//free(dbsq);
	//free(bsq);
	free(dpdz);

          free(dbzdx);
	  free(dbxdx);
	  free(dbzdz);
	  free(dbxdz);
         /* free(bsq);
          free(dbsq);
         // free(dpdz);
	  free(bvari);
	  free(bvarix);
          free(dbxbzdz);
          free(dbxbxdx);
          free(rho1);
	  free(b0z);
          free(db0z);
	  free(xf);   */ //opening function
printf("finished");
	

}

void initialisation_user2(real *w, real *wd, struct params *p) {
                    



}






