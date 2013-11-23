#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <direct.h>
#include <ctype.h>
#include <usrlib.h>
#include <keys.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>

char bnds1[4] = {1,1,23,78};
char euidirect[65];
char apidirect[65];
short disktype;
char r = 2;
char c = 1;

char *euifiles[] =
   {
   "DL.BAT",
   "FM.BAT",
   "TE.BAT",
   "DIRECT.EXE",
   "DIRECT.MSG",
   "DIRECT.OVL",
   "VT100.MAP",
   "DIRECT.CNF",
   "DIRECT.HLP",
   0
   };

char *apifiles[] =
   {
   "DPCCFG.EXE",
   "DPCPP.EXE",
   "DPCRTL.EXE",
   "DPCEND.EXE",
   "DPCCHK.EXE",
   "DIRECT.BIN",
   "DPC.MSG",
   "DBLDOT.PRG",
   "EMPLQRY.DIR",
   "CUSTQRY.DIR",
   "SALESRPT.DIR",
   0
   };

main(argc,argv)

  short argc;
  char **argv;
  {
  static char bnds[4] = {0,0,24,79};
  short key;
  short esckeys[1];

  cls(0);
  box(bnds,1,7," dBASE DIRECT/UX  Version 1.0 Installation ",15);

  bios_scp(2,4);
  conout("This installation proceedure will copy the dBASE DIRECT/UX files",7);
  bios_scp(3,4);
  conout("from the distribution disk(s) to the appropriate directories on",7);
  bios_scp(4,4);
  conout("your hard disk.  Before running this program you should have made",7);
  bios_scp(5,4);
  conout("made backup copies of the distribution disks and you should have",7);
  bios_scp(6,4);
  conout("have run the ID program.",7);
  bios_scp(8,4);
  conout("You can quit Install at any time by pressing the",7);
  conout(" <ESC> ",15);
  conout("key",7);

  bios_scp(12,20);
  conout("Are you ready to continue? ",15);
  bios_scp(14,15);
  conout("<ESC> ",15);
  conout("to quit or any other key to continue",7);

  key = onein();
  if(key == 27)
    {
    do_exit("");
    }

  disktype = getdisktype();
  get_euidirect();
  get_apidirect();

  do_install();

  cls(7);

  }

getdisktype()
  {
  static struct MENU disktype[2] =
    {
    {10,30,"5-1/4 Inch",'5'},
    {12,30,"3-1/2 Inch",'3'},
    };
  short item = 0;
  short esckeys[1];
  short key;

  esckeys[0] = 0;

  /*  clear work area */

  bios_su(bnds1,0,0);

  bios_scp(6,4);
  conout("Install needs to know what type of disk you are installing from.",7);
  bios_scp(7,4);
  conout("Select a disk drive type by highlighting the correct type and",7);
  bios_scp(8,4);
  conout("press the ",7);
  conout("<ENTER> ",15);
  conout("key or press ",7);
  conout("<ESC> ",15);
  conout("to quit.",7);

  key = menu(disktype,2,esckeys,&item,112,7);
  if(key == ESC)
    {
    do_exit("");
    }
  return(item);
  }

get_euidirect()
  {
  short key;

  strcpy(euidirect,"C:\\DIRECT");

  /*  clear work area */

  bios_su(bnds1,0,0);

  bios_scp(6,4);
  conout("Install needs to know the disk drive & directory where the ",7);
  bios_scp(7,4);
  conout("dBASE DIRECT/UX Menu interface should be installed.",7);
  bios_scp(9,4);
  conout("Please enter the disk and directory below or press ",7);
  conout("<ESC> ",15);
  conout("to quit.",7);

  key = conin(11,5,euidirect,64,112,7);
  if(key == ESC)
    {
    do_exit("");
    }
  ltrim(euidirect);
  trim(euidirect);
  }

