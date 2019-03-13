#include "BMPHelper.h"
#include <stdio.h>

void HistogramStatic() {

	const int L = 256;

	BMFILEHEADER header;
	INFOHEADER info;
	RGBITEM ** data = malloc(sizeof(RGBITEM*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));

	unsigned pixelCounts = BMPReader("width.bmp", &header, &info, palette, data);

	int histogram[256] = { 0 };
	double grayscaleDistribution[256] = { 0 };
	double cumulativeDistribution[256] = { 0 };

	//24位真彩色求灰度
	for (size_t i = 0; i < pixelCounts; i++)
	{
		int gray = ((*data + i)->r * 299 + (*data + i)->g * 587 + (*data + i)->b * 114 + 500) / 1000;
		histogram[gray]++;
	}

	for (size_t i = 0; i < 256; i++)
	{
		grayscaleDistribution[i] = histogram[i] * 1.0 / pixelCounts;
		//求cdf
		if (i==0)
		{
			cumulativeDistribution[i] = grayscaleDistribution[i];
		}
		else
		{
			cumulativeDistribution[i] = cumulativeDistribution[i - 1] + grayscaleDistribution[i];
		}
	/*	if (grayscaleDistribution[i] * 100.0 <0.01)
		{
			continue;
		}
		printf("灰度级【%3d】统计像素概率：%4.2f%%\n", i, grayscaleDistribution[i]*100);*/
	}

	for (size_t i = 0; i < pixelCounts; i++)
	{
		int gray = ((*data + i)->r * 299 + (*data + i)->g * 587 + (*data + i)->b * 114 + 500) / 1000;
		int newGray = (int)(cumulativeDistribution[gray] * (L-1) + 0.5);
		(*data + i)->r = newGray;
		(*data + i)->g = newGray;
		(*data + i)->b = newGray;

	}
	BMPWriter("histogramout.bmp", &header, &info, palette, data);
	//outputGrayscaleHistogram("grayHistogram.bmp", grayscaleDistribution,&info);
	//printf("%f\n", cumulativeDistribution[L - 1]);
	//BMPWriter("histogramout.bmp", &header, &info, palette, data);


}