#include "BMPUtil.h"
#include<stdlib.h>
#include<stdio.h>

#pragma warning(disable : 4996)

void BMPResolver() {
	

	BMFILEHEADER header;
	INFOHEADER info;
	RGBITEM ** data = malloc(sizeof(RGBITEM*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	const char* filename = "width.bmp";
	printf("Read from %s\n", filename);
	unsigned pixelCounts = BMPReader(filename, &header, &info, palette, data);
	//修改单色
	//for (size_t i = 0; i < pixelCounts; i++)
	//{
	//	//printf("%p-%p\n", *data,*data+1);
	//	//(*data+i)->r = 0;
	//	(*data + i)->g = 0;
	//	(*data + i)->b = 0;
	//}

	//灰度化
	int gray;
	/*for (size_t i = 0; i < pixelCounts; i++)
	{
		gray = ((*data + i)->r * 299 + (*data + i)->g * 587 + (*data + i)->b * 114 + 500) / 1000;
		(*data + i)->r = gray;
		(*data + i)->g = gray;
		(*data + i)->b = gray;
	}*/

	//灰度图反色
	for (size_t i = 0; i < pixelCounts; i++)
	{
		gray = ((*data + i)->r * 299 + (*data + i)->g * 587 + (*data + i)->b * 114 + 500) / 1000;
		(*data + i)->r = 255 - gray;
		(*data + i)->g = 255 - gray;
		(*data + i)->b = 255 - gray;
	}

	char * result = "1-testaw.bmp";

	BMPWriter(result, &header, &info, palette, data);
	printf("Write to %s\n", result);
}