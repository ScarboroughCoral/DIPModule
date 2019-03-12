#include "BMPUtil.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

int BMPReader(const char* filename,BMFILEHEADER* header,INFOHEADER * info,RGBQUAD ** palette,RGBITEM ** data) {
	FILE *fp = fopen(filename, "rb");
	if (fp==NULL)
	{
		perror("File access error!cannot access file£º%s\n",filename);
		exit(0);
	}

	fread(header, 14, 1, fp);
	fread(info, sizeof(INFOHEADER), 1, fp);

	unsigned offset = *(int *)(header->offset);
	unsigned realWidth = info->sizeImage / info->height;
	unsigned rowPixelNumber = realWidth / sizeof(RGBITEM);
	unsigned remanentByteOfRow = realWidth % sizeof(RGBITEM);
	unsigned pixelCounts = rowPixelNumber * info->height;
	fseek(fp, offset, 0);


	*data = (RGBITEM *)malloc(pixelCounts * sizeof(RGBITEM));

	for (size_t i = 0; i < info->height; i++)
	{
		fread(*data + i * rowPixelNumber, sizeof(RGBITEM), rowPixelNumber, fp);
		fseek(fp, remanentByteOfRow, SEEK_CUR);
	}
	fclose(fp);
	return pixelCounts;
}


int BMPWriter(const char* filename, BMFILEHEADER* header, INFOHEADER * info,RGBQUAD ** palette, RGBITEM ** data) {
	FILE *fp = fopen(filename, "wb");
	if (fp == NULL)
	{
		perror("File access error!cannot access file£º%s\n", filename);
		exit(0);
	}

	unsigned offset = *(int *)(header->offset);
	unsigned realWidth = info->sizeImage / info->height;
	unsigned rowPixelNumber = realWidth / sizeof(RGBITEM);
	unsigned remanentByteOfRow = realWidth % sizeof(RGBITEM);
	unsigned pixelCounts = rowPixelNumber * info->height;
	fwrite(header, 14, 1, fp);
	fwrite(info, sizeof(INFOHEADER), 1, fp);
	fseek(fp, offset, 0);

	for (size_t i = 0; i < info->height; i++)
	{
		fwrite(*data + i * rowPixelNumber, sizeof(RGBITEM), rowPixelNumber, fp);
		fseek(fp, remanentByteOfRow, SEEK_CUR);
	}

	fclose(fp);
	return pixelCounts;
}