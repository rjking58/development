#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
 


extern "C" void VGAm          (unsigned int modeval);
extern "C" void clrs          (unsigned char far     *screen,
                               unsigned int  val     );

void linedraw(int x1, int y1, int x2, int y2, int color, char far * screen);
extern "C" void linedraw_asm( int x1, 
                              int y1, 
                              int x2, 
                              int y2, 
                              int color, 
                              char far * screen);

void gac(void);

const COLOR=15;


char far     *screen;      /* duh... */
unsigned int oldmode;

void main()
{
   int x1,x2,y1,y2,color;

   randomize();

   oldmode = *(int *)MK_FP(0x40,0x49);
   screen = (char far *)MK_FP(0xA000,0);

   clrs(screen,0);
   /* set up new vga mode */
   VGAm(0x13);

   x1 = random(320);
   y1 = random(200);

   for (x1=0;x1<320;x1++)
   {
      y1=0;
      y2=199;
      x2=x1;
      color = 20;
      linedraw_asm(x1, y1, x2, y2,color , screen);
   }
   gac();
   for (x1=0;x1<320;x1++)
   {
      y1=199;
      y2=0;
      x2=x1;
      color = 40;
      linedraw_asm(x1, y1, x2, y2,color , screen);
   }
   gac();
   for (y1=0;y1<200;y1++)
   {
      x1=0;
      x2=320;
      y2=y1;
      color = 80;
      linedraw_asm(x1, y1, x2, y2,color , screen);
   }
   gac();
   for (y1=0;y1<200;y1++)
   {
      x1=320;
      x2=0;
      y2=y1;
      color = 100;
      linedraw_asm(x1, y1, x2, y2,color , screen);
   }
   gac();
   for (x1=1;x1<320;x1++)
   {
      y1 = 0;
      x2 = 0;
//      gac();
      for (y2 = 1; y2<200; y2++)
      {
         color = 150;
         linedraw_asm(x1, y1, x2, y2,color , screen);
      }
   }
   gac();
   for (x2=1;x2<320;x2++)
   {
      y2 = 0;
      x1 = 0;
      for (y1 = 1; y1<200; y1++)
      {
         color = 200;
         linedraw_asm(x1, y1, x2, y2,color , screen);
      }
   }
   gac();
   VGAm(oldmode);
}

// x_unit          DW      1
// y_unit          DW      1
// offset          DW      1
// y_diff          DW      1
// x_diff          DW      1
// error_term      DW      1
// length          DW      1
// i               DW      1

//                 PUBLIC  _linedraw
// _linedraw       PROC    FAR
//                 ARG     x1:WORD
//                 ARG     y1:WORD
//                 ARG     x2:WORD
//                 ARG     y2:WORD
//                 ARG     color:BYTE
//                 ARG     screen:DWORD
//                 push    bp
//                 mov     bp,sp
//                 push    es              ;save em off to allay a C barf
//                 push    di
//                 push    ax
//                 push    bx
//                 push    cx
//                 push    dx
//                 les     di,screen       ;get passed address from C prog


void linedraw(int x1, int y1, int x2, int y2, int color, char far * screen)
   {
   int y_unit, 
       x_unit;

   unsigned int offset = y1 * 320 + x1;
//
//    mov   bx,320
//    mov   ax,y1
//    mul   bx
//    add   ax,x1    ;add em..
//    mov   offset,ax

   int ydiff = y2-y1;

//    mov   y_unit,320

//    mov   ax,y2
//    sub   ax,y1
//    jc    ld2      ;go to negative result
//                   ; else.. positive...
//    mov   ydiff,ax
//    jmp   ld3
// ld2:              ; negative result logic
//    neg   ax
//    mov   ydiff,ax
//    neg   y_unit
// ld3:


   int xdiff = x2-x1;
//    mov   x_unit,1

//    mov   ax,x2
//    sub   ax,x1
//    jc    ld4      ;go to negative result
//                   ; else.. positive...
//    mov   xdiff,ax
//    jmp   ld5
// ld4:              ; negative result logic
//    neg   ax
//    mov   xdiff,ax
//    neg   x_unit
// ld5:

   int error_term = 0;
   int length,
       i;

   if (ydiff < 0)
      {
      ydiff = -ydiff;
      y_unit = -320;
      }
   else
      {
      y_unit = 320;
      }
   if (xdiff < 0)
      {
      xdiff = -xdiff;
      x_unit = -1;
      }
   else
      {
      x_unit = 1;
      }
//       mov   ax,xdiff
//       cmp   ax,ydiff
//       jc    ld6            ;xdiff < ydiff!

//       mov   bx,offset
//       mov   cl,color       ;
//       mov   dx,xdiff       ;length = xdiff + 1  (dx)
//       inc   dx
// xdg_loop:
//       mov   es:[bx + di],cl   ;screen[offset] = color
//       add   bx,x_unit         ; offset += x_unit
//       mov   ax,error_term     ; error_term += ydiff
//       add   ax,ydiff          
//       cmp   ax,xdiff          ; error_term > xdiff ?
//       jle   xdg_loop2         ; take if no.
//       sub   ax,xdiff          ; yup... error_term -= xdiff
//       add   bx,y_unit         ; offset += y_unit
// xdg_loop2:
//       mov   error_term,ax     ; save off error_term...
//       dec   dx
//       jnz   xdg_loop
//       jmp   bresh_out
   if (xdiff > ydiff)
      {
      length = xdiff+1;
      for (i = 0; i< length; i++)
         {
         screen[offset] = color;
         offset += x_unit;
         error_term += ydiff;
         if (error_term >= xdiff)
            {
            error_term -= xdiff;
            offset += y_unit;
            }
         }
      }
   else
      {
//       mov   bx,offset
//       mov   cl,color       ;
//       mov   dx,ydiff       ;length = ydiff + 1  (dx)
//       inc   dx
// xdg_loop:
//       mov   es:[bx + di],cl   ;screen[offset] = color
//       add   bx,y_unit         ; offset += y_unit
//       mov   ax,error_term     ; error_term += xdiff
//       add   ax,xdiff          
//       cmp   ax,ydiff          ; error_term > ydiff ?
//       jle   xdg_loop3         ; take if no.
//       sub   ax,ydiff          ; yup... error_term -= ydiff
//       add   bx,x_unit         ; offset += x_unit
// xdg_loop3:
//       mov   error_term,ax     ; save off error_term...
//       dec   dx
//       jnz   xdg_loop
      length = ydiff + 1;
      for (i = 0; i<length ; i++)
         {
         screen[offset] = color;
         offset += y_unit;
         error_term += xdiff;
         if(error_term >= ydiff)
            {
            error_term -= ydiff;
            offset += x_unit;
            }
         }
      }
   }
// bresh_out:
//                 pop     dx
//                 pop     cx
//                 pop     bx
//                 pop     ax
//                 pop     di
//                 pop     es
//                 pop     bp
//                 ret                     
//_linedraw        ENDP

void gac(void)
{
   int cin;

   cin = getch();
   if (cin =='a' || cin =='A' )
   {
      VGAm(oldmode);
      exit(0);
   }
}
