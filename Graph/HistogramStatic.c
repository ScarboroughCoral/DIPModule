#include "BMPHelper.h"
#include <stdio.h>

void HistogramStatic() {

	const int L = 256;

	

	// 24位真彩色转8位灰度

	const char* filename = "1.bmp";
	printf("Read from %s\n", filename);
	const char* filename2 = "2.bmp";
	BMP24To8Gray(filename, filename2);

	printf("Convert %s to 8bit: %s\n", filename, filename2);

	BMFILEHEADER header;
	INFOHEADER info;
	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));

	unsigned pixelCounts = BMPReader8("2.bmp", &header, &info, palette, data);

	int histogram[256] = { 0 };
	double grayscaleDistribution[256] = { 0 };
	double cumulativeDistribution[256] = { 0 };


	//8位灰度统计
	for (size_t i = 0; i < pixelCounts; i++)
	{
		
		histogram[*(*data+i)]++;
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
		
		int newGray = (int)(cumulativeDistribution[*(*data + i)] * (L-1) + 0.5);
		*(*data + i) = newGray;

	}

	int histogramLatest[256] = { 0 };
	double grayscaleDistributionLatest[256] = { 0 };
	for (size_t i = 0; i < pixelCounts; i++)
	{

		histogramLatest[*(*data + i)]++;
	}
	for (size_t i = 0; i < 256; i++)
	{
		grayscaleDistributionLatest[i] = histogramLatest[i] * 1.0 / pixelCounts;
	}

	const char *out = "2-3.bmp";
	printf("Write to %s\n", out);
	BMPWriter8(out, &header, &info, palette, data);
	const char * originHistogram = "2-4.bmp";
	printf("Original Histogram Write to %s\n", originHistogram);
	const char * latestHistogram = "2-5.bmp";
	printf("Latest Histogram Write to %s\n", latestHistogram);
	outputGrayscaleHistogram(originHistogram, grayscaleDistribution, &info);
	outputGrayscaleHistogram(latestHistogram, grayscaleDistributionLatest, &info);
	//printf("%f\n", cumulativeDistribution[L - 1]);
	//BMPWriter("histogramout.bmp", &header, &info, palette, data);


}