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
	//unsigned color = info->colorUsed;

	*palette = (RGBQUAD *)malloc(info->colorUsed * sizeof(RGBQUAD));

	fread(*palette, sizeof(RGBQUAD), info->colorUsed, fp);

	*data = (RGBITEM *)malloc(pixelCounts * sizeof(RGBITEM));

	for (size_t i = 0; i < info->height; i++)
	{
		fread(*data + i * rowPixelNumber, sizeof(RGBITEM), rowPixelNumber, fp);
		fseek(fp, remanentByteOfRow, SEEK_CUR);
	}
	fclose(fp);
	return pixelCounts;
}

int BMPReader8(const char* filename, BMFILEHEADER* header, INFOHEADER * info, RGBQUAD ** palette, unsigned char ** data) {
	FILE *fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		perror("File access error!cannot access file£º%s\n", filename);
		exit(0);
	}

	fread(header, 14, 1, fp);
	fread(info, sizeof(INFOHEADER), 1, fp);
	unsigned offset = *(int *)(header->offset);
	unsigned realWidth = info->sizeImage / info->height;
	unsigned rowPixelNumber = info->width;
	unsigned remanentByteOfRow = realWidth - info->width;
	unsigned pixelCounts = rowPixelNumber * info->height;

	*palette = (RGBQUAD *)malloc(info->colorUsed * sizeof(RGBQUAD));

	fread(*palette, sizeof(RGBQUAD), info->colorUsed, fp);

	*data = malloc(pixelCounts);

	for (size_t i = 0; i < info->height; i++)
	{
		fread(*data + i * rowPixelNumber, 1, rowPixelNumber, fp);
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
	int t = sizeof(INFOHEADER);
	fwrite(*palette, sizeof(RGBQUAD), info->colorUsed, fp);

	for (size_t i = 0; i < info->height; i++)
	{
		fwrite(*data + i * rowPixelNumber, sizeof(RGBITEM), rowPixelNumber, fp);
		fseek(fp, remanentByteOfRow, SEEK_CUR);
	}

	fclose(fp);
	return pixelCounts;
}

int BMPWriter8(const char* filename, BMFILEHEADER* header, INFOHEADER * info, RGBQUAD ** palette, unsigned char ** data) {
	FILE *fp = fopen(filename, "wb");
	if (fp == NULL)
	{
		perror("File access error!cannot access file£º%s\n", filename);
		exit(0);
	}

	unsigned offset = *(int *)(header->offset);
	unsigned realWidth = info->sizeImage / info->height;
	unsigned rowPixelNumber = info->width;
	unsigned remanentByteOfRow = realWidth - info->width;
	unsigned pixelCounts = rowPixelNumber * info->height;
	fwrite(header, 14, 1, fp);
	fwrite(info, sizeof(INFOHEADER), 1, fp);
	int t = sizeof(INFOHEADER);
	fwrite(*palette, sizeof(RGBQUAD), info->colorUsed, fp);

	for (size_t i = 0; i < info->height; i++)
	{
		//long p = *data;
		fwrite((*data) + i * rowPixelNumber, rowPixelNumber, 1, fp);
		fseek(fp, remanentByteOfRow, SEEK_CUR);
	}

	fclose(fp);
	return pixelCounts;
}

void BMP24To8Gray(const char * from, const char * to) {
	BMFILEHEADER fromHeader;
	INFOHEADER fromInfo;


	RGBITEM ** fromData = malloc(sizeof(RGBITEM*));
	RGBQUAD ** fromPalette = malloc(sizeof(RGBQUAD*));

	int fromPixelNumber = BMPReader(from, &fromHeader, &fromInfo, fromPalette, fromData);




	



	BMFILEHEADER toHeader = fromHeader;
	INFOHEADER toInfo = fromInfo;
	// set info
	toInfo.colorCount = 8;
	toInfo.infoHeaderSize = 40;
	toInfo.planes = 1;
	toInfo.sizeImage = (toInfo.width+3)/4*4*toInfo.height;
	toInfo.colorUsed = 256;


	RGBQUAD ** toPalette = malloc(sizeof(RGBQUAD*));
	*toPalette = malloc(256 * sizeof(RGBQUAD));
	for (size_t i = 0; i < 256; i++)
	{
		((*toPalette) + i)->r = ((*toPalette) + i)->b = ((*toPalette) + i)->g = i;
	}

	unsigned char **toData = malloc(sizeof(unsigned char *));
	*toData = malloc(fromPixelNumber);

	for (size_t i = 0; i < fromPixelNumber; i++)
	{
		*(*toData+i)= ((*fromData + i)->r * 299 + (*fromData + i)->g * 587 + (*fromData + i)->b * 114 + 500) / 1000;
	}

	*(unsigned *)toHeader.offset = sizeof(toHeader) + sizeof(toInfo) + 256 * sizeof(RGBQUAD);
	*(unsigned *)toHeader.size = toHeader.offset + toInfo.sizeImage;




	BMPWriter8(to, &toHeader, &toInfo, toPalette, toData);




}