#include "../include/readwrite.h"

void freadl(FILE *stream, char **string)
{    
    unsigned long counter = 0;
    char *line = NULL;
    int next = fgetc(stream);

    do {
        next = fgetc(stream);
        if (next == EOF) {
            free(line);
            break;
        }
        ++counter;
        line = (char*)realloc(line, counter + 1);
        if (line == NULL) {
            puts("line == NULL");
            exit(EXIT_FAILURE);
        }
        line[counter - 1] = (char)next;
    } while (next != '\n');
    line[counter - 1] = '\0';
    *string = (char *)malloc(strlen(line) + 1);
    if (*string == NULL) {
        puts("*string == NULL");
    } else {
        strcpy(*string, line);
    }
    free(line);

}



int createlog(char *logfile)
{
	int status=0;

      FILE *fdt=0;

      fdt=fopen(logfile,"a+");
      fprintf(fdt,"it   t   dt    rho m1 m2 m3 e bx by bz\n");
      fclose(fdt);	

	return status;
}

int appendlog(char *logfile, params p, state s)
{
  int status=0;
      FILE *fdt=0;

      fdt=fopen(logfile,"a+");
      fprintf(fdt,"%d %f %f %f %f %f %f %f %f %f %f %f\n",s.it,
               s.t,s.dt,s.rho,s.m1,s.m2,s.m3,s.e,s.b1,s.b2,s.b3);
      fclose(fdt);
  return status;
}

int writeconfig(char *name,int n,params p, meta md, real *w)
{
  int status=0;
  int i1,j1;
  int ni,nj;
  char configfile[300];


  ni=p.n[0];
  nj=p.n[1];



      //save file containing current data
      sprintf(configfile,"tmp/%ss%d.out",name,n);
      printf("check dims %d %d \n",ni,nj);
      FILE *fdt=fopen(configfile,"w");
      fprintf(fdt,"%d\n",n);
     for( j1=(p.ng[1]);j1<(nj-(p.ng[1]));j1++)
      {
        for( i1=(p.ng[0]);i1<(nj-(p.ng[0]));i1++)
	{
               // printf("%d %d ", i1,j1);
 #ifdef ADIABHYDRO
		fprintf(fdt,"%d %d %f %f %f %f \n",i1,j1,w[(j1*ni+i1)+(ni*nj*rho)],w[(j1*ni+i1)+(ni*nj*mom1)],w[(j1*ni+i1)+(ni*nj*mom2)],w[j1*ni+i1+(ni*nj*energy)]);
#endif
 #ifdef USE_SAC
		fprintf(fdt,"%d %d %f %f %f %f %f %f\n",i1,j1,w[(j1*ni+i1)+(ni*nj*rho)],w[(j1*ni+i1)+(ni*nj*mom1)],w[(j1*ni+i1)+(ni*nj*mom2)],w[j1*ni+i1+(ni*nj*energy)],w[j1*ni+i1+(ni*nj*b1)],w[j1*ni+i1+(ni*nj*b2)]);
#endif
 #ifdef USE_SAC_3D
		fprintf(fdt,"%d %d %f %f %f %f %f %f %f %f\n",i1,j1,w[(j1*ni+i1)+(ni*nj*rho)],w[(j1*ni+i1)+(ni*nj*mom1)],w[(j1*ni+i1)+(ni*nj*mom2)],w[j1*ni+i1+(ni*nj*mom3)],w[j1*ni+i1+(ni*nj*energy)],w[j1*ni+i1+(ni*nj*b1)],w[j1*ni+i1+(ni*nj*b2)],w[j1*ni+i1+(ni*nj*b3)]);
#endif
           //fprintf(fdt,"%d %f %f %f ",j1+i1*nj, u[j1+i1*nj],v[j1+i1*nj],h[j1+i1*nj]);
               // fprintf(fdt,"%f ",h[j1+i1*nj]);
        }     
        //printf("\n");   
        //fprintf(fdt,"\n");
      }
      fclose(fdt);


      //save file containing current data
      sprintf(configfile,"out/%s.out",name);
      printf("write out check dims %s %d %d \n",configfile ,ni,nj);
      fdt=fopen(configfile,"a+");
      fprintf(fdt,"%d\n",n);
     for( j1=(p.ng[1]);j1<(nj-(p.ng[1]));j1++)
      {
        for( i1=(p.ng[0]);i1<(nj-(p.ng[0]));i1++)
	{
               // printf("%d %d ", i1,j1);
 #ifdef ADIABHYDRO
 fprintf(fdt,"%d %d %f %f %f %f \n",i1,j1,w[(j1*ni+i1)+(ni*nj*rho)],w[(j1*ni+i1)+(ni*nj*mom1)],w[(j1*ni+i1)+(ni*nj*mom2)],w[j1*ni+i1+(ni*nj*energy)]);
#endif
#ifdef USE_SAC
fprintf(fdt,"%d %d %f %f %f %f %f %f\n",i1,j1,w[(j1*ni+i1)+(ni*nj*rho)],w[(j1*ni+i1)+(ni*nj*mom1)],w[(j1*ni+i1)+(ni*nj*mom2)],w[j1*ni+i1+(ni*nj*energy)],w[j1*ni+i1+(ni*nj*b1)],w[j1*ni+i1+(ni*nj*b2)]);
        #endif
#ifdef USE_SAC_3D
fprintf(fdt,"%d %d %f %f %f %f %f %f %f %f\n",i1,j1,w[(j1*ni+i1)+(ni*nj*rho)],w[(j1*ni+i1)+(ni*nj*mom1)],w[(j1*ni+i1)+(ni*nj*mom2)],w[j1*ni+i1+(ni*nj*mom3)],w[j1*ni+i1+(ni*nj*energy)],w[j1*ni+i1+(ni*nj*b1)],w[j1*ni+i1+(ni*nj*b2)],w[j1*ni+i1+(ni*nj*b3)]);
        #endif
		
           //fprintf(fdt,"%d %f %f %f ",j1+i1*nj, u[j1+i1*nj],v[j1+i1*nj],h[j1+i1*nj]);
               // fprintf(fdt,"%f ",h[j1+i1*nj]);
        }     
        //printf("\n");   
        //fprintf(fdt,"\n");
      }
      fclose(fdt);


  return status;
}