get_apidirect()
  {
  short key;

  strcpy(apidirect,"C:\\dBASE");

  /*  clear work area */

  bios_su(bnds1,0,0);

  bios_scp(6,4);
  conout("Install needs to know the disk drive & directory where the ",7);
  bios_scp(7,4);
  conout("dBASE DIRECT/UX API should be installed. We recomend that you",7);
  bios_scp(8,4);
  conout("install the API into your dBASE directory.",7);
  bios_scp(10,4);
  conout("Please enter the disk and directory below or press ",7);
  conout("<ESC> ",15);
  conout("to quit.",7);

  key = conin(12,5,apidirect,64,112,7);
  if(key == ESC)
    {
    do_exit("");
    }
  ltrim(apidirect);
  trim(apidirect);
  }

do_exit(str)

  char *str;
  {
  cls(7);
  bios_scp(0,0);
  conout(str,7);
  bios_scp(1,0);
  conout("Install not completed",7);
  bios_scp(1,0);
  exit(0);
  }

do_install()
  {
  short instdrive;
  char drive[3];
  char str[81];
  char type[11];
  short key;
  short ret;

  /*  clear work area */

  bios_su(bnds1,0,0);

/* get disk drive that istall was started from  */

  _dos_getdrive(&instdrive);
  strcpy(drive," :");
  drive[0] = 'A' + instdrive - 1;

  if(disktype == 1)
    {
    strcpy(type,"3-1/2 Inch");
    }
  else
    {
    strcpy(type,"5-1/4 Inch");
    }
  bios_scp(4,4);
  conout("Install will install from drive ",7);
  conout(drive,15);
  conout(" wich is a ",7);
  conout(type,15);
  conout(" drive",7);
  bios_scp(6,4);
  conout("and put the Menu interface into the directory:",7);
  bios_scp(7,4);
  conout(euidirect,15);
  bios_scp(9,4);
  conout("and put the API into the directory:",7);
  bios_scp(10,4);
  conout(apidirect,15);

  bios_scp(16,4);
  conout("Press any key to perform the installation or press ",7);
  conout("<ESC> ",15);
  bios_scp(17,4);
  conout("to quit Install.",7);

  key = onein();
  if(key == ESC)
    {
    do_exit("");
    }

  /*  clear work area */

  bios_su(bnds1,0,0);


  if(disktype == 1)
    {
    install3(drive,euidirect,apidirect);
    }
  else
    {
    install5(drive,euidirect,apidirect);
    }
  }

install3(source,euidirect,apidirect)
  char *source;
  char *euidirect;
  char *apidirect;
  {
  short ret;
  short i;
  char src[80];
  char dest[80];

  ret = chdir(euidirect);
  if(ret != 0)
    {
    message("Directory did not exist",0,0);
    message("Creating directory %s",euidirect,0);
    makepath(euidirect);
    }
  ret = chdir(apidirect);
  if(ret != 0)
    {
    message("Directory did not exist",0,0);
    message("Creating directory %s",apidirect,0);
    makepath(apidirect);
    }

  while(access("DIRECT.BIN",0))
    {
    prompt("Be sure your SYSTEM DISK is in drive %s",source);
    }

/* copy eui files to destination */
  i = 0;
  while(euifiles[i] != NULL)
    {
    sprintf(src,"%s\\%s",source,euifiles[i]);
    sprintf(dest,"%s\\%s",euidirect,euifiles[i]);
    message("Copying file %s -> %s",src,dest);
    fcopy(src,dest);
    i++;
    }

/* copy api files to destination */
  i = 0;
  while(apifiles[i] != NULL)
    {
    sprintf(src,"%s\\%s",source,apifiles[i]);
    sprintf(dest,"%s\\%s",apidirect,apifiles[i]);
    message("Copying file %s -> %s",src,dest);
    fcopy(src,dest);
    i++;
    }
  prompt("Install Complete",0,0);
  }

