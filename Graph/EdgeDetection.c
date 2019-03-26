#include "EdgeDetection.h"
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
			int newGray = *(*data + (i - 1) * info.width + (j - 1)) +
				*(*data + (i)* info.width + (j - 1)) +
				*(*data + (i + 1)* info.width + (j - 1)) +
				+*(*data + (i - 1)* info.width + (j)) +
				+*(*data + (i)* info.width + (j)) +
				+*(*data + (i + 1)* info.width + (j)) +
				+*(*data + (i - 1)* info.width + (j + 1)) +
				+*(*data + (i)* info.width + (j + 1)) +
				+*(*data + (i + 1)* info.width + (j + 1));
			newGray /= 9;
			*(*outData + i * info.width + j) = newGray;
		}
	}

	BMPWriter8(to, &header, &info, palette, outData);
}

void Sobel(const char * from, const char * to)
{
}

void Log(const char * from, const char * to)
{
}

void Canny(const char * from, const char * to)
{
}