int writevacconfig(char *name,int n,params p, meta md, real *w, state st)
{
  int status=0;
  int i1,j1,k1,ifield;
  int ni,nj,nk;
  char configfile[300];
  char buffer[800];
  double dbuffer[12];
  int ibuffer[5];

  ni=p.n[0];
  nj=p.n[1];
    #ifdef USE_SAC_3D
  nk=p.n[2];
    #endif

      //save file containing current data
      sprintf(configfile,"out/%s_%d.out",name,st.it);
     // sprintf(configfile,"%s",name);
      printf("write vac check dims %d %d %d %lf\n",ni,nj,st.it,st.t);
      FILE *fdt=fopen(configfile,"w");

      fwrite(md.name,sizeof(char)*79,1,fdt);
      //*line2:
      //*   it          - timestep (integer)
      //*   t           - time     (real)
      //*   ndim        - dimensionality, negative sign for gen. coord (integer)
      //*   neqpar      - number of equation parameters (integer)
      //*   nw          - number of flow variables (integer)
      //sprintf(buffer,"%ld %lg %ld %ld %ld\n",st.it,st.t,3,4,8);
      //it,time,ndim,neqpar,nw
      printf("st.it=%d\n",st.it);
      ibuffer[0]=st.it;
      dbuffer[0]=st.t;
      //ibuffer[0]=1;
      //dbuffer[0]=10.98; st.it
      fwrite(ibuffer,sizeof(int),1,fdt);
      fwrite(dbuffer,sizeof(double),1,fdt);

    #ifdef USE_SAC
      ibuffer[0]=2;
      ibuffer[1]=6;
      ibuffer[2]=10;
   #endif
    #ifdef USE_SAC_3D
      ibuffer[0]=3;
      ibuffer[1]=7;
      ibuffer[2]=13;
    #endif
      fwrite(ibuffer,sizeof(int)*3,1,fdt);

      //line3:
      //*   nx()        - the grid dimensions      (ndim integers)
      //sprintf(buffer,"%ld %ld\n",ni,nj);
      ibuffer[0]=ni;
      ibuffer[1]=nj;
    #ifdef USE_SAC
      fwrite(ibuffer,sizeof(int)*2,1,fdt);
    #endif
    #ifdef USE_SAC_3D
      ibuffer[2]=nk;
      fwrite(ibuffer,sizeof(int)*3,1,fdt);
    #endif
      //*line4:
      //*   eqpar()     - equation parameters from filenameini (neqpar reals)
      //sprintf(buffer,"%lg %lg %lg %lg %lg %lg\n",p.gamma,p.eta,p.g[0],p.g[1],0,0);
      dbuffer[0]=p.gamma;
      dbuffer[1]=p.eta;
      dbuffer[2]=p.g[0];
      dbuffer[3]=p.g[1];

    #ifdef USE_SAC
      dbuffer[4]=0;
      dbuffer[5]=0;
     fwrite(dbuffer,sizeof(double)*6,1,fdt);
    #endif
    #ifdef USE_SAC_3D
      dbuffer[4]=p.g[2];
      dbuffer[5]=0;
      dbuffer[6]=0;
     fwrite(dbuffer,sizeof(double)*7,1,fdt);
    #endif
 

      //*line5:
      //*   varnames    - names of the coordinates, variables, equation parameters
      //*                 eg. 'x y rho mx my e bx by  gamma eta' (character*79)

    #ifdef USE_SAC_3D
      sprintf(buffer,"x y z rho mx my mz e bx by bz gamma eta g1 g2 g3");
    #else
      sprintf(buffer,"x y rho mx my mz e bx by bz gamma eta g1 g2 g3");
    #endif

      fwrite(buffer,sizeof(char)*79,1,fdt);

    #ifdef USE_SAC_3D
      for(ifield=0;ifield<16;ifield++)   
   #else
       for(ifield=0;ifield<12;ifield++)   
   #endif 

    #ifdef USE_SAC_3D
   for( k1=0;k1<nk;k1++)
    #endif
for( j1=0;j1<nj;j1++)
  
	{
//energyb,rhob,b1b,b2b         
       for( i1=0;i1<ni;i1++)     
      {
   
               if(ifield==0)
               dbuffer[0]=(p.xmin[0])+i1*p.dx[0];
               else if(ifield==1)
               dbuffer[0]=(p.xmin[1])+j1*p.dx[1];
    #ifdef USE_SAC_3D
               else if(ifield==2)
               dbuffer[0]=(p.xmin[2])+k1*p.dx[2];
    #endif
               else
    #ifdef USE_SAC_3D
                dbuffer[0]=w[(k1*ni*nj+j1*ni+i1)+(ni*nj*nk*(ifield-3))];
    #else
                dbuffer[0]=w[(j1*ni+i1)+(ni*nj*(ifield-2))];
    #endif

                fwrite(dbuffer,sizeof(double),1,fdt);		

        }     
      }
      buffer[0]='\n';
      fwrite(buffer,sizeof(char),1,fdt);
      fclose(fdt);

  return status;
}

