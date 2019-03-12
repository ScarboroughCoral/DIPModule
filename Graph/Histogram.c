#include "BMPHelper.h"
#include <stdio.h>

void Histogram() {

	BMFILEHEADER header;
	INFOHEADER info;
	RGBITEM ** data = malloc(sizeof(RGBITEM*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));

	unsigned pixelCounts = BMPReader("test.bmp", &header, &info, palette, data);

	int histogram[256] = { 0 };

	for (size_t i = 0; i < pixelCounts; i++)
	{
		int gray = ((*data + i)->r * 299 + (*data + i)->g * 587 + (*data + i)->b * 114 + 500) / 1000;
		histogram[gray]++;
	}

	for (size_t i = 0; i < 256; i++)
	{
		if (histogram[i] * 100.0 / pixelCounts<0.01)
		{
			continue;
		}
		printf("灰度级【%3d】统计像素概率：%4.2f%%\n", i, histogram[i]*100.0/ pixelCounts);
	}

}