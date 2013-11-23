#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#define TOP_VIEWP       12
#define BOTTOM_VIEWP   212
#define LEFT_VIEWP     100
#define RIGHT_VIEWP    300
#define CLIP_PLEASE      1
#define NOCLIP_PLEASE    0

main()
  {
  int graphdriver;
  int graphmode;
  int g_errorcode;

  graphdriver = DETECT;
  initgraph(&graphdriver,&graphmode,"D:\\TC\\BGI");
  g_errorcode = graphresult(); 
  if (g_errorcode != grOk)
    {
    printf("Graphics error: %s\n",grapherrormsg(g_errorcode));


    exit(1);
    }
  else
    {
    outtextxy(10,10,"hi there from graphx!");
    setcolor(RED);

    rectangle(LEFT_VIEWP,TOP_VIEWP,RIGHT_VIEWP,BOTTOM_VIEWP);
    setviewport(LEFT_VIEWP,TOP_VIEWP,RIGHT_VIEWP,BOTTOM_VIEWP,CLIP_PLEASE);

    setfillstyle(SOLID_FILL,YELLOW);

    pieslice(150,150,0,360,100);
    getchar();

    }
  closegraph();
  }
