#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <windows.h>
#include <windowsx.h>

#include <mmsystem.h>

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>

#include <ddraw.h>
#include "blackbox.h"


#define WINDOW_CLASS_NAME "WIN3DCLASS"

#define WINDOW_WIDTH    640
#define WINDOW_HEIGHT   480

#define GAME_STATE_INIT          0
#define GAME_STATE_START_LEVEL   1
#define GAME_STATE_RUN           2
#define GAME_STATE_SHUTDOWN      3
#define GAME_STATE_EXIT          4

#define NUM_BLOCK_ROWS           6
#define NUM_BLOCK_COLUMNS       8

#define BLOCK_WIDTH              64
#define BLOCK_HEIGHT             16
#define BLOCK_ORIGIN_X           8
#define BLOCK_ORIGIN_Y           8
#define BLOCK_X_GAP              80
#define BLOCK_Y_GAP              32

#define PADDLE_START_X           (SCREEN_WIDTH/2 - 16)
#define PADDLE_START_Y           (SCREEN_HEIGHT - 32)
#define PADDLE_WIDTH             32
#define PADDLE_HEIGHT            8
#define PADDLE_COLOR             191


#define BALL_START_Y             (SCREEN_HEIGHT/2)
#define BALL_SIZE                4

#define SHADOW_OFFSET            4  


int Game_Init(void * parms= NULL);
int Game_Shutdown(void *parms = NULL);
int Game_Main(void *parms = NULL);

HWND main_window_handle = NULL;
HINSTANCE main_instance = NULL;
int game_state = GAME_STATE_INIT;

int paddle_x      = 0;
int paddle_y      = 0;
int ball_x        = 0;
int ball_y        = 0;
int ball_dx       = 0;
int ball_dy       = 0;
int score         = 0;
int level         = 1;
int blocks_hit    = 0;

UCHAR blocks[NUM_BLOCK_ROWS][NUM_BLOCK_COLUMNS];

LRESULT CALLBACK WindowProc(  HWND hwnd,
                              UINT msg,
                              WPARAM wparam,
                              LPARAM lparam )
{
   PAINTSTRUCT ps;
   HDC         hdc;
   
   switch(msg)
   {
      case WM_CREATE:
         {
            return(0);
            
         }
         break;
      
      case WM_PAINT:
         {
            hdc = BeginPaint(hwnd,&ps);
            
            EndPaint(hwnd,&ps);
            return(0);
         }
         break;
      
      case WM_DESTROY:
         {
            PostQuitMessage(0);
            return(0);
         }
         break;
         
      default:
         break;   
      
   }
   
   return(DefWindowProc(hwnd,msg,wparam,lparam));
} // end WindowProc

int WINAPI WinMain(  HINSTANCE hinstance,
                     HINSTANCE hprevinstance,
                     LPSTR     lpcmdline,
                     int       ncmdshow)
{
   WNDCLASS    winclass;
   HWND        hwnd;
   MSG         msg;
   HDC         hdc;
   PAINTSTRUCT ps;
   
   winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
   winclass.lpfnWndProc    = WindowProc;
   winclass.cbClsExtra     = 0;
   winclass.cbWndExtra     = 0;
   winclass.hInstance      = hinstance;
   winclass.hIcon          = LoadIcon(NULL,IDI_APPLICATION);
   winclass.hCursor        = LoadCursor(NULL,IDC_ARROW);
   winclass.hbrBackground  = (HBRUSH) GetStockObject(BLACK_BRUSH);
   winclass.lpszMenuName   = NULL;
   winclass.lpszClassName  = WINDOW_CLASS_NAME;
   
   if (!RegisterClass(&winclass))
   {
      return(0);
   }

    
   if (!(hwnd = CreateWindow( WINDOW_CLASS_NAME,
                              "WIN3D Game Console",
                              WS_POPUP | WS_VISIBLE,
                              0,
                              0,
                              GetSystemMetrics(SM_CXSCREEN),
                              GetSystemMetrics(SM_CYSCREEN),
                              NULL,
                              NULL,
                              hinstance,
                              NULL )))
   {
      return(0);
   }
   
   ShowCursor(FALSE);
   
   main_window_handle = hwnd;
   main_instance      = hinstance;
   
   Game_Init();
   
   while(1)
   {
      if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
      {
         if (msg.message == WM_QUIT)
         {
            break;
         }
         
         TranslateMessage(&msg);
         
         DispatchMessage(&msg);
      }
       
      Game_Main();
   } // end while
   
   Game_Shutdown();
   
   ShowCursor(TRUE);
   
   return(msg.wParam);
   
} // end WinMain

