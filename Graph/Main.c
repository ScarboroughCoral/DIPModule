#include <stdlib.h>
#include "BMPHelper.h"
#include <stdio.h>

#pragma warning(disable : 4996)

int main(){
	
	int a, b, c, d, e, f;

	const char * buffer = "1 2 3 4 5 6";

	int result = sscanf(buffer, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

	printf("输入了%d个数，分别为%d %d %d %d %d %d",result, a, b, c, d, e, f);
	
	/*
	第一次作业：BMP文件处理
	*/
	//BMPResolver();

	/*
	第二次作业：直方图处理
	*/
	//HistogramStatic();
	
	/*
	第三次作业：空间域滤波
	*/

	/*SpatialDomainFilter("gray1.bmp", "gray2.bmp", TYPE_AVERAGE);
	for (size_t i = 0; i < 2; i++)
	{
		SpatialDomainFilter("gray2.bmp", "gray2.bmp", TYPE_AVERAGE);
	}
	SpatialDomainFilter("gray1.bmp", "gray3.bmp", TYPE_MEDIAN);
	for (size_t i = 0; i < 2; i++)
	{
		SpatialDomainFilter("gray3.bmp", "gray3.bmp", TYPE_AVERAGE);
	}*/
	system("pause");
	return 0;
}