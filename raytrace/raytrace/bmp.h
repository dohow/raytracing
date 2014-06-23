typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

typedef struct tagBITMAPFILEHEADER { 
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER;  
  
typedef struct tagBITMAPINFOHEADER {  
    DWORD biSize;
    LONG biWidth;  
    LONG biHeight; 
    WORD biPlanes; 
    WORD biBitCount;
    DWORD  biCompression; 
    DWORD  biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} BITMAPINFOHEADER;
  
typedef struct tagRGBQUAD {  
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD;

typedef struct tagIMAGEDATA
{
    BYTE red;
    BYTE green;
    BYTE blue;
} IMAGEDATA;
