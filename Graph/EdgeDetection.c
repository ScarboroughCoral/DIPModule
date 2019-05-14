
#include "BMPHelper.h"

void EdgeDetection(const char * from, const char * to, int type)
{
	switch (type)
	{
	case Edge_Dectect_Type_PREWITT:
		Prewitt(from, to);
		break;
	case Edge_Dectect_Type_SOBEL:
		Sobel(from, to);
		break;
	case Edge_Dectect_Type_LOG:
		Log(from, to);
		break;
	case Edge_Dectect_Type_CANNY:
		Canny(from, to);
		break;
	default:
		break;
	}
}

void Prewitt(const char * from, const char * to)
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
			if (i == 0 || (i == info.height - 1) || j == 0 || (j == info.width - 1))
			{
				*(*outData + i * info.width + j) = *(*data + i * info.width + j);
				continue;
			}
			int newGrayV = -*(*data + (i - 1) * info.width + (j - 1)) -
				*(*data + (i)* info.width + (j - 1)) -
				*(*data + (i + 1)* info.width + (j - 1)) +
				*(*data + (i - 1)* info.width + (j + 1)) +
				*(*data + (i)* info.width + (j + 1)) +
				*(*data + (i + 1)* info.width + (j + 1));
			int newGrayH = -*(*data + (i - 1) * info.width + (j - 1)) +
				*(*data + (i + 1)* info.width + (j - 1)) -
				*(*data + (i - 1)* info.width + (j)) +
				*(*data + (i + 1)* info.width + (j)) -
				*(*data + (i - 1)* info.width + (j + 1)) +
				*(*data + (i + 1)* info.width + (j + 1));
			int newGray = newGrayV + newGrayH;
			if (newGray>255)
			{
				newGray = 255;
			}
			if (newGray < 0)
			{
				newGray = 0;
			}
			*(*outData + i * info.width + j) = newGray;
		}
	}

	BMPWriter8(to, &header, &info, palette, outData);
}

void Sobel(const char * from, const char * to)
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
			if (i == 0 || (i == info.height - 1) || j == 0 || (j == info.width - 1))
			{
				*(*outData + i * info.width + j) = *(*data + i * info.width + j);
				continue;
			}
			int newGrayV = -*(*data + (i - 1) * info.width + (j - 1)) -
				*(*data + (i)* info.width + (j - 1))*2 -
				*(*data + (i + 1)* info.width + (j - 1)) +
				*(*data + (i - 1)* info.width + (j + 1)) +
				*(*data + (i)* info.width + (j + 1))*2 +
				*(*data + (i + 1)* info.width + (j + 1));
			int newGrayH = -*(*data + (i - 1) * info.width + (j - 1)) +
				*(*data + (i + 1)* info.width + (j - 1)) -
				*(*data + (i - 1)* info.width + (j))*2 +
				*(*data + (i + 1)* info.width + (j))*2 -
				*(*data + (i - 1)* info.width + (j + 1)) +
				*(*data + (i + 1)* info.width + (j + 1));
			int newGray = newGrayV + newGrayH;
			if (newGray > 255)
			{
				newGray = 255;
			}
			if (newGray<0)
			{
				newGray = 0;
			}
			*(*outData + i * info.width + j) = newGray;
		}
	}

	BMPWriter8(to, &header, &info, palette, outData);
}

/*
1.首先用高斯函数对图像作平滑滤波处理
2.再使用Laplacian算子边缘检测
*/
void Log(const char * from, const char * to)
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
			if (i == 0 || (i == info.height - 1) || j == 0 || (j == info.width - 1))
			{
				*(*outData + i * info.width + j) = *(*data + i * info.width + j);
				continue;
			}
			if (i == 1 || (i == info.height - 2) || j == 1 || (j == info.width - 2))
			{
				*(*outData + i * info.width + j) = *(*data + i * info.width + j);
				continue;
			}
			int newGray = *(*data + (i - 2) * info.width + j)*(-1) +
				*(*data + (i - 1) * info.width + (j - 1))*(-1) +
				*(*data + (i - 1) * info.width + j)*(-2) +
				*(*data + (i - 1) * info.width + (j + 1))*(-1) +
				*(*data + i * info.width + (j - 2))*(-1) +
				*(*data + i * info.width + (j - 1))*(-2) +
				*(*data + i * info.width + j) * 16 +
				*(*data + i * info.width + (j + 1))*(-2) +
				*(*data + i * info.width + (j + 2))*(-1) +
				*(*data + (i + 1) * info.width + (j - 1))*(-1) +
				*(*data + (i + 1) * info.width + j)*(-2) +
				*(*data + (i + 1) * info.width + (j + 1))*(-1) +
				*(*data + (i + 2) * info.width + j)*(-1);

			if (newGray > 255)
			{
				newGray = 255;
			}
			if (newGray < 0)
			{
				newGray = 0;
			}
			*(*outData + i * info.width + j) = newGray;
		}
	}

	BMPWriter8(to, &header, &info, palette, outData);
}


void Canny(const char * from, const char * to)
{
}
