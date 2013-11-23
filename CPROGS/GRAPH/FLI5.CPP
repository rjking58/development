#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include <mem.h>




const long 
   IMAGE_SIZE=64000,
   SCREEN_SIZE=64000;

const int 
   SCREEN_WIDTH=320,
   SCREEN_HEIGHT=200,
   
   NUM_OF_SPRITES=4,
   SPRITE_WIDTH=24,
   SPRITE_HEIGHT=24;
const long 
   DELAY=400000;   

   
int
   infile;           /* file handle for pcx file... */


struct sprite_struc
   {
   unsigned char far ** image;      // sprite images
   unsigned char far * savebuffer;  //background save area.
   int width,     // width and height of the goddamn thing
       height;
   int xsprite,         // current x/y coordinates of the goddamn thing
       ysprite;
   }  ;



struct pcx_header
   {
   char manufacturer;
   char version;
   char encoding;
   char bits_per_pixel;
   int  xmin,ymin;
   int  xmax,ymax;
   int  hres;
   int  vres;
   char palette16[48];
   char reserved;
   char color_planes;
   int  bytes_per_line;
   int  palette_type;
   char filler[58];
   };

struct pcx_struct
   {
   pcx_header header;
   unsigned char far *image;     /* image */
   unsigned char far *cimage;    /* compressed image */
   unsigned char palette[3*256]; /* palette for this baby */
   int clength;                  /* length of compressed puppy. */
   };

/* function prototypes... */

/* all assembler functions must be declared as 'extern "C"' to 
   avoid problems with function name matching by the linker!!   */

extern "C" void VGAm          (unsigned int modeval);
extern "C" void clrs          (unsigned char far     *screen,
                               unsigned int  val     );
extern "C" void SetPalette    (char far *color_regs);
extern "C" void slam_sprite   (char far * sprite_addr,
                               char far * savebuf,
                               char far * screenb,
                               unsigned int lines,
                               unsigned int width);
extern "C" void scrn_updt     (unsigned char far *l_screenbuf,
                               unsigned char far *l_screen,
                               unsigned int bytes_to_move);
extern "C" void zap_sprite    (unsigned char far * zs_saved_background,
                               unsigned char far * zs_screenb,
                               int zs_lines,
                               int zs_width);
                              
           void sec_delay     (unsigned int seconds);
           int  load_image    (int pcxfile,
                               pcx_struct far *pcx);
           void load_palette  (int pcxfile,
                               pcx_struct far *pcx);
           int load_PCX       (char far *filename, 
                               pcx_struct far *pcx);
           int compress       (pcx_struct far *pcx);
           void putbuffer     (unsigned char far *,
                               int y1,
                               int height); // move screen buffer to vram
           int allocate_sprite(int number_of_sprites,
                               int w, 
                               int h                 );
           int grab_sprite    (unsigned char far * buffer,
                               sprite_struc * sprite,
                               int sprite_num,
                               int x1,
                               int y1                       ) ;                                       
           void draw_sprite   (sprite_struc * sprite,
                               int sprite_num, 
                               int x, 
                               int y,
                               unsigned char far * screenb);
           void erase_sprite  (sprite_struc * sprite,
                               unsigned char far *screenb);


pcx_struct    pcx_buf,bg;  /* buffer for pcx data           */
sprite_struc  sprite1;     /* a sprite (a goddamn sprite)   */
char far     *screen;      /* duh... */
char far     *screen_buf;  /* off screen buffer */

int walk_sequence[]={0,1,2,1};   /* sequence of images for walking sprite */