/*Big problems with reading fortran unformatted "binary files" need to include 
  record field*/

int readbinvacconfig(char *name,params p, meta md, real *w, state st)
{
  int status=0;
  int i1,j1;
  int ni,nj;
  char configfile[300];
  char buffer[85];
  double dbuffer[12];
  int ibuffer[5];
  long lsize;
  size_t result;

  char *bigbuf;

  ni=p.n[0];
  nj=p.n[1];

      //save file containing current data
      //sprintf(configfile,"out/v%s.out",name);
      sprintf(configfile,"%s",name);
      printf("check dims %d %d \n",ni,nj);
      FILE *fdt=fopen(configfile,"r");


      fread(buffer,sizeof(char),80,fdt);
      for(i1=0;i1<81;i1++)
         putchar(buffer[i1]);
      printf("starting %s\n ",buffer);
      //*line2:
      //*   it          - timestep (integer)
      //*   t           - time     (real)
      //*   ndim        - dimensionality, negative sign for gen. coord (integer)
      //*   neqpar      - number of equation parameters (integer)
      //*   nw          - number of flow variables (integer)
      //sprintf(buffer,"%ld %lg %ld %ld %ld\n",st.it,st.t,3,4,8);
      //it,time,ndim,neqpar,nw

      fread(ibuffer,sizeof(int),1,fdt);
      fread(dbuffer,sizeof(double),1,fdt);
      st.it=ibuffer[0]=st.it;
      st.t=dbuffer[0]=st.t;
      printf("st.it=%f st.t=%d\n",st.it,st.t);


      //fread(ibuffer,sizeof(int)*3,1,fdt);

      //line3:
      //*   nx()        - the grid dimensions      (ndim integers)
      //sprintf(buffer,"%ld %ld\n",ni,nj);
      //fread(ibuffer,sizeof(int)*2,1,fdt);
      //ni=ibuffer[0];
      //nj=ibuffer[1];

      //*line4:
      //*   eqpar()     - equation parameters from filenameini (neqpar reals)
      //sprintf(buffer,"%lg %lg %lg %lg %lg %lg\n",p.gamma,p.eta,p.g[0],p.g[1],0,0);
      //fread(dbuffer,sizeof(double)*6,1,fdt);
      p.gamma=dbuffer[0];
      p.eta=dbuffer[1];
      p.g[0]=dbuffer[2];
      p.g[1]=dbuffer[3];
      printf("%f %f %f %f\n",dbuffer[0],dbuffer[1],dbuffer[2],dbuffer[3]);

      //*line5:
      //*   varnames    - names of the coordinates, variables, equation parameters
      //*                 eg. 'x y rho mx my e bx by  gamma eta' (character*79)
      sprintf(buffer,"x y rho mx my mz e bx by bz gamma eta g1 g2 g3\n");
      //fread(buffer,sizeof(char)*79,1,fdt);
         for( i1=0;i1<ni;i1++)   
	{
//energyb,rhob,b1b,b2b         
     
for( j1=0;j1<nj;j1++)  
      {


               // fread(dbuffer,12*sizeof(double),1,fdt);		
                //i1*p.dx[0]=dbuffer[0];
                //j1*p.dx[1]=dbuffer[1];
               //if(j1==2 || j1==3)
                //  printf("%d %d %d %d %lg\n", ni,nj,i1,j1,dbuffer[2]);
                w[(j1*ni+i1)+(ni*nj*rho)]=dbuffer[2];
                w[(j1*ni+i1)+(ni*nj*mom1)]=dbuffer[3];
                w[(j1*ni+i1)+(ni*nj*mom2)]=dbuffer[4];
                w[(j1*ni+i1)+(ni*nj*energy)]=dbuffer[5];
                w[(j1*ni+i1)+(ni*nj*b1)]=dbuffer[6];
                w[(j1*ni+i1)+(ni*nj*b2)]=dbuffer[7];
#ifndef ADIABHYDRO
                w[(j1*ni+i1)+(ni*nj*energyb)]=dbuffer[8];
                w[(j1*ni+i1)+(ni*nj*rhob)]=dbuffer[9];
                w[(j1*ni+i1)+(ni*nj*b1b)]=dbuffer[10];
                w[(j1*ni+i1)+(ni*nj*b2b)]=dbuffer[11];
#endif


        }     
      }
      fclose(fdt);
      free(bigbuf);
  return status;


}


