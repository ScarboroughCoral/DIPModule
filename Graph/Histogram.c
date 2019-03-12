#include "BMPHelper.h"
#include <stdio.h>

void Histogram() {

	BMFILEHEADER header;
	INFOHEADER info;
	RGBITEM ** data = malloc(sizeof(RGBITEM*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));

	unsigned pixelCounts = BMPReader("width.bmp", &header, &info, palette, data);



}