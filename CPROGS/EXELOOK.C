#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <graph.h>
#include <assert.h>




#define  EXE_HEADER_LENGTH 28 /*total bytes in header....  */

#define  FNAME_OFST         1         /* in argv..               */
#define  INBYTES            1         /* for fread               */
#define  PAGESIZE           512       /* size of file page       */
#define  PARAGRAPHSIZE      16        /* 80x86 memory paragraphs */
#define  RELOCTAB_ELEMENTSZ 4         /* seg/offst pair  4 bytes */

#define  START_SEG 0x1000   /* hex...    */

  union exe_header_u
    {
    struct broken_down_header_s
      {
      char           exe_id[2];          /* id characaters  "MZ"    2 bytes */
      unsigned short last_pg_size;       /* in file.... in bytes..  2 bytes */
      unsigned short total_file_pages;   /* in 512 byte pages       2 bytes */
      unsigned short reloc_item_cnt;     /* count of word pairs     2 bytes */
      unsigned short hdr_paragraphs;     /* in 16 byte paragraphs   2 bytes */
      unsigned short min_alloc;          /* additional mem reqrd by 2 bytes */
                                         /* program. in 16byte paragraphs   */
      unsigned short max_alloc;          /* max mem.. as above.     2 bytes */
      unsigned short initial_ss;         /* adjust by start seg.    2 bytes */
      unsigned short initial_sp;         /* no adjustment necessary 2 bytes */
      unsigned short check_sum;          /* ones comp./entire file. 2 bytes */
      unsigned short initial_ip;         /* no adjust               2 bytes */
      unsigned short initial_cs;         /* adjust by start seg.    2 bytes */
      unsigned short reloc_table_ofst;   /* ofset from begin of file2 bytes */
      unsigned short overlay_number;     /* should be zero..        2 bytes */


      }  broken_down_header;
    char exe_head[EXE_HEADER_LENGTH]; 

    } exe_header;

  typedef     /* so that we can use sizeof operator on this... */
    struct RELOC_LST_T
      {
        unsigned long         address  ;
/*        unsigned short        reloc_seg    ; */
/*        struct RELOC_LST_T   *reloc_lst_nxt; */

      } ;


  struct RELOC_LST_T *reloc_lst_ary   ;


  FILE *exe_file;
  FILE *new_exe_file;

  unsigned long int setup_fsize();

  union in_buffer_u
    {
    unsigned char  c_sz[512]; /* access by characters... */
    unsigned short s_sz[256]; /* access by shorts...     */
    } in_buffer;





  main (argc,argv)
  int   argc   ;
  char *argv[] ;
  {

  unsigned long int total_fsize         ,
                    total_imagesize     ,
                    total_header_length ,
                    reloctab_size       ,
                    next_ofst_toread    ,
                    loop_ofst           ,
                    slop                ,
                    distance_into_image ,
                    curr_addr           ,
                    addr_ofst           ,
                    last_addr           ,
                    seq_count           ,
                    nonseq_count        ,
                    total_bytes_read    ;

  unsigned int      new_ss              ,
                    new_cs              ;

  unsigned int      *addr_tofix         ;



  /* clear the screen to be pretty... */
  _clearscreen(_GCLEARSCREEN);

  /* initialize all list pointers... */
  reloc_lst_ary = NULL;


  if (argc == 2)
    {

    /* try to open the file in binary mode */
    if ((exe_file = fopen(argv[FNAME_OFST],"rb")) != NULL)
      {
      new_exe_file = fopen("newexe.exe","wb");

      if (new_exe_file == NULL)
        {
        printf("couln't open new_exe_file!\n");
        exit(0);

        }
      if (( total_bytes_read = 
             fread(exe_header.exe_head,INBYTES,EXE_HEADER_LENGTH,exe_file)) 
           == EXE_HEADER_LENGTH                                             )
        {
        fwrite(exe_header.exe_head,INBYTES,EXE_HEADER_LENGTH,new_exe_file);
        next_ofst_toread = EXE_HEADER_LENGTH;
        printf("next_ofst_toread :%lx\n\n",next_ofst_toread);

        printf("ahhh... feels so good\n");

        printf("exe id           :");
        putchar(exe_header.broken_down_header.exe_id[0]);
        putchar(exe_header.broken_down_header.exe_id[1]);
        printf("\n");

        printf("last_pg_size     :%4xh\n",
               exe_header.broken_down_header.last_pg_size     );


        printf("total_file_pages :%4xh\n",
               exe_header.broken_down_header.total_file_pages );

        total_fsize = 
          setup_fsize(exe_header.broken_down_header.total_file_pages,
                      exe_header.broken_down_header.last_pg_size      );
/*                                                                               */
/*        if(exe_header.broken_down_header.last_pg_size == 0)                    */
/*          {                                                                    */
/*          total_fsize =                                                        */
/*            ( (unsigned long)exe_header.broken_down_header.total_file_pages    */
/*              * (unsigned long) PAGESIZE                                       */
/*            );                                                                 */
/*          }                                                                    */
/*        else                                                                   */
/*          {                                                                    */
/*          total_fsize =                                                        */
/*            ( ( (unsigned long)exe_header.broken_down_header.total_file_pages  */
/*                * (unsigned long)PAGESIZE                                      */
/*              )                                                                */
/*              - (unsigned long) PAGESIZE                                       */
/*            )                                                                  */
/*            + (unsigned long) exe_header.broken_down_header.last_pg_size;      */
/*          }                                                                    */
                                                                                 
        printf("total_fsize      :%8lxh\n",total_fsize);                         


        printf("reloc_item_cnt   :%4xh ",
               exe_header.broken_down_header.reloc_item_cnt   );

        reloctab_size = 
          (unsigned long) exe_header.broken_down_header.reloc_item_cnt 
          * (unsigned long) RELOCTAB_ELEMENTSZ; 

        printf("(%8lx bytes)\n",reloctab_size);


        printf("hdr_paragraphs   :%4xh ",
               exe_header.broken_down_header.hdr_paragraphs   );

        total_header_length = 
          (unsigned long) exe_header.broken_down_header.hdr_paragraphs 
          * (unsigned long) PARAGRAPHSIZE;

        printf("(%8lx bytes)\n",total_header_length);


        total_imagesize = total_fsize - total_header_length;
        printf("total_imagesize  :%8lx\n",total_imagesize);
        

        printf("min_alloc        :%4xh\n",
               exe_header.broken_down_header.min_alloc        );


        printf("max_alloc        :%4xh\n",
               exe_header.broken_down_header.max_alloc        );


        printf("initial_ss       :%4xh\n",
               exe_header.broken_down_header.initial_ss       );

        new_ss = 
          exe_header.broken_down_header.initial_ss 
          + START_SEG;

        printf("new_ss           :%4xh\n",new_ss);



        printf("initial_sp       :%4xh\n",
               exe_header.broken_down_header.initial_sp       );


        printf("check_sum        :%4xh\n",
               exe_header.broken_down_header.check_sum        );


        printf("initial_ip       :%4xh\n",
               exe_header.broken_down_header.initial_ip       );


        printf("initial_cs       :%4xh\n",
               exe_header.broken_down_header.initial_cs       );
        new_cs = 
          exe_header.broken_down_header.initial_cs 
          + START_SEG;
        printf("new_cs           :%4xh\n",new_cs);
                                                  



        printf("reloc_table_ofst :%4xh\n",
               exe_header.broken_down_header.reloc_table_ofst );


        printf("overlay_number   :%4xh\n",
               exe_header.broken_down_header.overlay_number   );


        printf("Press <ENTER> to continue");
        getchar();

        /* clear the screen */

        _clearscreen(_GCLEARSCREEN);

        /* read the relocation table into memory. */

        /* read any extraneous bytes into memory and throw them away...  */
        slop = exe_header.broken_down_header.reloc_table_ofst - 
                 next_ofst_toread;

        if (slop > 0)
          {
          total_bytes_read = 
               fread(in_buffer.c_sz     ,
                     INBYTES            ,
                     slop               ,
                     exe_file            ); 
          fwrite(in_buffer.c_sz,
                 INBYTES,
                 slop,
                 new_exe_file);

          next_ofst_toread += slop;
          }

        /* try to allocate enough memory for the reloc table.... */

        reloc_lst_ary = 
          (struct RELOC_LST_T *) 
            malloc(exe_header.broken_down_header.reloc_item_cnt
                   * (sizeof(struct RELOC_LST_T))                    );
        if(reloc_lst_ary == NULL)
          {
          printf("yo boss, not enough memory for the reloc table boss!\n");
          exit(0);
          }
        seq_count    = 0;
        nonseq_count = 0;




        /* load in the relocation table */


        for(loop_ofst= 0                                             ;
            loop_ofst < exe_header.broken_down_header.reloc_item_cnt ;
            loop_ofst++                                                )
          {

          fread(in_buffer.c_sz     ,
                INBYTES            ,
                RELOCTAB_ELEMENTSZ ,
                exe_file            ); 
          fwrite(in_buffer.c_sz     ,
                 INBYTES            ,
                 RELOCTAB_ELEMENTSZ ,
                 new_exe_file        ); 


          next_ofst_toread += RELOCTAB_ELEMENTSZ;

          /* allocate element in linked list */


          /* convert it to a raw address and store it in the table */

          curr_addr = 
              ( (unsigned long)in_buffer.s_sz[0]     )
            + ( (unsigned long)in_buffer.s_sz[1] * 16); 

/*          printf("address  %lx\n"      ,
                 reloc_lst_ary->address );
*/

          /* do a list insertion on the bugger. 
             (this may end up being slow but it will get the job done!)
             (P.P.S. if this is too slow, replace with binary search before
              insertion!)
          */
          if(loop_ofst == 0)
            {
            reloc_lst_ary[0].address = curr_addr;
            last_addr = 0;
            }
          else
            {
            /* linear search the table */

            addr_ofst = 0;
            while(    (addr_ofst <= last_addr                      )
                   && (reloc_lst_ary[addr_ofst].address < curr_addr)  )
              {
              addr_ofst++;
              }
            if(addr_ofst > last_addr)
              {
              /* is sequential.... just insert it. */
              reloc_lst_ary[addr_ofst].address = curr_addr;
              seq_count++;    
              }
            else
              {
              /* isn't sequential... are we looking at a match (if so
                 this fucker is really hosed up! */

              assert(reloc_lst_ary[addr_ofst].address != curr_addr);
              /* move the current data up one element */

              memmove( (reloc_lst_ary + (addr_ofst+1))  ,    /* dest.    */
                       (reloc_lst_ary + addr_ofst)      ,    /* source   */
                       ( ((last_addr - addr_ofst)+1)
                         * sizeof(struct RELOC_LST_T) )   ); /* char cnt */

              /* insert the new piece of data */
              reloc_lst_ary[addr_ofst].address = curr_addr;
              nonseq_count++; 
              }

            last_addr++;
            }
          }
        /* print statistics... */
        printf("sequential     insertions: %f %%\n",
               ((float)(seq_count) / (float)(seq_count+nonseq_count))
                 * 100.0);
        printf("non-sequential insertions: %f %%\n",
               ((float)(nonseq_count) / (float)(seq_count+nonseq_count))
                 * 100.0);

        printf("first address  %lx\n"      ,
                reloc_lst_ary[0].address );
        printf("last address  %lx\n"      ,
                reloc_lst_ary[exe_header.broken_down_header.reloc_item_cnt-1].address );

                 
        /* check out table... */
        for(loop_ofst= 1                                             ;
            loop_ofst < exe_header.broken_down_header.reloc_item_cnt ;
            loop_ofst++                                                )
          {
          assert(reloc_lst_ary[loop_ofst].address
                 >  reloc_lst_ary[loop_ofst-1].address );

/*          printf("address  %lx\n"      ,
                 reloc_lst_ary[loop_ofst].address ); */
          }

        for(loop_ofst = 0 ;
            loop_ofst < exe_header.broken_down_header.total_file_pages ;
            loop_ofst++                                                  )
          {
          if(loop_ofst+1 
             != exe_header.broken_down_header.total_file_pages )
            {
            fread(in_buffer.c_sz  ,
                  INBYTES         ,
                  PAGESIZE        ,
                  exe_file         ); 
            fwrite(in_buffer.c_sz  ,
                   INBYTES         ,
                   PAGESIZE        ,
                   new_exe_file     ); 
            }
          else
            {
            fread(in_buffer.c_sz                               ,
                  INBYTES                                      ,
                  exe_header.broken_down_header.last_pg_size   ,
                  exe_file                                       ); 
            fwrite(in_buffer.c_sz                              ,
                   INBYTES                                     ,
                   exe_header.broken_down_header.last_pg_size  ,
                   new_exe_file                                  ); 
            }

          }
        fclose(exe_file);
        fclose(new_exe_file);
        }
      else
        {
        printf("this file must be pretty hosed up since the read failed!\n");
        exit(0);
        }

      }

    }
  else
    {
    printf("need file name:\n");
    printf("syntax:  exelook  <filename>\n");
    exit(0);
    }


  }




unsigned long int setup_fsize(total_fpages,last_pg_size)
unsigned int total_fpages;
unsigned int last_pg_size;
  {
  if(last_pg_size == 0)
    {
    return ((unsigned long)total_fpages * (unsigned long) PAGESIZE);
    }
  else
    {
    return( 
            ( ( 
                (unsigned long)total_fpages * (unsigned long)PAGESIZE                                    
              )
              - (unsigned long) PAGESIZE 
            )
            + (unsigned long) last_pg_size
          );
    }

  }
