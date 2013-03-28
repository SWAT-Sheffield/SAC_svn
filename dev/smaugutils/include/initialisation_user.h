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

real inte(real **w,int n, int i, int j, real dx)
{

	real res=0.0;

	if (n == 2) 
	  res=dx*0.5*(w[0][j]+w[1][j]);
	else if (n>2) 
	{
	  if(i==0) i++;
	  for( int ii=i;ii<n; ii++)
	      res=res+0.5*(w[ii-1][j]+w[ii][j])*dx;


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
       real mut=1.2;  //maybe mut = 0.6?
	real bzero=1.0e0;// bfield in tesla
	real bscale=0.5e6;
	real zr=0.5e6;

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
          for(i=0;i<n1;i++)
          {
            prese[i]=(real *)calloc(n2,sizeof(real));
	    pres[i]=(real *)calloc(n2,sizeof(real));
            dpdz[i]=(real *)calloc(n2,sizeof(real));
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




	real Bmax=0.10e0  ;// mag field Tesla
	//real Bmin=0.0006d0  ;// mag field Tesla
	real Bmin=0.0005e0  ;// mag field Tesla
	real bnmin,bnmax;

	real d_z=1.0e0 ;// width of Gaussian in Mm
	real z_shift=0.e0 ;// shift in Mm
	real A=1.0e0 ;// amplitude

	real xr=0.15e5;
	real yr=0.15e5;
	real yr=0.0;

	real R2=(xr*xr+yr*yr);

	real A=R2/2.e0;


	maxminb0z(b0z,n1, &bnmin, &bnmax);

        j=0;
        k=0;
	for(i=0;i<n1;i++)
		b0z[i]=exp(-((wd[encode3_uin(p,i,j,k,pos1)]/(scale-z_shift))/d_z)); 

	for(i=0;i<n1li++)
		b0z[i]=Bmin+((Bmax-Bmin)/(bnmax-bnmin))*(b0z[i]-bnmin);

           ii[1]=0;
	   for(i=0;i<=n1-1;i++)
           {	
                ii[0]=i;	
		db0z[i]= grad1d_uin(b0z, wd,p,ii,0);

           } 

        k=0;
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)	
		xf[i][j]=exp(-(wd[encode3_uin(p,i,j,k,pos2)]*wd[encode3_uin(p,i,j,k,pos2)])*b0z[i]/R2);


	printf("compute fields\n");
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {		
		w[encode3_uin(p,i,j,ii[2],b1)]=b0z[i]*xf[i][j];
                w[encode3_uin(p,i,j,ii[2],b2)]=-wd[encode3_uin(p,i,j,k,pos2)]*db0z[j]*xf[i][j]/2;
           } 


          //temp(w, wd,ii, p,T);
	  //for( int i=0;i<p->n[0];i++) 
          //    lambda[i]=-R*T[i]/ggg; //-ve sign because ggg is -ve




        //compute b-field components

	printf("compute fields\n");
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {		
		w[encode3_uin(p,i,j,ii[2],b1)]=-bzero*sin((wd[encode3_uin(p,i,j,k,pos2)]-(wd[encode3_uin(p,i,n2-1,k,pos2)]/2))/bscale)*exp(-(wd[encode3_uin(p,i,j,k,pos1)]-zr)/bscale);
		w[encode3_uin(p,i,j,ii[2],b2)]=bzero*cos((wd[encode3_uin(p,i,j,k,pos2)]-(wd[encode3_uin(p,i,n2-1,k,pos2)]/2))/bscale)*exp(-(wd[encode3_uin(p,i,j,k,pos1)]-zr)/bscale);
           } 








	printf("Computing pressure\n");
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)	
            {
		//prese[i][j]=-ggg*lambda[i]*w[encode3_uin(p,i,j,ii[2],rhob)];
                //prese[i][j]=w[encode3_uin(p,i,j,ii[2],rhob)]*T[i]*R/mut;
                prese[i][j]=presval[i];
               //if(j==0) printf("pres %d %g %g\n", i,T[i],prese[i][j]);

             }







real sum;

printf("compute energy and bfields to background\n");
	for(j=0;j<=n2-1;j++)
	   for(i=0;i<=n1-1;i++)
           {

                w[encode3_uin(p,i,j,ii[2],rho)]=0.0;
                w[encode3_uin(p,i,j,ii[2],mom1)]=0.0;
                w[encode3_uin(p,i,j,ii[2],mom2)]=0.0;
		//w[encode3_uin(p,i,j,ii[2],energyb)]=((pres[i][j]-((bsq[i][j])/2))/(gamma-1))+(bsq[i][j]/2);
                w[encode3_uin(p,i,j,ii[2],energyb)]=((prese[i][j])/(gamma-1));
		w[encode3_uin(p,i,j,ii[2],energy)]=0.0;

		w[encode3_uin(p,i,j,ii[2],b1b)]=w[encode3_uin(p,i,j,ii[2],b1)];
		w[encode3_uin(p,i,j,ii[2],b2b)]=w[encode3_uin(p,i,j,ii[2],b2)];
		w[encode3_uin(p,i,j,ii[2],b1)]=0.0;
		w[encode3_uin(p,i,j,ii[2],b2)]=0.0;
	   }


         free(T);
         free(lambda);
         free(prese);
         free(pres);
         free(presval);
	//free(dbsq);
	//free(bsq);
	free(dpdz);

printf("finished");
	//free(dbzdx);
	//free(dbzdz);
	//free(dbxdx);
	//free(dbxdz);

}

void initialisation_user2(real *w, real *wd, struct params *p) {
                    



}






