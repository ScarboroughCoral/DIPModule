#include "BMPHelper.h"
#include <stdio.h>



/*
区域分割：基于种子值的区域增长
给定种子值和参数T，开始区域增长
增长结束条件：所有像素点都已经遍历过
不同区域颜色使用“种子索引/总种子数目*255”作为灰度值

*/
void regionSegmentSeed(const char * src, const char * dest, Point * seeds, int length,int t)
{
	//BMFILEHEADER header;
	//INFOHEADER info;


	////原图像素数据
	//unsigned char ** data = malloc(sizeof(unsigned char*));
	////原图调色板数据
	//RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	////读取图片，返回像素数
	//unsigned pixelCounts = BMPReader8(src, &header, &info, palette, data);

	////处理后的输出图片的像素数据
	//unsigned char **outData = malloc(sizeof(unsigned char*));
	//*outData = malloc(pixelCounts);



	for (size_t i = 0; i < length; i++)
	{

	}


	//BMPWriter8(dest, &header, &info, palette, outData);
}

void regionSegmentWithoutSeed(const char * src, const char * dest)
{
}
