#include <time.h>

#define TRUE  1
#define FALSE 0
/* structures for manipulation of messages. */


/* definitions of raw types used in messages */

#define EOT         0x0004
#define ENQ         0x0005
#define SOH         0x0001
#define ETB         0x0017
#define ACK         0x0006
#define STX         0x0002
#define NAK         0x0015
#define ETX         0x0003
#define CMD1_TYPE   0x0100
#define CMD2_TYPE   0x0200
#define CMD3_TYPE   0x0300
#define CMD4_TYPE   0x0400
#define CMD5_TYPE   0x0500
#define CMD6_TYPE   0x0600
#define CMD7_TYPE   0x0700
#define ChksumStart 0x0800 /* inclusive     */
#define ChksumStop  0x1000 /* non-inclusive */
#define EndMsg      0x8000

/* generic command types. */
/*  WC = write command                                       */
/*  RC = read command                                        */
/*  BB = Binary Byte                                         */
/*  BW = Binary Word                                         */
/*  BRW = Binary Reverse Word (LSB first)                    */
/*  AHB = ASCII hex byte (2 characters representing 8 bits)  */
/*  AHW = ASCII hex word(4 characters representing 16 bits)  */
/*  AHRW = ASCII hex reverse word
      (4 characters representing 16 bits, LSB chars first)   */
/*  AHLW = ASCII hex long word (8 chars repr. 32 bits)       */
/*  SPCL = Special.. generally for specific PLC types        */

#define WC_DATA_BLK_TYPE_405     CMD1_TYPE & 0x0001
#define WC_REMAIN_BYTES_256_AHB  CMD1_TYPE & 0x0002
#define WC_BLOCKS_256_AHB        CMD1_TYPE & 0x0003
#define WC_NET_ADDR_AHB          CMD1_TYPE & 0x0004
#define WC_NET_ADDR_405_SPCL_BB  CMD1_TYPE & 0x0005
#define RC_DATA_BLK_TYPE_405     CMD1_TYPE & 0x0006
#define RC_REMAIN_BYTES_256_AHB  CMD1_TYPE & 0x0007
#define RC_BLOCKS_256_AHB        CMD1_TYPE & 0x0008
#define RC_NET_ADDR_AHB          CMD1_TYPE & 0x0009
#define RC_NET_ADDR_405_SPCL_BB  CMD1_TYPE & 0x000A
#define WC_RW_TYPE_405_BB        CMD1_TYPE & 0x000B
#define RC_RW_TYPE_405_BB        CMD1_TYPE & 0x000C
/* must be special since the 405 algorithm for xlating address is */
/* screwball                                                      */
#define WC_ADDR_405_AHW          CMD1_TYPE & 0x000D 
#define RC_ADDR_405_AHW          CMD1_TYPE & 0x000E
#define WC_ADDR_AHW              CMD1_TYPE & 0x000F 
#define RC_ADDR_AHW              CMD1_TYPE & 0x0010
#define WC_CHKSUM                CMD1_TYPE & 0x0011
#define RC_CHKSUM                CMD1_TYPE & 0x0012


/* plc types */
#define PLC_405  1

/* 405 ADDRESS TYPES.... */
/* for now.. just this one type.. */
#define V_MEM_405        0x031

#define READ_405     0x030
#define WRITE_405    0x038

/* checksum types */
#define CHECKSUM_LRC  1

/* blocksizes for PLC's */
#define BLOCKSIZE_405 256

/* readwrite sense defs */
#define READ_THEN_WRITE   1
#define WRITE_THEN_READ   2
#define READ_ONLY         3
#define WRITE_ONLY        4



char
   msg_buffer_ofst,
   msg_buffer[200];

unsigned int
   msg_len;

time_t
   tnow;
struct tm
   *time_now;  

unsigned int 
   /* first node */
   master_enq_msg_405[] =
                        { 'N'                     ,
                          WC_NET_ADDR_405_SPCL_BB  ,
                          ENQ                     ,
                          EndMsg                    },
   slave_enq_ack_msg_405[] =
                        { 'N'                     ,
                          RC_NET_ADDR_405_SPCL_BB  ,
                          ACK                     ,
                          EndMsg                    },
   slave_enq_nak_msg_405[] =
                        { 'N'                     ,
                          RC_NET_ADDR_405_SPCL_BB  ,
                          NAK                     ,
                          EndMsg                    },
   /* second node */
   simple_ack_msg[] = 
                        { ACK                     ,
                          EndMsg                    },
   simple_nak_msg[] =
                        { NAK                     ,
                          EndMsg                    },
   simple_eot_msg[] =
                        { EOT                     ,
                          EndMsg                    },
                        
   master_header_msg_405[] =
                        { SOH                             ,
                          WC_NET_ADDR_AHB   | ChksumStart ,
                          WC_RW_TYPE_405_BB               ,
                          V_MEM_405                       ,
                          WC_ADDR_405_AHW                 ,
                          WC_BLOCKS_256_AHB               ,
                          WC_REMAIN_BYTES_256_AHB         ,
                          0x0030                          ,
                          0x0031                          ,
                          ETB               | ChksumStop  ,
                          WC_CHKSUM                       ,
                          EndMsg                             },

   intrmdiate_data_block_405[] =
                        { STX                                ,
                          RC_DATA_BLK_TYPE_405 | ChksumStart ,
                          ETB                  | ChksumStop  ,
                          RC_CHKSUM                          ,
                          EndMsg                               },

   end_data_block_405[] =
                        { STX                                ,
                          RC_DATA_BLK_TYPE_405 | ChksumStart ,
                          ETX                  | ChksumStop  ,
                          RC_CHKSUM                          ,
                          EndMsg                               },
                                                               
                     
