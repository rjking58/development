#include <dos.h>
#include <stdio.h>
#include <usrlib.h>

void init_harderror();
int do_harderror();

char he_window[4]; /* Window to display message in */
char he_style;     /* Box style */
char he_bclr;      /* box color */
char *he_btxt;     /* Box string */
char he_tclr;      /* Box text color */
char he_mhiclr;    /* Menu Hi color  */
char he_mloclr;    /* Menu low color */

#if 1

main()
  {
  int i;
  FILE *in;
  init_harderror(10,10,2,15,"Critical Error",7,112,15);
  in = fopen("abc","w");
  printf("\nin = %p\n",in);
  if(in == NULL)
    {
    exit(0);
    }
  fprintf(in,"ABC\n");
  printf("Done1\n");
  fclose(in);
  printf("Done2\n");
  }
#endif

void init_harderror(tr,tc,style,bclr,btxt,tclr,hiclr,loclr)
  char tr;
  char tc;
  char style;
  char bclr;
  char *btxt;
  char tclr;
  {

   he_window[0] = tr;
   he_window[1] = tc;
   he_window[2] = tr + 5;
   he_window[3] = tc + 25;
   he_style = style;
   he_bclr = bclr;
   he_btxt = btxt;
   he_tclr = tclr;
   he_mhiclr = hiclr;
   he_mloclr = loclr;

  _harderr((void far *)do_harderror);
  }

int do_harderror(deverror,errcode,devhdr)
  unsigned deverror;
  unsigned errcode;
  unsigned far *devhdr;
  {
  short ret;
  short key;
  short item = 0;
  short keys[1];
  char go = 1;
  static struct MENU m1[3] =
    {
    {0,0,"Abort",'A'},
    {0,0,"Retry",'R'},
    {0,0,"Ignore",'I'}
    };
  char winptr[26][6][2];
  char r;
  char c;
  char str[6];
  static char *message[] =
    {
    "Disk is write protected",
    "Unknown Unit",
    "Drive not ready",
    "Disk Error",
    "Disk Error",
    "Disk Error",
    "Disk Error",
    "Disk Error",
    "Disk Error",
    "Priner out of paper",
    "Disk Error",
    "Disk Error",
    "General Failure"
    };

  keys[0] = 0;

  m1[0].row = he_window[0]+3;
  m1[1].row = he_window[0]+3;
  m1[2].row = he_window[0]+3;
  m1[0].col = he_window[1]+3;
  m1[1].col = he_window[1]+10;
  m1[2].col = he_window[1]+17;

  bios_rcp(&r,&c);
  savergn(he_window,winptr);
  bios_su(he_window,0,he_tclr);
  box(he_window,he_style,he_bclr,he_btxt,he_tclr);
  bios_scp(he_window[0]+1,he_window[1]+1);
  errcode &= 0x0ff;
  conout(message[errcode],he_tclr);

  while(go)
    {
    key = menu(m1,3,keys,&item,he_mhiclr,he_mloclr);
    switch(key)
      {
      case 'A':
        go = 0;
        ret = _HARDERR_ABORT;
        break;

      case 'R':
        go = 0;
        ret = _HARDERR_RETRY;
        break;

      case 'I':
        go = 0;
        ret = _HARDERR_IGNORE;
        break;
      }
    }
  restrgn(he_window,winptr);
  bios_scp(r,c);
  return(ret);
  }