install5(source,euidirect,apidirect)
  char *source;
  char *euidirect;
  char *apidirect;
  {
  short ret;
  short i;
  char src[80];
  char dest[80];

  ret = chdir(euidirect);
  if(ret != 0)
    {
    message("Directory did not exist",0,0);
    message("Creating directory %s",euidirect,0);
    makepath(euidirect);
    }
  ret = chdir(apidirect);
  if(ret != 0)
    {
    message("Directory did not exist",0,0);
    message("Creating directory %s",apidirect,0);
    makepath(apidirect);
    }

  while(access("DIRECT.BIN",0))
    {
    prompt("Be sure your API Disk is in drive %s",source);
    }

/* copy api files to destination */
  i = 0;
  while(apifiles[i] != NULL)
    {
    sprintf(src,"%s\\%s",source,apifiles[i]);
    sprintf(dest,"%s\\%s",apidirect,apifiles[i]);
    message("Copying file %s -> %s",src,dest);
    fcopy(src,dest);
    i++;
    }

  while(access("DIRECT.EXE",0))
    {
    prompt("Put your Menu System Disk in drive %s",source);
    }

/* copy eui files to destination */
  i = 0;
  while(euifiles[i] != NULL)
    {
    sprintf(src,"%s\\%s",source,euifiles[i]);
    sprintf(dest,"%s\\%s",euidirect,euifiles[i]);
    message("Copying file %s -> %s",src,dest);
    fcopy(src,dest);
    i++;
    }
  prompt("Install Complete",0,0);
  }


makepath(path)
  char *path;
  {
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];
  short dummy;
  char *ptr;
  char str[81];
  short ret;

/* get components of the path */

  _splitpath(path,drive,dir,fname,ext);
  strcat(dir,fname);

  if(strlen(ext) > 0)
    {
    do_exit("Invalid directory name for Menu interface");
    }
  else if(strlen(drive) == 0)
    {
    do_exit("No drive name in Menu interface path");
    }

/* make the path one level at a time */

  strcpy(str,drive);
  ptr = strtok(dir,"\\");
  while(ptr != NULL)
    {
    strcat(str,"\\");
    strcat(str,ptr);
    ret = mkdir(str);
    if(ret == -1 && errno == ENOENT)
      {
      do_exit("Bad Menu interface path");
      }
    ptr = strtok(NULL,"\\");
    }
  }

message(fmt,str1,str2)
  char *fmt;
  char *str1;
  char *str2;
  {
  char str[81];

  sprintf(str,fmt,str1,str2);
  if(r > bnds1[2])
    {
    bios_su(bnds1,1,0);
    r = bnds1[2];
    }

  bios_scp(r,c);
  conout(str,7);
  r++;
  }

prompt(fmt,str1,str2)
  char *fmt;
  char *str1;
  char *str2;
  {
  char str[81];

  sprintf(str,fmt,str1,str2);
  if(r > bnds1[2])
    {
    bios_su(bnds1,1,0);
    r = bnds1[2];
    }

  bios_scp(r,c);
  conout(str,15);
  r++;
  if(r > bnds1[2])
    {
    bios_su(bnds1,1,0);
    r = bnds1[2];
    }

  bios_scp(r,c);
  conout("Press any key to continue. . .",15);
  if(onein() == 27)
    {
    do_exit("");
    }
  r++;
  }

fcopy(src,dest)
  char *src;
  char *dest;
  {
  short in;
  short out;
  char buf[1024];
  short stat;
  short ret;

  in = open(src,O_BINARY | O_RDONLY);
  if(in < 0)
    {
    do_exit("File not found");
    }

  out = open(dest,O_BINARY | O_CREAT | O_TRUNC | O_WRONLY,S_IREAD | S_IWRITE);
  if(out < 0)
    {
    do_exit("Cannot create file");
    }

  stat = read(in,buf,1024);
  while(stat > 0)
    {
    ret = write(out,buf,stat);
    if(ret != stat)
      {
      do_exit("Disk Full");
      }
    stat = read(in,buf,1024);
    }

  close(out);
  close(in);
  }
