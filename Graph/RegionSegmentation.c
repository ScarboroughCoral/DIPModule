#include "BMPHelper.h"
#include <stdio.h>



void regionSegmentSeed(const char * src, const char * dest, Point * seeds, int length,int t)
{
	BMFILEHEADER header;
	INFOHEADER info;


	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(src, &header, &info, palette, data);

	unsigned char **outData = malloc(sizeof(unsigned char*));

	
	*outData = malloc(pixelCounts);

	for (size_t i = 0; i < length; i++)
	{

	}


	BMPWriter8(dest, &header, &info, palette, outData);
}

void regionSegmentWithoutSeed(const char * src, const char * dest)
{
}