struct node_struct
   {
   unsigned int 
      rw_sense              ,
      *action_msg           ,
      *good_action_msg      ,
      *bad_action_msg       ,
      *intermediate_data_msg,
      *end_data_msg         ,
      chksum_type           ,
      block_cnt             ,
      byte_cnt              ,
      retries               ,
      whole_block_sz        ;

   struct tm 
      timeout               ; 

   struct node_struct  
      *nxt_if_good_ptr      ,
      *nxt_if_bad_ptr       ;
   };

struct node_struct
   *curr_node,
   *head_405_read_msg_ptr,
   *prev_405_read_msg_ptr,
   *new_405_read_msg_ptr ,
   *curr_405_read_msg_ptr;

struct node_struct *make_a_405_msg_struct();
   {
   struct node_struct
      *temp_ptr;
   temp_ptr = (struct node_struct *) malloc((sizeof struct node_struct));
   if (temp_ptr == NULL)
      {
      printf("not enough memory to run");
      exit(1);
      }
   return(temp_ptr);
   }



make_405_msg_tables()
   {
   /* enquiry message */
   head_405_read_msg_ptr = make_a_405_msg_struct();
   head_405_read_msg_ptr->rw_sense               = WRITE_THEN_READ;
   head_405_read_msg_ptr->*action_msg            = master_enq_msg_405   ;
   head_405_read_msg_ptr->*good_action_msg       = slave_enq_ack_msg_405;
   head_405_read_msg_ptr->*bad_action_msg        = slave_enq_nak_msg_405;
   head_405_read_msg_ptr->*intermediate_data_msg = NULL;
   head_405_read_msg_ptr->*end_data_msg          = NULL;
   head_405_read_msg_ptr->chksum_type            = CHECKSUM_LRC;
   head_405_read_msg_ptr->block_cnt              = 0;
   head_405_read_msg_ptr->byte_cnt               = 0;
   head_405_read_msg_ptr->retries                = 0;
   head_405_read_msg_ptr->whole_block_sz         = BLOCKSIZE_405;

   head_405_read_msg_ptr->nxt_if_bad_ptr  = head_405_read_msg_ptr;

   /* header message */
   new_405_read_msg_ptr = make_a_405_msg_struct();
   new_405_read_msg_ptr->rw_sense               = WRITE_THEN_READ;
   new_405_read_msg_ptr->*action_msg            = master_header_msg_405 ;
   new_405_read_msg_ptr->*good_action_msg       = simple_ack_msg        ;
   new_405_read_msg_ptr->*bad_action_msg        = simple_nak_msg        ;
   new_405_read_msg_ptr->*intermediate_data_msg = NULL;
   new_405_read_msg_ptr->*end_data_msg          = NULL;
   new_405_read_msg_ptr->chksum_type            = CHECKSUM_LRC;
   new_405_read_msg_ptr->block_cnt              = 0;
   new_405_read_msg_ptr->byte_cnt               = 0;
   new_405_read_msg_ptr->retries                = 0;
   new_405_read_msg_ptr->whole_block_sz         = BLOCKSIZE_405;

   /* make previous message point here if good */
   head_405_read_msg_ptr->nxt_if_good_ptr = new_405_read_msg_ptr;

   new_405_read_msg_ptr->nxt_if_bad_ptr   = new_405_read_msg_ptr;

   /* save it off for next message */
   prev_405_read_msg_ptr = new_405_read_msg_ptr;

   /* read data block */
   new_405_read_msg_ptr = make_a_405_msg_struct();
   new_405_read_msg_ptr->rw_sense               = READ_THEN_WRITE;
   new_405_read_msg_ptr->*action_msg            = NULL  ;
   new_405_read_msg_ptr->*good_action_msg       = simple_ack_msg ;
   new_405_read_msg_ptr->*bad_action_msg        = simple_nak_msg ;
   new_405_read_msg_ptr->*intermediate_data_msg = intrmdiate_data_block_405;
   new_405_read_msg_ptr->*end_data_msg          = end_data_block_405;
   new_405_read_msg_ptr->chksum_type            = CHECKSUM_LRC;
   new_405_read_msg_ptr->block_cnt              = 0;
   new_405_read_msg_ptr->byte_cnt               = 0;
   new_405_read_msg_ptr->retries                = 0;
   new_405_read_msg_ptr->whole_block_sz         = BLOCKSIZE_405;

   /* make previous message point here if good */
   prev_405_read_msg_ptr->nxt_if_good_ptr  = new_405_read_msg_ptr;

   new_405_read_msg_ptr->nxt_if_bad_ptr   = new_405_read_msg_ptr;

   /* save it off for next message */
   prev_405_read_msg_ptr = new_405_read_msg_ptr;


   /* EOT data block */
   new_405_read_msg_ptr = make_a_405_msg_struct();
   new_405_read_msg_ptr->rw_sense               = READ_THEN_WRITE;
   new_405_read_msg_ptr->*action_msg            = simple_eot_msg ;
   new_405_read_msg_ptr->*good_action_msg       = simple_eot_msg ;
   new_405_read_msg_ptr->*bad_action_msg        = simple_eot_msg ;
   new_405_read_msg_ptr->*intermediate_data_msg = NULL;
   new_405_read_msg_ptr->*end_data_msg          = NULL;
   new_405_read_msg_ptr->chksum_type            = CHECKSUM_LRC;
   new_405_read_msg_ptr->block_cnt              = 0;
   new_405_read_msg_ptr->byte_cnt               = 0;
   new_405_read_msg_ptr->retries                = 0;
   new_405_read_msg_ptr->whole_block_sz         = BLOCKSIZE_405;

   /* make previous message point here if good */
   prev_405_read_msg_ptr->nxt_if_good_ptr  = new_405_read_msg_ptr;
   
   /* end the sequence... */                                   
   new_405_read_msg_ptr->nxt_if_bad_ptr    = NULL;
   new_405_read_msg_ptr->nxt_if_good_ptr   = NULL;

   }