void main(void)
   {
   unsigned int 
      i,       // just a temp...
      j,
      color,
      clrval,  /* value to clear screen with */
      oldmode;
//   long
//      i;
   long
      d;


   if (load_PCX("walkman.pcx",&pcx_buf))
      {
      exit(0);
      }
   if (load_PCX("walkbg.pcx",&bg))
      {
      exit(0);
      }

   /* initialize the sprite... */
   allocate_sprite(NUM_OF_SPRITES,
                   SPRITE_WIDTH,
                   SPRITE_HEIGHT);   

   /* get old vga mode and remember it.. */
   oldmode = *(int *)MK_FP(0x40,0x49);
   screen = (char far *)MK_FP(0xA000,0);
   
   screen_buf = (unsigned char far *)malloc(SCREEN_SIZE);

   /* set up new vga mode */
   VGAm(0x13);

   clrval = 0;
   // clear the screen
   clrs(screen,
        clrval);
   // setup our palette        
   SetPalette((char far *)&pcx_buf.palette);

   memmove(screen_buf,bg.image,SCREEN_SIZE);
   putbuffer(screen_buf,0,SCREEN_HEIGHT);

   for (i=0; i<3; i++)
      grab_sprite(pcx_buf.image,
                  &sprite1,
                  i,
                  i*SPRITE_WIDTH+3*24,
                  0);

   for(;;)
      {
      for (j=0;j<15;j++)
         {
         for(i=0;i<4;i++)
            {
            draw_sprite(&sprite1,walk_sequence[i],j*20+i*5,100,screen_buf);
            putbuffer(screen_buf,100,SPRITE_HEIGHT);

//            for(d=0; d<DELAY; d++)
//               ;
            erase_sprite(&sprite1,screen_buf);
            if(kbhit())    
               break;            
            }
         if(kbhit()) 
            break;            
         }
      if(kbhit())    
         break;            
      }      
//   while(!kbhit());
  
   /* set back old mode */
   VGAm(oldmode);
   /* outta here */
   }

int load_PCX(char far *filename, pcx_struct far *pcx)
   {
   int
      readlen;

   /* open the puppy up */
   if ((infile=open(filename,O_BINARY))==-1)
      {
      puts("cannot find specified file");
      return(-1);
      }
   lseek(infile,0L,SEEK_SET);
   readlen = read(infile             ,
                  &(pcx->header)     ,   
                  sizeof(pcx_header)   );
   if( (pcx->header.xmin != 0                ) ||
       (pcx->header.xmax != (SCREEN_WIDTH-1) ) ||
       (pcx->header.ymin != 0                ) ||
       (pcx->header.ymax != (SCREEN_HEIGHT-1))   )
      {
      puts("bad pcx file");
      return(-1);
      }

      
   if (load_image(infile,pcx))
      return(-1);
   load_palette(infile,pcx);
   close(infile);
   if (compress(pcx))
      return(-1);
   return(0);
   }

int load_image(int pcxfile,pcx_struct far *pcx)
   {
   const int 
      BYTEMODE = 0,
      RUNMODE  = 1;
   long
      i;                      // image byte counter

   const int BUFLEN=5 * 1024; // nominal size of buffer.
   int mode = BYTEMODE;       // default start on bytemode

   int readlen ,              // size of block that was just read.
       bufptr  ;              // pointer into read buffer.
         
   unsigned char far *image_ptr;  // update-able image pointer

   static unsigned char outbyte         , //next byte for buffer
                        bytecount       , //counter for byte runs
                        buffer [BUFLEN] ; // size of read buffer.

   pcx->image= (unsigned char far *)malloc(IMAGE_SIZE*sizeof(char));
   if (pcx->image==NULL)
      {
      puts("not enough memory in load_image");
      return(-1);
      }
   bufptr=0;
   readlen=0;
   
   image_ptr=pcx->image;

   for (i=0;i<IMAGE_SIZE;i++)
      {
      if (mode==BYTEMODE)
         {
         if(bufptr>=readlen)
            {
            bufptr=0;
            // read until no more blocks available from file...
            if((readlen=read(pcxfile,buffer,BUFLEN))==0)
               break;
            }
         outbyte=buffer[bufptr++];
         if(outbyte>0xbf) // bf hex =  191 decimal = 1011 1111 binary
                          // looking for number 1100 0000 or greater...
            {
            bytecount=(int)( (int)outbyte & 0x3f ); // 0x3f = 0011 1111 duh...
            if(bufptr>=readlen)
               {
               bufptr=0;
               if((readlen=read(pcxfile,buffer,BUFLEN))==0)
                  break;
               }
            outbyte=buffer[bufptr++];
            if(--bytecount>0)
               mode=RUNMODE;
            }

         } else if (--bytecount==0)
            mode=BYTEMODE;
         *image_ptr=outbyte;
         image_ptr++;
      }
   return(0);
   }
