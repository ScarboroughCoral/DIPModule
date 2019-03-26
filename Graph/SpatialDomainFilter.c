#include "BMPHelper.h"
#include <stdio.h>
#include "Algo.h"

void SpatialDomainFilter(const char * src, const char * output, int type) {
	switch (type)
	{
	case TYPE_AVERAGE:
		AverageProcessing(src, output);
		break;
	case TYPE_MEDIAN:
		MedianFiltering(src, output);
		break;
	default:
		break;
	}
}

void AverageProcessing(const char * src, const char * output)
{
	BMFILEHEADER header;
	INFOHEADER info;


	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(src, &header, &info, palette, data);

	unsigned char **outData = malloc(sizeof(unsigned char*));

	*outData = malloc(pixelCounts);


	for (unsigned i = 0; i < info.height; i++)
	{
		
		for (unsigned j = 0; j < info.width; j++)
		{
			if (i == 0 ||( i == info.height - 1)|| j == 0 || (j == info.width - 1))
			{
				*(*outData + i * info.width + j) = *(*data + i * info.width + j);
				continue;
			}
			int newGray = *(*data + (i - 1) * info.width + (j - 1)) +
				*(*data + (i)* info.width + (j - 1)) +
				*(*data + (i + 1)* info.width + (j - 1)) +
				*(*data + (i - 1)* info.width + (j)) +
				*(*data + (i)* info.width + (j)) +
				*(*data + (i + 1)* info.width + (j)) +
				*(*data + (i - 1)* info.width + (j + 1)) +
				*(*data + (i)* info.width + (j + 1)) +
				*(*data + (i + 1)* info.width + (j + 1));
			newGray /= 9;
			*(*outData + i * info.width+j) = newGray;
		}
	}

	BMPWriter8(output, &header, &info, palette, outData);

}

void MedianFiltering(const char * src, const char * output)
{
	BMFILEHEADER header;
	INFOHEADER info;


	unsigned char ** data = malloc(sizeof(unsigned char*));
	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned pixelCounts = BMPReader8(src, &header, &info, palette, data);

	unsigned char **outData = malloc(sizeof(unsigned char*));

	*outData = malloc(pixelCounts);


	for (unsigned i = 0; i < info.height; i++)
	{

		for (unsigned j = 0; j < info.width; j++)
		{
			if (i == 0 || (i == info.height - 1) || j == 0 || (j == info.width - 1))
			{
				if (i==0&&j==0)
				{

					int newGrays[] = { *(*data + (i)* info.width + (j)) ,
										*(*data + (i + 1)* info.width + (j)) ,
										*(*data + (i)* info.width + (j + 1)) ,
										*(*data + (i + 1)* info.width + (j + 1)) };
					quicksort(newGrays, 0, 3);
					int newGray = newGrays[2];
					*(*outData + i * info.width + j) = newGray;
				}
				else if (i==0&& j == info.width - 1)
				{
					int newGrays[] = { *(*data + (i)* info.width + (j - 1)) ,
									*(*data + (i + 1)* info.width + (j - 1)) ,
									*(*data + (i)* info.width + (j)) ,
									*(*data + (i + 1)* info.width + (j)) };
					quicksort(newGrays, 0, 3);
					int newGray = newGrays[2];
					*(*outData + i * info.width + j) = newGray;
				}
				else if (i == info.height - 1&&j==0)
				{
					int newGrays[] = { *(*data + (i - 1)* info.width + (j)) ,
										*(*data + (i)* info.width + (j)) ,
										*(*data + (i - 1)* info.width + (j + 1)) ,
										*(*data + (i)* info.width + (j + 1)) };
					quicksort(newGrays, 0, 3);
					int newGray = newGrays[2];
					*(*outData + i * info.width + j) = newGray;
				}
				else if (i == info.height - 1&& j == info.width - 1)
				{
					int newGrays[] = { *(*data + (i - 1) * info.width + (j - 1)) ,
										*(*data + (i)* info.width + (j - 1)) ,
										*(*data + (i - 1)* info.width + (j)) ,
										*(*data + (i)* info.width + (j))};
					quicksort(newGrays, 0, 3);
					int newGray = newGrays[2];
					*(*outData + i * info.width + j) = newGray;
				}
				else if (i == 0)
				{
					int newGrays[] = { *(*data + (i)* info.width + (j - 1)) ,
									*(*data + (i + 1)* info.width + (j - 1)) ,
									*(*data + (i)* info.width + (j)) ,
									*(*data + (i + 1)* info.width + (j)) ,
									*(*data + (i)* info.width + (j + 1)) ,
									*(*data + (i + 1)* info.width + (j + 1)) };
					quicksort(newGrays, 0, 5);
					int newGray = newGrays[3];
					*(*outData + i * info.width + j) = newGray;
				}
				else if (j == 0)
				{
					int newGrays[] = {*(*data + (i - 1)* info.width + (j)) ,
									*(*data + (i)* info.width + (j)) ,
									*(*data + (i + 1)* info.width + (j)) ,
									*(*data + (i - 1)* info.width + (j + 1)) ,
									*(*data + (i)* info.width + (j + 1)) ,
									*(*data + (i + 1)* info.width + (j + 1)) };
					quicksort(newGrays, 0, 5);
					int newGray = newGrays[3];
					*(*outData + i * info.width + j) = newGray;
				}
				else if (i == info.height - 1)
				{
					int newGrays[] = { *(*data + (i - 1) * info.width + (j - 1)) ,
										*(*data + (i)* info.width + (j - 1)) ,
										*(*data + (i - 1)* info.width + (j)) ,
										*(*data + (i)* info.width + (j)) ,
										*(*data + (i - 1)* info.width + (j + 1)) ,
										*(*data + (i)* info.width + (j + 1)) };
					quicksort(newGrays, 0, 5);
					int newGray = newGrays[3];
					*(*outData + i * info.width + j) = newGray;
				}
				else if (j == info.width - 1)
				{
				int newGrays[] = { *(*data + (i - 1) * info.width + (j - 1)) ,
									*(*data + (i)* info.width + (j - 1)) ,
									*(*data + (i + 1)* info.width + (j - 1)) ,
									*(*data + (i - 1)* info.width + (j)) ,
									*(*data + (i)* info.width + (j)) ,
									*(*data + (i + 1)* info.width + (j)) };
				quicksort(newGrays, 0, 5);
				int newGray = newGrays[3];
					*(*outData + i * info.width + j) = newGray;
				}
				continue;
			}
			int newGrays[] = { *(*data + (i - 1) * info.width + (j - 1)) ,
				*(*data + (i)* info.width + (j - 1)) ,
				*(*data + (i + 1)* info.width + (j - 1)) ,
				*(*data + (i - 1)* info.width + (j)) ,
				*(*data + (i)* info.width + (j)) ,
				*(*data + (i + 1)* info.width + (j)) ,
				*(*data + (i - 1)* info.width + (j + 1)) ,
				*(*data + (i)* info.width + (j + 1)) ,
				*(*data + (i + 1)* info.width + (j + 1)) };
			quicksort(newGrays, 0, 8);
			int newGray = newGrays[4];
			*(*outData + i * info.width + j) = newGray;
		}
	}

	BMPWriter8(output, &header, &info, palette, outData);
}
