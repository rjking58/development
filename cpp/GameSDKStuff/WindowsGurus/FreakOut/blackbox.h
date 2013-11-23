#ifndef BLACKBOX
#define BLACKBOX

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      8   // 8 bits per pixel
#define MAX_COLORS      256


#define KEY_DOWN(vk_code)  ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0 )
#define KEY_UP(vk_code)    ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1 )


#define DD_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct));  ddstruct.dwSize=sizeof(ddstruct); }


typedef unsigned short USHORT;
typedef unsigned short WORD;
typedef unsigned char  UCHAR;
typedef unsigned char  BYTE;


extern LPDIRECTDRAW7          lpdd;    //dd obj.
extern LPDIRECTDRAWSURFACE7   lpddsprimary;
extern LPDIRECTDRAWSURFACE7   lpddsback;
extern LPDIRECTDRAWPALETTE    lpddpal;
extern LPDIRECTDRAWCLIPPER    lpddclipper;
extern PALETTEENTRY           palette[256];
extern PALETTEENTRY           save_palette[256];
extern DDSURFACEDESC2         ddsd;
extern DDBLTFX                ddbltfx;
extern DDSCAPS2               ddscaps;
extern HRESULT                ddrval;
extern DWORD                  start_clock_count;

extern int                    min_clip_x,
                              max_clip_x,
                              min_clip_y,
                              max_clip_y,
                              
                              screen_width,
                              screen_height,
                              screen_bpp;
                              
int DD_Init(int width,int height, int bpp);
int DD_Shutdown(void);
LPDIRECTDRAWCLIPPER DD_Attach_Clipper( LPDIRECTDRAWSURFACE7 lpdds,
                                       int num_rects,
                                       LPRECT clip_list);
                                       
int DD_Flip(void);
int DD_Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds,int color);

DWORD Start_Clock(void);
DWORD Get_Clock(void);
DWORD Wait_Clock(DWORD count);

int Draw_Rectangle(int                    x1,
                     int                  y1,
                     int                  x2,
                     int                  y2,
                     int                  color,
                     LPDIRECTDRAWSURFACE7 lpdd=lpddsback);
                     
int Draw_Text_GDI(char                 *text,
                  int                  x,
                  int                  y,
                  COLORREF             color,
                  LPDIRECTDRAWSURFACE7 lpdds=lpddsback);

int Draw_Text_GDI(char                 *text,
                  int                  x,
                  int                  y,
                  int                  color,
                  LPDIRECTDRAWSURFACE7 lpdds=lpddsback);
                  
                              


#endif