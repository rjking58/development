#include "sops1.c"

main()
   {
   FILE *setops_file;

   boolean
      netbios_b,
      network_b,
      virus_b,
      printq_b;


   netbios_b = TRUE;
   network_b = TRUE;
   virus_b   = TRUE;
   printq_b  = TRUE;

   if ((setops_file = fopen("c:\\setops.bat", "w")) == NULL) 
      {
      printf("bad file open???\n");
      }
   else
      {
      disp_Init(def_ModeText, NULL);
      sops1(&network_b , 
            &netbios_b , 
            &virus_b   , 
            &printq_b    );
      if(network_b)
         {
         fprintf(setops_file,"set NETWORK=TRUE\n");
         }
      else
         {
         fprintf(setops_file,"set NETWORK=FALSE\n");
         }
      if(netbios_b)
         {
         fprintf(setops_file,"set NETBIOS=TRUE\n");
         }
      else
         {
         fprintf(setops_file,"set NETBIOS=FALSE\n");
         }
      if(virus_b)
         {
         fprintf(setops_file,"set VIRUSER=TRUE\n");
         }
      else
         {
         fprintf(setops_file,"set VIRUSER=FALSE\n");
         }
      if(printq_b)
         {
         fprintf(setops_file,"set PQ=TRUE\n");
         }
      else
         {
         fprintf(setops_file,"set PQ=FALSE\n");
         }

      disp_Close();
      fclose(setops_file);
      }  /* if fopen */
   } /* main */
