#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN 133 // line length + null

main(int argc, char ** argv)
{
  char line_in[LINE_LEN];
  char *line_ret;
  int  line_len;
  FILE *out_f;

  if(argc != 2)
  {
    printf("usage:  DtoU foutname\n"); 
  }
  else
  {
    out_f=fopen(argv[1],"wb");
    if(out_f != (FILE *) NULL)
    {
      line_ret = gets(line_in);
      while (line_ret != (char *) NULL)   
      {
        line_len = strlen(line_in);
        line_in[line_len] = (char) 0x0a;
        fwrite(line_in,1,line_len+1,out_f);
        line_ret = gets(line_in);
      } 
      fclose(out_f);
    }
  }

}
