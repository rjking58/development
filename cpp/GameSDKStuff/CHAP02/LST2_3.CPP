typedef struct tagBITMAPINFOHEADER {
   DWORD biSize;
   DWORD biWidth;
   DWORD biHeight;
   WORD biPlanes;
   WORD biBitCount;
   DWORD biCompression;
   DWORD biSizeImage;
   DWORD biXPelsPerMeter;
   DWORD biYPelsPerMeter;
   DWORD biClrUsed;
   DWORD biClrImportant;
} BITMAPINFOHEADER;

