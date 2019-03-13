#include "BMPHelper.h"
#include "Histogram.h"
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 8
#define HEIGHT 3
#define L 256


void outputGrayscaleHistogram(const char * filename, double distribution[], INFOHEADER *origin) {
	BMFILEHEADER header;
	INFOHEADER info = *origin;


	// set header
	header.type[0] = 'B';
	header.type[1] = 'M';
	*(unsigned *)header.offset = sizeof(header)+sizeof(info)+256*sizeof(RGBQUAD);

	// set info
	info.colorCount = 30;
	info.width = 100* WIDTH;
	info.height = HEIGHT * L;
	info.infoHeaderSize = 40;
	info.planes = 1;
	info.sizeImage = info.width*info.height;
	info.colorCount = 8;
	info.colorUsed = 256;

	*(unsigned *)header.size = header.offset + info.sizeImage;


	RGBQUAD ** palette = malloc(sizeof(RGBQUAD *));
	*palette = malloc(256* sizeof(RGBQUAD));

	for (size_t i = 0; i < 256; i++)
	{
		((*palette) + i)->r = ((*palette) + i)->b = ((*palette) + i)->g = i;
	}

	unsigned char image[HEIGHT * L][100 * WIDTH];
	for (size_t i = 0; i < HEIGHT * L; i++)
	{
		for (size_t j = 0; j < 100 * WIDTH; j++)
		{
			image[i][j] = 255;
		}
	}

	for (size_t i = 0; i < info.height; i += HEIGHT)
	{
		for (size_t j = 0; j < info.width; j++)
		{
			if (distribution[i/HEIGHT]>0.25)
			{
				distribution[i / HEIGHT] = 0.25;
			}
			if (j/ WIDTH >= distribution[i/ HEIGHT]*100*4)
			{
				break;
			}
			for (size_t k = 0; k < HEIGHT; k++)
			{
				image[i + k][j] = 0;
			}
		}
	}

	unsigned char *p = image;
	unsigned char *q = &p;

	//printf("%p,%p,%d", p, q,*q);

	BMPWriter8(filename, &header, &info, palette, q);

}