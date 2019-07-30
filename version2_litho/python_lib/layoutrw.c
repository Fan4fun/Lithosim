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
int lvlcnt1;

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
      

     ////////////////////////////
     lvlcnt1  = lvlcnt[MAXLVL-1];
     rectdata = lvldata[MAXLVL-1];
     ////////////////////////////
     //lvldata is a pointer type struct, i dont know what it is
     //devdata is rect type struct.
     // fprintf(stderr,"%d %d\n" ,urx,ury);

     // for (int i=0;i<lvlcnt1;i++) 
     // {

     // fprintf(stderr,"%d\n",rectdata[i].x );
     // fprintf(stderr,"%d\n",rectdata[i].y );
     // fprintf(stderr,"%d\n",rectdata[i].w );
     // fprintf(stderr,"%d\n",rectdata[i].h ); 
     // }
     

}


void create_csv(char *filename) {
  //TI_TN;

  FILE *fp;
  fprintf(stderr,"\n Creating %s.csv file",filename);
  filename=strcat(filename,".csv");
  fp=fopen(filename,"w+");
  fprintf(fp,"or_x,or_y,height,width");

  int i;
  int x;
  int y;
  int c =255;
  int nx =2048; 
  int ny=2048;
  int ox=0;
  int oy=0;
  int sc=1;


  for( i = 0; i<lvlcnt1; i++) {
    rect r = rectdata[i];
    int x0 = (r.x / sc - ox);
    int y0 = (r.y / sc - oy);
    int x1 = x0 + r.w / sc + 1;
    int y1 = y0 + r.h / sc + 1;
    printf("lvlcnt = %d",i);
    fprintf(stderr,"nx=%d, ny=%d\n",nx,ny);
    fprintf(stderr,"Read rectangle (%d,%d) to (%d,%d)\n",x0,y0,x1,y1);
    fprintf(fp,"\n%d,%d,%d,%d",x0,y0,x1,y1);
    // int p = (x1 < 0) || (x0 >= nx) || (y1 < 0) || (y0 >= ny);
    // if (!p) {
    //   for( x = myMax(0,x0) ; x<myMin(nx-1,x1); x++) 
    //   {
    //     for( y = myMax(0,y0); y<myMin(ny-1,y1); y++) 
    //     {
    //       //imgpbo[nx*y + x] = c;
    //       fprintf(fp,"\n%d,%d,%d,%d",x0,y0,x1,y1);
    //     }
    //   }
    // }
    /*else { fprintf(stderr,"Error: Rectangle (%d, %d) to (%d,%d) out of bounds!\n",x0,y0,x1,y1); exit(0); }*/
  }
  fclose(fp);

printf("\n %sfile created",filename);
}



   




