#include "BMPHelper.h"
#include <stdlib.h>
#include <math.h>


void Hough(const char * src, const char * output)
{
	BMFILEHEADER header;
	INFOHEADER info;


	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(src, &header, &info, palette, data);

	unsigned char **outData = malloc(sizeof(unsigned char*));

	*outData = calloc(pixelCounts,sizeof(char));


	double sin_value[180];
	double cos_value[180];
	for (int i = -90; i < 90; i++)
	{
		sin_value[i + 90] = sin(i*3.1415926 / 180);
		cos_value[i + 90] = cos(i*3.1415926 / 180);
	}
	const int r = sqrt(info.width*info.width+ info.height*info.height);
	int *hough_acc = calloc(180*2*r,sizeof(int));
	
	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{
			for (size_t k = 0; k < 180; k++)
			{
				if (*(*data + i* info.width + j)>0)
				{
					int tp = (int)(i*sin_value[k] + j * cos_value[k])+r;
					if (tp < 0)
					{
						
						continue;
					}
					hough_acc[tp * 180 + k]++;
				}
			}
		}
	}
	int max = 0;
	for (size_t i = 0; i < 180 * r; i++)
	{
		if (max<hough_acc[i])
		{
			max = hough_acc[i];
		}
	}

	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{
			for (size_t k = 0; k < 180; k++)
			{
				int tp = (int)(i*sin_value[k] + j * cos_value[k])+r;
				if (tp<0)
				{
					continue;
				}
				if (hough_acc[tp * 180 + k]>0.4*max)
				{
					*(*outData + i * info.width + j) = 255;
				}
			}
		}
	}



	BMPWriter8(output, &header, &info, palette, outData);
}

//ImageUtil::IMGDATA ImageUtil::Hough::line(ImageUtil::ImageData data, double deltaSigma)
//{
//
//	typedef ImageUtil::ImageSize uint;
//
//	const int r = std::sqrt(data.width * data.width + data.height * data.height);
//	const int d = 2 * r;
//	const int sigma = 181 / deltaSigma;
//
//	uint *houghSpace = new uint[d  * sigma];
//	memset(houghSpace, 0, d * sigma * sizeof(uint));
//
//
//	ImageUtil::ImageData cannyImg = ImageUtil::EdgeDetection::canny(data, 40, 80);
//
//	ImageUtil::outputBlackWhiteImage(cannyImg, "bitmap/canny.bmp");
//	//ImageUtil::toTwoValueImage(cannyImg);
//
//	ImageUtil::progressBar.reset(data.height * data.width, "生成HoughSpace");
//
//	for (uint i = 0; i < data.height; i++)
//	{
//		for (uint j = 0; j < data.width; j++)
//		{
//			if (cannyImg[i][j] > 0)
//			{
//				double s = 0;
//				while (true) {
//					const int p = j * std::cos(ImageUtil::toRadian(static_cast<double>(s))) +
//						i * std::sin(ImageUtil::toRadian(static_cast<double>(s))) + r;
//					houghSpace[p * sigma + static_cast<int>(s / deltaSigma)]++;
//
//
//
//					s += deltaSigma;
//					if (s > 180)
//						break;
//				}
//			}
//			++ImageUtil::progressBar;
//		}
//	}
//
//	uint max = 0;
//	for (int i = 0; i < r * sigma; i++)
//	{
//		if (houghSpace[i] > max)
//			max = houghSpace[i];
//	}
//
//
//	ImageUtil::progressBar.reset(data.height * data.width, "检测直线....");
//	for (uint i = 0; i < data.height; i++)
//	{
//		for (uint j = 0; j < data.width; j++)
//		{
//			double s = 0;
//			while (true)
//			{
//				const int p = j * std::cos(ImageUtil::toRadian(static_cast<double>(s)))
//					+ i * std::sin(ImageUtil::toRadian(static_cast<double>(s))) + r;
//				if (houghSpace[p * sigma + static_cast<int>(s / deltaSigma)] > max * 0.9)
//				{
//					data[i][j] = static_cast<byte>(255);
//				}
//
//				s += deltaSigma;
//				if (s > 180)
//					break;
//			}
//
//			++ImageUtil::progressBar;
//		}
//	}
//
//	BYTE* houghSpaceImg = new BYTE[d * sigma];
//
//	for (int i = 0; i < d*sigma; i++)
//	{
//		houghSpaceImg[i] = ImageUtil::clamp(static_cast<double>(houghSpace[i]) / max * 255);
//	}
//
//	ImageUtil::outputImage(houghSpaceImg, sigma, d, 256, 8, data.rgbquad, "bitmap/houghSpace.bmp");
//
//	data.rgbquad[255].rgbBlue = 0;
//	data.rgbquad[255].rgbGreen = 0;
//
//	delete[] houghSpace;
//	delete[] cannyImg.pImg;
//	delete[] houghSpaceImg;
//	return data;
//}