void wc_data_blk_type_405     ();
   {
   }
void wc_remain_bytes_256_ahb  ();
   {
   }
void wc_blocks_256_ahb        ();
   {
   }
void wc_net_addr_ahb          ();
   {
   }
void wc_net_addr_405_spcl_bb  ();
   {
   }
int rc_data_blk_type_405     ();
   {
   }
int rc_remain_bytes_256_ahb  ();
   {
   }
int rc_blocks_256_ahb        ();
   {
   }
int rc_net_addr_ahb          ();
   {
   }
int rc_net_addr_405_spcl_bb  ();
   {
   }
void wc_rw_type_405_bb        ();
   {
   }
int rc_rw_type_405_bb        ();
   {
   }
void wc_addr_405_ahw          ();
   {
   }
int rc_addr_405_ahw          ();
   {
   }
void wc_addr_ahw              ();
   {
   }
int rc_addr_ahw              ();
   {
   }
void wc_chksum                ();
   {
   }
int rc_chksum                ();
   {
   }

/* control for messages. */
#define READ_FIRST_STATE       1
#define READ_SECOND_STATE      2
#define GOTO_NXT_MSG_STATE     3
#define WRITE_FIRST_STATE      4
#define WRITE_SECOND_STATE     5
#define NO_ACTIVE_MSG_STATE    6
#define DO_ACK_STATE           7
#define DO_NAK_STATE           8

unsigned int
   curr_state     , /* i.e. read or write */
   read_char_ofst ,
   plc_type       ,
   addr           ,
   rw_type        ,
   blocks_to_read ,
   leftovers_to_read,
   curr_block     ,
   curr_char      ,
   byte_cnt       ;

void prep_node_state()
   {
   curr_node->block_cnt              = 0;
   curr_node->byte_cnt               = 0;
   curr_node->retries                = 0;
   if ( (curr_node->rw_sense == READ_THEN_WRITE ) ||
        (curr_node->rw_sense == READ_ONLY       )    )
      {
      curr_state = READ_FIRST_STATE;
      }
   else
      {
      curr_state = WRITE_FIRST_STATE;
      }
   }

void do_prep_msg()
   {
   switch(plc_type)
      {
      case PLC_405 :
         {
         if (rw_type==READ_405)
            {
            curr_node = head_405_read_msg_ptr;
            prep_node_state();
            }
         else
            {
            /* write type... */
            }
         }    
         break;
      default:
         exit(1);
      }

   }

void match_msg()
   {
   /* must return either a 'yes I matched' or 'still waiting' or 
      'bad match---retry' message                                  */
   }

void do_bee_do()
   {
   unsigned int
      fini;

   if ( curr_state!=NO_ACTIVE_MSG_STATE )
      {
      fini = FALSE;
      while (!fini)
         {
         switch(curr_state)
            {
            case READ_FIRST_STATE       :
            case READ_SECOND_STATE      :
               {
               get_waiting_chars();
               if ( msg_buffer_ofst!= 0 )
                  {
                  match_msg();
                  }
               }
               break;
            case GOTO_NXT_MSG_STATE  :
               {
                
               curr_node = 
               }
               break;
            case WRITE_FIRST_STATE      :
            case WRITE_SECOND_STATE     :
               {

               }
               break;
            case DO_ACK_STATE           :
            case DO_NAK_STATE           :
               {

               }
               break;
            }

         }
      }
   }
main()
   {


   }