void load_palette(int pcxfile,
                  pcx_struct far *pcx)
   {
   int
      i,j;

   lseek(pcxfile,-768L,SEEK_END);
   read(pcxfile,pcx->palette,3*256);
   for ( i=0 ; i<256 ; i++ )
      for( j=0 ; j<3 ; j++ )
         pcx->palette[i*3+j]=pcx->palette[i*3+j]>>2;
   }

int compress(pcx_struct far *pcx)
   {
   int
      value,
      runlength,
      runptr;

   unsigned char far
      *cbuffer;

   long ptr=0;    // long offset into PCX->IMAGE
   long cptr=0;   // long offset into PCX->CIMAGE

   // get block to mess with for the compression...
   cbuffer = (unsigned char far *)malloc(65530*sizeof(char));
   if (cbuffer==NULL)
      {
      puts("bad memory allocate in compress");
      return(-1);
      }
   while (ptr<IMAGE_SIZE)
      {
      if(pcx->image[ptr]==0)
         {
         runlength=0;
         while(pcx->image[ptr]==0)
            {
            ptr++;
            runlength++;
            if ( runlength>=127 )
               break;
            if( ptr>= IMAGE_SIZE )
               break;
            }
          cbuffer[cptr]=(unsigned char) (runlength | 0x80);
          cptr++;
          cbuffer[cptr]=0;
          cptr++;
         }
      else
         {
         runlength=0;
         runptr=cptr++;
         while (pcx->image[ptr] != 0)
            {
            cbuffer[cptr]=pcx->image[ptr];
            cptr++;
            ptr++;
            runlength++;
            if (runlength>=127)
               break;
            if (ptr >= IMAGE_SIZE)
               break;
            }
         cbuffer[runptr]=runlength;
         }
      }
      pcx->cimage = (unsigned char far *)malloc(cptr * sizeof(char));
      if (pcx->cimage == NULL)
         {
         puts("bad cimage allocate");
         return(-1);
         }
      memcpy(pcx->cimage,cbuffer,cptr);
      free( (void *) cbuffer);
      pcx->clength=cptr;
      return(0);
   }

int allocate_sprite(int number_of_sprites,int w,int h)
   {
   // make a pointer to pointers
   sprite1.image = 
      (unsigned char far **)malloc(sizeof(void far * )*number_of_sprites); 
   if (sprite1.image == NULL)
      {
      puts("bad sprite allocate");
      return(-1);
      }
   sprite1.savebuffer = 
      (unsigned char far *)malloc(sizeof(char)*w*h); 
   sprite1.width = w;
   sprite1.height = h;   
   return(0);
   }

void draw_sprite(sprite_struc * sprite,int sprite_num, int x, int y,unsigned char far * screenb)
   {
   char far * screenbo; // its the screen buffer offset... jimbo
   
//   screenbo = (char far *) MK_FP(FP_SEG(screenb),
//                                 FP_OFF(screenb) + ((y*SCREEN_WIDTH)+x));
   screenbo = screenb + (y*SCREEN_WIDTH)+x;

   slam_sprite   (sprite->image[sprite_num],
                  sprite->savebuffer,
                  screenbo,
                  sprite->height,
                  sprite->width);

                  
//   for (row = 0 ; row < sprite->height; row++)
//      {
//      for (column=0 ; column < sprite->width ; column ++)
//         {
//         sprite->savebuffer[soffset] = screenb[poffset];
//         pixel = sprite->image[sprite_num][soffset];
//         if(pixel)
//            screenb[poffset]=pixel;
//         soffset++;
//         poffset++;   
//         }
//      poffset += (SCREEN_WIDTH - sprite->width);   
//      }
//   sprite->xsprite = x;
//   sprite->ysprite = y;


//   int 
//      row,
//      column,
//      pixel,
//      soffset, // sprite offset
//      poffset; // pixel offset
//
//   poffset = (y*SCREEN_WIDTH)+x;
//   soffset = 0;
//   
//
//   for (row = 0 ; row < sprite->height; row++)
//      {
//      for (column=0 ; column < sprite->width ; column ++)
//         {
//         sprite->savebuffer[soffset] = screenb[poffset];
//         pixel = sprite->image[sprite_num][soffset];
//         if(pixel)
//            screenb[poffset]=pixel;
//         soffset++;
//         poffset++;   
//         }
//      poffset += (SCREEN_WIDTH - sprite->width);   
//      }
   sprite->xsprite = x;
   sprite->ysprite = y;   
   }   
   