int Game_Init(void *parms)
{
   return(1);
}

int Game_Shutdown(void *parms)
{
   return(1);
}

void Init_Blocks(void)
{
   for (int row = 0; row < NUM_BLOCK_ROWS; row++)
   {
      for (int col = 0; col < NUM_BLOCK_COLUMNS; col ++)
      {
         // setup the color of the block..
         blocks[row][col] = row*16 + col*3 + 16;
      }
   }
}

void Draw_Blocks(void)
{
   int x1 = BLOCK_ORIGIN_X;
   int y1 = BLOCK_ORIGIN_Y;
   
   for (int row=0; row < NUM_BLOCK_ROWS; row++)
   {
      x1 = BLOCK_ORIGIN_X;
      
      for (int col = 0; col < NUM_BLOCK_COLUMNS; col++)
      {
         if (blocks[row][col] != 0)
         {
            // shadow first..
            // shadow is to the right and lower than actual image..
            Draw_Rectangle(x1 - SHADOW_OFFSET,       
                           y1 + SHADOW_OFFSET,
                           x1 + BLOCK_WIDTH  - SHADOW_OFFSET,
                           y1 + BLOCK_HEIGHT + SHADOW_OFFSET,
                           0);
            // then the block..
            Draw_Rectangle(x1,
                           y1,
                           x1+BLOCK_WIDTH,
                           y1+BLOCK_HEIGHT,
                           blocks[row][col]);
         }
         x1 += BLOCK_X_GAP;
      }
      y1 += BLOCK_Y_GAP;
   }
}

void Process_Ball(void)
{
   
   int ball_cx = ball_x+(BALL_SIZE/2);
   int ball_cy = ball_y+(BALL_SIZE/2);
   
   // are we in the paddle portion of the screen and is the ball moving DOWN?                        
   if (ball_y > (SCREEN_HEIGHT/2) && ball_dy > 0)
   {
      // x,y = center of ball 
      int x = ball_x + (BALL_SIZE/2);
      int y = ball_y + (BALL_SIZE/2);
      
      // is center of ball overlapping the paddle?
      if (     (x >= paddle_x && x <= paddle_x + PADDLE_WIDTH  ) 
            && (y >= paddle_y && y <= paddle_y + PADDLE_HEIGHT )
         )
      {
         // collision.. 
         // ball should go UP
         ball_dy = -ball_dy;
         
         // move ball
         ball_y += ball_dy;
         
         // if paddle is moving right..            
         if (KEY_DOWN(VK_RIGHT))
         {
            ball_dx += (rand()%3);
         }
         // if paddle is moving left..            
         else if (KEY_DOWN(VK_LEFT))
         {
            ball_dx -= (rand()%3);
         }
         else
         {
            ball_dx += (-1 + rand()%3);
         }
         
         if (blocks_hit >= (NUM_BLOCK_ROWS*NUM_BLOCK_COLUMNS))
         {
            // up one level if all blocks are clear :)
            game_state = GAME_STATE_START_LEVEL;
            level++;
         }
         
         MessageBeep(MB_OK);
         
         return;
      }
   }
   
   int x1 = BLOCK_ORIGIN_X;
   int y1 = BLOCK_ORIGIN_Y;
   
   for (int row = 0; row < NUM_BLOCK_ROWS; row++)
   {
      x1 = BLOCK_ORIGIN_X;
      
      for (int col = 0; col < NUM_BLOCK_COLUMNS; col++)
      {
         if (blocks[row][col] != 0)
         {
            if (     (ball_cx > x1                 ) 
                  && (ball_cx < x1 + BLOCK_WIDTH   )
                  && (ball_cy > y1                 )
                  && (ball_cy < y1 + BLOCK_HEIGHT  ) )
            {
               blocks[row][col] = 0;
               
               blocks_hit++;
               
               ball_dy = -ball_dy;
               
               ball_dx += (-1+rand()%3);
               
               MessageBeep(MB_OK);
               
               score+=5*(level+(abs(ball_dx)));
               
               return;
            }
         }
         
         x1 += BLOCK_X_GAP;
      }
      
      y1 += BLOCK_Y_GAP;
   }
}