int writevtkconfig(char *name,int n,params p, meta md, real *w)
{
  int status=0;
  int i1,j1,k1;
  int ni,nj,nk;
  char configfile[300];
  char labels[4][4]={"rho","e","mom","b"};
  int is;
  ni=p.n[0];
  nj=p.n[1];

#ifdef USE_SAC_3D

nk=p.n[2];
#endif


      //save file containing current data

      //scalar fields
//n+=10;
        #ifdef ADIABHYDRO
      for(int i=0,is=0; i<=3; i+=4)
      //for(int i=0; i<=4; i+=3)
       #else
      for(int i=0,is=0; i<=4; i+=4,is+=3)
      //for(int i=0; i<=4; i+=3)
        #endif
      {
	      if(n<=9)
                 sprintf(configfile,"vtk/%s%ss00%d.vtk",labels[i/4],name,n);
              else if(n<=99)
                 sprintf(configfile,"vtk/%s%ss0%d.vtk",labels[i/4],name,n);
              else
                 sprintf(configfile,"vtk/%s%ss%d.vtk",labels[i/4],name,n);

	      //printf("check dims %s %s %d %d \n",configfile,labels[i/4],ni,nj);
	      FILE *fdt=fopen(configfile,"w");


	      fprintf(fdt,"# vtk DataFile Version 2.0\n");
	      fprintf(fdt,"Structured Grid\n");
	      fprintf(fdt,"ASCII\n");
	      fprintf(fdt," \n");
	      fprintf(fdt,"DATASET RECTILINEAR_GRID\n");
#ifdef USE_SAC_3D
	      fprintf(fdt,"DIMENSIONS %d %d %d\n",ni,nj,nk);
#else
	      fprintf(fdt,"DIMENSIONS %d %d 1\n",ni,nj);
#endif


	      fprintf(fdt,"X_COORDINATES %d double\n",ni);
              for(i1=0;i1<ni;i1++)
	        fprintf(fdt,"%G\n",(p.xmin[0])+i1*p.dx[0]);

	      fprintf(fdt,"Y_COORDINATES %d double\n",nj);
              for(i1=0;i1<nj;i1++)
	        fprintf(fdt,"%G\n",(p.xmin[1])+i1*p.dx[1]);


   #ifdef USE_SAC_3D
	      fprintf(fdt,"Z_COORDINATES %d double\n",nk);
              for(k1=0;k1<nk;k1++)
	        fprintf(fdt,"%G\n",(p.xmin[2])+k1*p.dx[2]);

    #else
	      fprintf(fdt,"Z_COORDINATES 1 double\n");
	      fprintf(fdt,"0\n");
   #endif
   #ifdef USE_SAC_3D
	      fprintf(fdt,"POINT_DATA  %d\n",(ni)*(nj)*nk);
   #else

	      fprintf(fdt,"POINT_DATA  %d\n",(ni)*(nj));
    #endif

	      fprintf(fdt,"SCALARS %s double 1\n",labels[i/4]);

             fprintf(fdt,"LOOKUP_TABLE TableName \n");

   #ifdef USE_SAC_3D
	     for( k1=0;k1<(nk);k1++)
   #endif
	     for( j1=0;j1<(nj);j1++)
		for( i1=0;i1<(ni);i1++)
                {
                 if(is==0)
                    #ifdef USE_SAC_3D
			fprintf(fdt,"%G\n",w[(k1*ni*nj)+(j1*ni+i1)+(ni*nj*nk*is)]+w[(k1*ni*nj)+(j1*ni+i1)+(ni*nj*nk*8)]);
                    #else
			fprintf(fdt,"%G\n",w[(j1*ni+i1)+(ni*nj*is)]+w[(j1*ni+i1)+(ni*nj*7)]);
                    #endif
                 else
                    #ifdef USE_SAC_3D
			fprintf(fdt,"%G\n",w[(k1*ni*nj)+(j1*ni+i1)+(ni*nj*nk*is)]);
                    #else
			fprintf(fdt,"%G\n",w[(j1*ni+i1)+(ni*nj*is)]);
                    #endif

                }

	      fclose(fdt);
      }

      //vector fields
      int iv;
        #ifdef ADIABHYDRO
      for(int i=2; i<3; i++)
       #else
      for(int i=2; i<=3; i++)
        #endif

      {
	      if(i==2)
                iv=1;
              else
                //iv=5;
                iv=4;
              if(n<=9)
                 sprintf(configfile,"vtk/%s%ss00%d.vtk",labels[i],name,n);
              else if(n<=99)
                 sprintf(configfile,"vtk/%s%ss0%d.vtk",labels[i],name,n);
              else
                 sprintf(configfile,"vtk/%s%ss%d.vtk",labels[i],name,n);

	      //printf("check dims %s %s %d %d \n",configfile,labels[i],ni,nj);
	      FILE *fdt=fopen(configfile,"w");


	      fprintf(fdt,"# vtk DataFile Version 2.0\n");
	      fprintf(fdt,"Structured Grid\n");
	      fprintf(fdt,"ASCII\n");
	      fprintf(fdt," \n");
	      fprintf(fdt,"DATASET RECTILINEAR_GRID\n");
	      fprintf(fdt,"DIMENSIONS %d %d 1\n",ni,nj);


	      fprintf(fdt,"X_COORDINATES %d double\n",ni);
              for(i1=0;i1<ni;i1++)
	        fprintf(fdt,"%G\n",(p.xmin[0])+i1*p.dx[0]);

	      fprintf(fdt,"Y_COORDINATES %d double\n",nj);
              for(i1=0;i1<nj;i1++)
	        fprintf(fdt,"%G\n",(p.xmin[1])+i1*p.dx[1]);


               #ifdef USE_SAC_3D
	      fprintf(fdt,"Z_COORDINATES %d double\n",nk);
              for(i1=0;i1<nk;i1++)
	        fprintf(fdt,"%G\n",(p.xmin[2])+i1*p.dx[2]);
               #else
	      fprintf(fdt,"Z_COORDINATES 1 double\n");
	      fprintf(fdt,"0\n");
               #endif


             #ifdef USE_SAC_3D
	      fprintf(fdt,"POINT_DATA  %d\n",(ni)*(nj)*nk);
             #else
	      fprintf(fdt,"POINT_DATA  %d\n",(ni)*(nj));
             #endif
	      fprintf(fdt,"VECTORS %s double \n",labels[i]);

            #ifdef USE_SAC_3D
		for( k1=0;k1<(nk);k1++)
             #endif
		for( j1=0;j1<(nj);j1++)
	      		for( i1=0;i1<(ni);i1++)
   
            #ifdef USE_SAC_3D
                         fprintf(fdt,"%G %G %G\n",w[(k1*ni*nj)+(j1*ni+i1)+(ni*nk*nj*iv)],w[(k1*ni*nj)+(j1*ni+i1)+(ni*nk*nj*(iv+1))],w[(k1*ni*nj)+(j1*ni+i1)+(ni*nk*nj*(iv+2))]);
            #else
                         fprintf(fdt,"%G %G %G\n",w[(j1*ni+i1)+(ni*nj*iv)],w[(j1*ni+i1)+(ni*nj*(iv+1))]);
             #endif

                       //printing mag fields including backround for SAC
                       //if(iv==4)
                       //  fprintf(fdt,"%f %f %f\n",w[(j1*ni+i1)+(ni*nj*iv)]+w[(j1*ni+i1)+(ni*nj*(iv+4))],w[(j1*ni+i1)+(ni*nj*(iv+1))]+w[(j1*ni+i1)+(ni*nj*(iv+1+4))]);


	      fclose(fdt);
      }




  return status;
}