void erase_sprite(sprite_struc * sprite,unsigned char far *screenb)
   {
   unsigned char far * screenbo;
   int 
      soffset, // sprite offset
      poffset; // pixel offset

   screenbo= screenb + (sprite->ysprite*SCREEN_WIDTH)+sprite->xsprite;
   zap_sprite(sprite->savebuffer,
              screenbo,
              sprite->height,
              sprite->width);

//   for (row = 0 ; row < sprite->height; row++)
//      {
//      for (column=0 ; column < sprite->width ; column ++)
//         {
//         screenb[poffset]=sprite->savebuffer[soffset];
//         soffset++;
//         poffset++;   
//         }
//      poffset += (SCREEN_WIDTH - sprite->width);   
//      }
   }   

int grab_sprite(unsigned char far * buffer,
                 sprite_struc * sprite,
                 int sprite_num,
                 int x1,
                 int y1                       )
   {
   int
      row,
      column;
      
   sprite->image[sprite_num] = 
      (unsigned char far *)malloc((sprite->width) * (sprite->height));
   if (sprite->image[sprite_num] == NULL)
      {
      puts("bad grab_sprite image allocate");
      return(-1);
      }      
   if (    (x1 + sprite->width > SCREEN_WIDTH) 
        || (y1 + sprite->height > SCREEN_HEIGHT))  
      {
      puts("vectored off screen!!!");
      return(-1);
      }      
   for (row = 0 ; row < sprite->height; row++)
      {
      for (column=0 ; column < sprite->width ; column ++)
         {
         sprite->image[sprite_num][row*sprite->width+column]=
            buffer[(y1+row)*SCREEN_WIDTH+x1+column];           
         }
      }
   return(0);
   }                    
   
void putbuffer(unsigned char far * screenbuf,   
               int y1,
               int height )
   {
   unsigned char far *l_screenbuf,
                     *l_screen;
   int               bytes_to_move;

   l_screenbuf = screenbuf + y1*SCREEN_WIDTH;
   l_screen = screen + y1*SCREEN_WIDTH      ;
   bytes_to_move = SCREEN_WIDTH*height;

   scrn_updt(l_screenbuf,
             l_screen,
             bytes_to_move);

//   memmove(screen+ y1*SCREEN_WIDTH,
//           screenbuf+y1*SCREEN_WIDTH,
//           height*SCREEN_WIDTH);
   }               
   
void sec_delay(unsigned int seconds)
   {
   time_t
      tnow;
   struct tm
      *tm_p;
   unsigned int
      then_hour,
      then_min,
      then_sec,
      x,
      delay;

   delay = seconds + 1;
   for(x=1;x<delay;x++)
      {
      time(&tnow);
      tm_p = localtime(&tnow);
      then_hour = tm_p->tm_hour;
      then_min   = tm_p->tm_min;
      then_sec  = tm_p->tm_sec;
      do
         {
         time(&tnow);
         tm_p = localtime(&tnow);
         }
      while ( (tm_p->tm_hour == then_hour) &&
              (tm_p->tm_min  == then_min ) &&
              (tm_p->tm_sec  == then_sec )    );
      }

   }

