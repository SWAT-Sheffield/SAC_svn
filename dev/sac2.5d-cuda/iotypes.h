#ifndef TYPES_H_
#define TYPES_H_


struct Meta {
   char *directory ;
   char *author;
   char *sdate;
   char *platform;
   char *desc;
   char *name;
};

struct Iome {
    char *server;
    int port;
    int id;
};

struct params {
	int ni;
 	int nj;

        float xmax;
        float ymax;
	int nt;
        float tmax;

        int steeringenabled;
        int finishsteering;     
	float dt;
        float dx;
        float dy;
        float g;
        float gamma;
        float mu;
        float eta;
        float g1;
        float g2;
        float g3;       
};

struct hydrovars{
    int numvars; //variables each vector component
	int num;   //total number of dimensions including any ghost variables
	float *w;

};



typedef enum vars {rho, mom1, mom2, mom3, energy, b1, b2, b3} CEV;
typedef enum dvars {current1,current2,current3,pressuret,pressurek,bdotv} DEV;

typedef struct Source source;
typedef struct Constants constants;
typedef struct Domain domain;
typedef struct Iome iome;
typedef struct Meta meta;

#endif

