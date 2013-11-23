#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include <mem.h>




const long 
   IMAGE_SIZE=64000;

int
   infile;           /* file handle for pcx file... */

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

extern "C" void VGAm        (unsigned int modeval);
extern "C" void clrs        (char far     *screen,
                             unsigned int  val     );
extern "C" void SetPalette  (char far *color_regs);

           void sec_delay   (unsigned int seconds);
           int  load_image  (int pcxfile,
                             pcx_struct far *pcx);
           void load_palette(int pcxfile,
                             pcx_struct far *pcx);
           int load_PCX     (char far *filename, 
                             pcx_struct far *pcx);
           int compress     (pcx_struct far *pcx);


pcx_struct pcx_buf;  /* buffer for pcx data */

int main(int argc,char *argv[])
   {
   unsigned int 
      color,
      clrval,  /* value to clear screen with */
      oldmode;
   long
      i;
   char far 
      *screen;

   if (argc != 2)
      {
      puts("oops... wrong number of arguments");
      exit(0);
      }
   if (load_PCX(argv[1],&pcx_buf))
      {
      exit(0);
      }

   /* get old vga mode and remember it.. */
   oldmode = *(int *)MK_FP(0x40,0x49);
   screen = (char far *)MK_FP(0xA000,0);

   /* set up new vga mode */
   VGAm(0x13);

   clrval = 0;
   clrs(screen,
        clrval);
   SetPalette((char far *)&pcx_buf.palette);

   for (i=0;i<64000;i++)
      screen[i]=pcx_buf.image[i];

   while(!kbhit());

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
   if( (pcx->header.xmin != 0  ) ||
       (pcx->header.xmax != 319) ||
       (pcx->header.ymin != 0  ) ||
       (pcx->header.ymax != 199)    )
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
            if((readlen=read(pcxfile,buffer,BUFLEN))==0)
               break;
            }
         outbyte=buffer[bufptr++];
         if(outbyte>0xbf)
            {
            bytecount=(int)( (int)outbyte & 0x3f );
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