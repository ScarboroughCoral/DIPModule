#include "BMP.h"
#include<stdlib.h>
#include<stdio.h>

#pragma warning(disable : 4996)

void BMPResolver() {
	FILE * fp = fopen("width.bmp", "rb");
	if (fp == NULL)
	{
		getchar();
		return;
	}
	BMFILEHEADER header;
	INFOHEADER info;
	fread(&header, sizeof(header), 1, fp);
	fread(&info, sizeof(info), 1, fp);
	RGBQUAD * prgbquad = (RGBQUAD *)malloc(info.colorUsed * sizeof(RGBQUAD));
	fread(prgbquad, sizeof(RGBQUAD), info.colorUsed, fp);
	//fseek(fp, header.offset, 0);
	RGBITEM *pitem = (RGBITEM *)malloc(info.sizeImage);

	unsigned itemCounts = info.sizeImage /3;
	fread(pitem, sizeof(RGBITEM), itemCounts, fp);


	//修改单色
	for (size_t i = 0; i < itemCounts; i++)
	{
		//printf("%d\n", pitem->r);
		(pitem+i)->r = 0;
		//(pitem+i)->g = 0;
		(pitem + i)->b = 0;
	}

	//灰度化
	int gray;
	/*for (size_t i = 0; i < itemCounts; i++)
	{
		gray = ((pitem + i)->r * 299 + (pitem + i)->g * 587 + (pitem + i)->b * 114 + 500) / 1000;
		(pitem + i)->r = gray;
		(pitem + i)->g = gray;
		(pitem + i)->b = gray;
	}*/

	//灰度图反色
	/*for (size_t i = 0; i < itemCounts; i++)
	{
		gray = ((pitem + i)->r * 299 + (pitem + i)->g * 587 + (pitem + i)->b * 114 + 500) / 1000;
		(pitem + i)->r = 255 - gray;
		(pitem + i)->g = 255 - gray;
		(pitem + i)->b = 255 - gray;
	}*/

	char * result = "singleColor1.bmp";
	FILE * rp = fopen(result, "wb");
	if (rp == NULL)
	{
		return;
	}
	fwrite(&header, sizeof(header), 1, rp);
	fwrite(&info, sizeof(info), 1, rp);
	//fseek(rp, header.offset, 0);
	fwrite(prgbquad, sizeof(RGBQUAD), info.colorUsed, rp);
	fwrite(pitem, sizeof(RGBITEM), info.sizeImage / 3, rp);
	printf("Output singleColor.bmp  successfully!\n");
}