int Game_Main(void *parms)
{
   char buffer[80];
   
   if (game_state == GAME_STATE_INIT)
   {
      DD_Init(SCREEN_WIDTH, SCREEN_HEIGHT,SCREEN_BPP);
      
      srand(Start_Clock());
      
      paddle_x = PADDLE_START_X;
      paddle_y = PADDLE_START_Y;
      
      ball_x   = 8 + rand() % (SCREEN_WIDTH - 16);
      ball_y   = BALL_START_Y;
      ball_dx  = -4 + rand()%(8+1);
      ball_dy  = 6 + rand() % 2;
      
      game_state = GAME_STATE_START_LEVEL;
   }
   else if (game_state == GAME_STATE_START_LEVEL)
   {
      Init_Blocks();
      
      blocks_hit = 0;
      
      game_state = GAME_STATE_RUN;
   }
   else if (game_state == GAME_STATE_RUN)
   {
      Start_Clock();
      
      // CLEAR SURFACE
      Draw_Rectangle(0,0,SCREEN_WIDTH - 1, SCREEN_HEIGHT -1,200);
      
      if (KEY_DOWN(VK_RIGHT))
      {
         paddle_x += 8;
         
         // paddle on screen guarantee
         
         if (paddle_x > (SCREEN_WIDTH - PADDLE_WIDTH))
         {
            paddle_x = SCREEN_WIDTH - PADDLE_WIDTH;
         }
      }
      else if (KEY_DOWN(VK_LEFT))
      {
         paddle_x -= 8;
         
         // paddle on screen guarantee
         
         if (paddle_x < 0 )
         {
            paddle_x = 0;
         }
      }
      
      Draw_Blocks();
      
      ball_x += ball_dx;
      ball_y += ball_dy;
      
      if (ball_x > (SCREEN_WIDTH - BALL_SIZE) || ball_x < 0)
      {
         ball_dx = -ball_dx;
         
         ball_x += ball_dx;
      }
      
      if (ball_y < 0)
      {
         ball_dy = -ball_dy;
         
         ball_y += ball_dy;
      }
      else if (ball_y > (SCREEN_HEIGHT - BALL_SIZE))
      {
         ball_dy = -ball_dy;
         
         ball_y += ball_dy;
         
         score -= 100;
      }
      
      if (ball_dx > 8)
      {
         ball_dx = 8;
      }
      else if (ball_dx < -8)
      {
         ball_dx = -8;
      }
      
      Process_Ball();
      
      Draw_Rectangle(paddle_x -8,
                     paddle_y +8,
                     paddle_x + PADDLE_WIDTH - 8,
                     paddle_y + PADDLE_HEIGHT +8,
                     0                             );
                     
      Draw_Rectangle(paddle_x ,
                     paddle_y ,
                     paddle_x + PADDLE_WIDTH ,
                     paddle_y + PADDLE_HEIGHT,
                     PADDLE_COLOR                  );


      Draw_Rectangle(ball_x -4,
                     ball_y +4,
                     ball_x + BALL_SIZE - 4,
                     ball_y + BALL_SIZE + 4,
                     0                             );

      Draw_Rectangle(ball_x,
                     ball_y,
                     ball_x + BALL_SIZE ,
                     ball_y + BALL_SIZE ,
                     255                          );
                     

      sprintf(buffer," F R E A K O U T                   score %d //            Level %d",score,level);
      
      Draw_Text_GDI(buffer,8,SCREEN_HEIGHT - 16, 127);
      
      DD_Flip();
      
      Wait_Clock(30);
      
      if (KEY_DOWN(VK_ESCAPE))
      {
         PostMessage(main_window_handle,WM_DESTROY,0,0);
         
         game_state = GAME_STATE_SHUTDOWN;
      }
      
      
   }
   else if (game_state == GAME_STATE_SHUTDOWN)
   {
      DD_Shutdown();
      
      game_state = GAME_STATE_EXIT;
   }
   
   return(1);
}