int readconfig(char *cfgfile, params p, meta md, real *w)
{
  int status=0;

  return status;
}


int readasciivacconfig(char *cfgfile, params p, meta md, real *w, char **hlines)
{
  int status=0;
  int i;
  int i1,j1;
  int ni,nj;
  int shift;
  real x,y,val;

   ni=p.n[0];
   nj=p.n[1];

   FILE *fdt=fopen(cfgfile,"r+");
   //char **hlines;
   char *line;
   //hlines=(char **)calloc(5, sizeof(char*));

   //read 5 header lines
   for(i=0;i<5;i++)
   {
     freadl(fdt, &hlines[i]);
     printf("%s\n", hlines[i]);
   }
  //fscanf(fdt,"%f",&val);
 //printf("%f",val);
for( j1=0;j1<(nj);j1++)
for( i1=0;i1<(ni);i1++)
   
	     
             {
                         shift=(j1*ni+i1);
                         fscanf(fdt,"%lG %lG %lG %lG %lG %lG %lG %lG %lG %lG %lG %lG\n",&x,&y,&w[shift],&w[shift+(ni*nj)],&w[shift+(ni*nj*2)],&w[shift+(ni*nj*3)],&w[shift+(ni*nj*4)],&w[shift+(ni*nj*5)],&w[shift+(ni*nj*6)],&w[shift+(ni*nj*7)],&w[shift+(ni*nj*8)],&w[shift+(ni*nj*9)]);
                         //freadl(fdt, &line);
                         /*for(i=0; i<NVAR;i++)
                         {
                            //fscanf(fdt,"%g",&);
                             //w[shift+(ni*nj*i)]=val;
                              printf("%lG ",w[shift+(ni*nj*i)]);
                         }*/
                         //fscanf(fdt,"\n");
                         //printf("\n");
              }


	      fclose(fdt);

  //free(hlines);
  return status;
}

