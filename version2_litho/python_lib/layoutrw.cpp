#include "glpParse.h"
#include "agsUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXLVL 1
#define myMin(a,b) ((a)<=(b) ? (a) : (b))
#define myMax(a,b) ((a)<=(b) ? (b) : (a))

int lvlcnt[MAXLVL];

typedef struct {
  int x,y,w,h;
} rect;


rect *lvldata[MAXLVL];
rect *d_lvldata[MAXLVL];
rect *rectdata;
int nlvl = 0;

int *devdata[MAXLVL];
int llx =  1000000000;
int lly =  1000000000;
int urx = -1000000000;
int ury = -1000000000;

int rctr = 0;
int ef_xoff = 0;
int ef_yoff = 0;

int min(int a, int b) {
	return ((a<b)?a:b);
}

int max(int a, int b) {
	return ((a>b)?a:b);
}

int ercnt(char *l,int x, int y, int w, int h) {
  int i = agsIntern(l);
  lvlcnt[i]++;
  llx = min(x,llx);
  lly = min(y,lly);
  urx = max(x+w,urx);
  ury = max(y+h,ury);
  rctr++;
  return 1;
}

int erfill(char *l,int x, int y, int w, int h) {
  int i = agsIntern(l);
  int j = lvlcnt[i];
  rect *r = lvldata[i]+j;
  r->x = x + ef_xoff;
  r->y = y + ef_yoff;
  r->w = w;
  r->h = h;
  llx = min(r->x,llx);
  lly = min(r->y,lly);
  urx = max(r->x+w,urx);
  ury = max(r->y+h,ury);
  lvlcnt[i]++;
  return 1;
}

void clear_design_space()
{
  int i;
  for(i=0;i<nlvl;i++)  { free(lvldata[i]); lvlcnt[i]=0; }   /* Clear up the design space */
  llx = lly =  10000000;//start point
  urx = ury = -10000000;// end points
}

// This function reads in a file in GULP form and stores it as rectangles
void read_layout(char* fname)
{
     fprintf(stderr, "First pass counting\n"); glpParseFileRect(fname, ercnt); nlvl = agsInternCnt();
     fprintf(stderr,"%d layers parsed\n", nlvl);
     int j;
     for(j=0;j<MAXLVL;j++) {
       lvldata[j]=NULL;
       if (lvlcnt[j]>0) { fprintf(stderr, "Level %s (%d) count = %d\n", agsUnintern(j),j,lvlcnt[j]); 
       lvldata[j] = malloc(lvlcnt[j] * sizeof(rect)); 
       //rect r = lvldata[j];

       lvlcnt[j] = 0;}
     }
     fprintf(stderr, "Second pass filling\n"); ef_xoff = -llx; ef_yoff = -lly;
     llx = lly =  10000000; urx = ury = -10000000;
     glpParseFileRect(fname, erfill);
     fprintf(stderr,"Adjusted bounding box	(%5d,%d) -> (%d,%d)\n", llx, lly, urx, ury);
     rectdata = lvldata[MAXLVL-1];
     //lvldata is a pointer type struct, i dont know what it is
     //devdata is rect type struct.
     fprintf(stderr,"%d %d\n" ,urx,ury);
     fprintf(stderr,"%d\n",rectdata[1].x );
     fprintf(stderr,"%d\n",rectdata[1].y );
     fprintf(stderr,"%d\n",rectdata[1].w );
     fprintf(stderr,"%d\n",rectdata[1].h );
     //return devdata;
     /////////////////////////////////////////////////////////////
      //TI_TN;
   

}




