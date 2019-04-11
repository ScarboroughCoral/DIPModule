#include "BMPHelper.h"
#include <math.h>

void ThresholdSegment(const char * from, const char * to, int type, double param)
{
	switch (type)
	{
	case THRESHOLD_SEED:
		seed(from, to, param);
		break;
	case THRESHOLD_ITERATION:
		iteration(from, to,param);
		break;
	case THRESHOLD_OSTU:
		ostu(from, to);
		break;
	default:
		break;
	}
}

void seed(const char * from, const char * to, double k)
{
	BMFILEHEADER header;
	INFOHEADER info;


	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(from, &header, &info, palette, data);

	unsigned char **outData = malloc(sizeof(unsigned char*));

	*outData = malloc(pixelCounts);

	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{
			if (*(*data + i * info.width + j)>k)
			{
				*(*outData + i * info.width + j) = 255;
			}
			else
			{
				*(*outData + i * info.width + j) = 0;
			}
			
		}
	}

	BMPWriter8(to, &header, &info, palette, outData);
	int histogramLatest[256] = { 0 };
	double grayscaleDistributionLatest[256] = { 0 };
	for (unsigned i = 0; i < pixelCounts; i++)
	{

		histogramLatest[*(*data + i)]++;
	}
	for (unsigned i = 0; i < 256; i++)
	{
		grayscaleDistributionLatest[i] = histogramLatest[i] * 1.0 / pixelCounts;
	}
	outputGrayscaleHistogramWithThresholdMark("threshold-seed-histogram.bmp",grayscaleDistributionLatest,&info,k);

}

void iteration(const char * from, const char * to, double e)
{
	BMFILEHEADER header;
	INFOHEADER info;


	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(from, &header, &info, palette, data);

	unsigned char **outData = malloc(sizeof(unsigned char*));

	*outData = malloc(pixelCounts);
	double lastAverageGrayVal = 0, newAverageGrayVal = 0;
	double sum0 = 0, sum1 = 0;

	int count0 = 0, count1 = 0;

	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{
				sum0+=*(*data + i * info.width + j) ;
		}
	}
	lastAverageGrayVal = newAverageGrayVal = sum0 / pixelCounts;

	
	do{
		sum0 = 0;
		sum1 = 0;
		count1 = 0;
		count0 = 0;
		for (unsigned i = 0; i < info.height; i++)
		{
			lastAverageGrayVal = newAverageGrayVal;
			for (unsigned j = 0; j < info.width; j++)
			{
				if (*(*data + i * info.width + j)> lastAverageGrayVal)
				{
					sum1 += *(*data + i * info.width + j);
					count1++;
				}
				else
				{
					sum0 += *(*data + i * info.width + j);
					count0++;
				}
			}
		}
		newAverageGrayVal = (sum1/count1 + sum0/count0)/2;
		

	} while (fabs(lastAverageGrayVal - newAverageGrayVal) > e);


	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{
			if (*(*data + i * info.width + j) > newAverageGrayVal)
			{
				*(*outData + i * info.width + j) = 255;
			}
			else
			{
				*(*outData + i * info.width + j) = 0;
			}

		}
	}

	BMPWriter8(to, &header, &info, palette, outData);
	int histogramLatest[256] = { 0 };
	double grayscaleDistributionLatest[256] = { 0 };
	for (unsigned i = 0; i < pixelCounts; i++)
	{

		histogramLatest[*(*data + i)]++;
	}
	for (unsigned i = 0; i < 256; i++)
	{
		grayscaleDistributionLatest[i] = histogramLatest[i] * 1.0 / pixelCounts;
	}
	outputGrayscaleHistogramWithThresholdMark("threshold-seed-iteration.bmp", grayscaleDistributionLatest, &info,newAverageGrayVal);
}

void ostu(const char * from, const char * to)
{
	BMFILEHEADER header;
	INFOHEADER info;


	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(from, &header, &info, palette, data);

	unsigned char **outData = malloc(sizeof(unsigned char*));

	*outData = malloc(pixelCounts);
	double sum0 = 0, sum1 = 0;

	int count0 = 0, count1 = 0;
	double variance = 0;
	double threshold = 0;

	for (size_t gray = 1; gray < 256; gray++)
	{
		sum0 = 0;
		sum1 = 0;
		count1 = 0;
		count0 = 0;
		for (unsigned i = 0; i < info.height; i++)
		{
			for (unsigned j = 0; j < info.width; j++)
			{
				if (*(*data + i * info.width + j) > gray)
				{
					sum1 += *(*data + i * info.width + j);
					count1++;
				}
				else
				{
					sum0 += *(*data + i * info.width + j);
					count0++;
				}
			}
		}
		double newVariance = pow(sum1 / count1 - sum0 / count0, 2)*count0/pixelCounts*count1/pixelCounts;
		if (newVariance>variance)
		{
			variance = newVariance;
			threshold = gray;
		}
	}



	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{
			if (*(*data + i * info.width + j) > threshold)
			{
				*(*outData + i * info.width + j) = 255;
			}
			else
			{
				*(*outData + i * info.width + j) = 0;
			}

		}
	}

	BMPWriter8(to, &header, &info, palette, outData);
	int histogramLatest[256] = { 0 };
	double grayscaleDistributionLatest[256] = { 0 };
	for (unsigned i = 0; i < pixelCounts; i++)
	{

		histogramLatest[*(*data + i)]++;
	}
	for (unsigned i = 0; i < 256; i++)
	{
		grayscaleDistributionLatest[i] = histogramLatest[i] * 1.0 / pixelCounts;
	}
	outputGrayscaleHistogramWithThresholdMark("threshold-seed-ostu.bmp", grayscaleDistributionLatest, &info,threshold);
}