int writeasciivacconfig(char *cfgfile, params p, meta md, real *w, char **hlines, state st)
{
  int status=0;
  int i;
  int i1,j1;
  int ni,nj;                         
  int shift;
  real x,y,val;

   ni=p.n[0];
   nj=p.n[1];

   FILE *fdt=fopen(cfgfile,"a+");
   //char **hlines;
   char *line;
   //hlines=(char **)calloc(5, sizeof(char*));

   //printf("here %s\n",hlines[0]);
   fprintf(fdt,"%s\n", hlines[0]);
   //read 5 header lines

      //*line2:
      //*   it          - timestep (integer)
      //*   t           - time     (real)
      //*   ndim        - dimensionality, negative sign for gen. coord (integer)
      //*   neqpar      - number of equation parameters (integer)
      //*   nw          - number of flow variables (integer)
      fprintf(fdt,"%d %d %d 6 %d\n", st.it,st.t,NDIM,NVAR);
   for(i=1;i<=4;i++)
   {
     fprintf(fdt,"%s\n", hlines[i]);
     printf("%s\n",hlines[i]);
    }

   for( j1=0;j1<(nj);j1++)
	     for( i1=0;i1<(nj);i1++)
             {
                         x=(1+i1)*(p.dx[0]);
                         y=(1+j1)*(p.dx[1]);
                         shift=(j1*ni+i1);
                         fprintf(fdt,"%lE %lE %lE %lE %lE %lE %lE %lE %lE %lE %lE %lE\n",x,y,w[shift],w[shift+(ni*nj)],w[shift+(ni*nj*2)],w[shift+(ni*nj*3)],w[shift+(ni*nj*4)],w[shift+(ni*nj*5)],w[shift+(ni*nj*6)],w[shift+(ni*nj*7)],w[shift+(ni*nj*8)],w[shift+(ni*nj*9)]);

              }


	      fclose(fdt);

  //free(hlines);
  return status;
}



