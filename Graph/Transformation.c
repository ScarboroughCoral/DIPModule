#include "Transformation.h"
#include "BMPHelper.h"
#include <math.h>

void transform(const char * from, const char * to, int type, double xSize, double ySize)
{
	switch (type)
	{
	case TRANSFORM_SCALE:
		scale(from, to, xSize,ySize);
		break;
	case TRANSFORM_SHIFT:
		shift(from, to, xSize, ySize);
		break;
	case TRANSFORM_MIRROR:
		mirror(from, to, xSize);
		break;
	case TRANSFORM_ROTATE:
		rotate(from, to, xSize);
		break;
	default:
		break;
	}
}

void scale(const char * from, const char * to, double xScale, double yScale)
{
	BMFILEHEADER header;
	INFOHEADER info;

	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(from, &header, &info, palette, data);


	unsigned char **outData = malloc(sizeof(unsigned char*));

	INFOHEADER outInfo = info;
	BMFILEHEADER outHeader = header;
	if (xScale>1||yScale>1)
	{
		outInfo.width *= xScale;
		outInfo.height *= yScale;
		outInfo.sizeImage = (outInfo.width  +3)/4*4 * outInfo.height;
		*(int *)outHeader.size += outInfo.sizeImage - info.sizeImage;
		*outData = malloc(outInfo.sizeImage);

	}
	else
	{
		*outData = malloc(pixelCounts);
	}
	for (unsigned i = 0; i < outInfo.height; i++)
	{

		for (unsigned j = 0; j < outInfo.width; j++)
		{

			*(*outData + i * outInfo.width + j) = WHITE;
		}
	}
	for (unsigned i = 0; i < outInfo.height; i++)
	{

		for (unsigned j = 0; j < outInfo.width; j++)
		{
			
			int originI = (i / yScale);
			int originJ = (j / xScale);

			*(*outData + i * outInfo.width + j) = *(*data + originI * info.width + originJ);
		}
	}


	BMPWriter8(to, &outHeader, &outInfo, palette, outData);
}

void shift(const char * from, const char * to, int xoffset, int yoffset)
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
			
			*(*outData + i * info.width + j) = WHITE;
		}
	}
	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{
			if (!(j + xoffset >= info.width || j + xoffset < 0 || i + yoffset < 0 || i + yoffset >= info.height))
			{

				*(*outData + (i+ yoffset) * info.width + j+xoffset) = *(*data + i * info.width + j);
			}
			//*(*outData + i * info.width + j) = WHITE;
		}
	}
		

	BMPWriter8(to, &header, &info, palette, outData);
}

void mirror(const char * from, const char * to,int direction)
{
	BMFILEHEADER header;
	INFOHEADER info;

	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(from, &header, &info, palette, data);

	unsigned char **outData = malloc(sizeof(unsigned char*));

	*outData = malloc(pixelCounts);

	if (direction>=0)//Ë®Æ½¾µÏñ
	{
		for (unsigned i = 0; i < info.height; i++)
		{

			for (unsigned j = 0; j < info.width; j++)
			{
				
				*(*outData + i * info.width + j) = *(*data + i * info.width + info.width - 1 - j);
			}
		}
	}
	else//´¹Ö±¾µÏñ
	{
		for (unsigned i = 0; i < info.height; i++)
		{

			for (unsigned j = 0; j < info.width; j++)
			{
				*(*outData + i * info.width + j) = *(*data + (info.height - i - 1) * info.width + j);
			}
		}
	}
	

	BMPWriter8(to, &header, &info, palette, outData);
}

void rotate(const char * from, const char * to, double angle)
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

			*(*outData + i * info.width + j) = WHITE;
		}
	}
	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{


			int originI = sin(angle)*j+cos(angle)*i +0.5;
			int originJ = cos(angle)*j-sin(angle)*i +0.5;
			if (originJ >= info.width || originJ < 0 || originI < 0 || originI >= info.height) {
				continue;
			}
			*(*outData + i * info.width + j) = *(*data + originI * info.width + originJ);
		}
	}


	BMPWriter8(to, &header, &info, palette, outData);
}
