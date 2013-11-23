#include <stdio.h>

main()
{
  
  char *env_var;

  env_var = getenv("FLURB");

  if (env_var != NULL)
  {
    printf("env_var->%s",env_var);
  
    *env_var = 'c';
  
    printf("env_var->%s",env_var);
  
    if (putenv("FLURB=clurb"))
    {
      printf("out of environment space");
    } /* if */
  }
  else
  {
    printf("environment variable doesn't exist!");
  } /* if */

} /* main */

