#include "iotypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int createlog(char *logfile);
int appendlog(char *logfile, params p, state s);
int writeconfig(char *name,int n,params p, meta md, real *w);
int writevtkconfig(char *name,int n,params p, meta md, real *w);
int writevacconfig(char *name,int n,params p, meta md, real *w, state st);
int readconfig(char *cfgfile, params p, meta md, real *w);
int readasciivacconfig(char *cfgfile, params p, meta md, real *w, char **hlines);
int writeasciivacconfig(char *cfgfile, params p, meta md, real *w, char **hlines, state st);
