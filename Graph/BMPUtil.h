#pragma once
#include "BMP.h"
/*
*Summary: read bmp file
*Parameters:
*     filename:bmp file name    
*     header : bmp file header struct variable(not null)
*     info	 : bmp file info struct variable(not null)
*     palette: bmp file palette  variable(RGBQUAD **,not null)
*     data   : bmp file data  variable(RGBITEM **,not null)
*Return : pixelCounts if read completely.
*/
int BMPReader(const char* filename, BMFILEHEADER* header, INFOHEADER * info, RGBQUAD ** palette, RGBITEM ** data);


/*
*Summary: write bmp file
*Parameters:
*     filename:bmp file name    
*     header : bmp file header struct variable(not null)
*     info	 : bmp file info struct variable(not null)
*     palette: bmp file palette  variable(RGBQUAD **,not null)
*     data   : bmp file data  variable(RGBITEM **,not null)
*Return : pixelCounts if read completely.
*/

int BMPWriter(const char* filename, BMFILEHEADER* header, INFOHEADER * info, RGBQUAD ** palette, RGBITEM ** data);
int BMPWriter8(const char* filename, BMFILEHEADER* header, INFOHEADER * info, RGBQUAD ** palette, unsigned char ** data);
int BMPReader8(const char* filename, BMFILEHEADER* header, INFOHEADER * info, RGBQUAD ** palette, unsigned char ** data);