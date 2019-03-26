#include <stdlib.h>
#include "BMPHelper.h"
#include <stdio.h>

#pragma warning(disable : 4996)

int main(){
	
	/*int a, b, c, d, e, f;

	const char * buffer = "1 2 3 4 5 6";

	int result = sscanf(buffer, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

	printf("输入了%d个数，分别为%d %d %d %d %d %d",result, a, b, c, d, e, f);*/
	
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

	/*SpatialDomainFilter("3-1.bmp", "3-2.bmp", TYPE_AVERAGE);
	SpatialDomainFilter("3-1.bmp", "3-3.bmp", TYPE_MEDIAN);*/

	/*SpatialDomainFilter("3-1.bmp", "3-2.bmp", TYPE_AVERAGE);
	for (size_t i = 0; i < 2; i++)
	{
		SpatialDomainFilter("3-2.bmp", "3-2-3.bmp", TYPE_AVERAGE);
	}
	SpatialDomainFilter("3-1.bmp", "3-3.bmp", TYPE_MEDIAN);
	for (size_t i = 0; i < 2; i++)
	{
		SpatialDomainFilter("3-3.bmp", "3-3-3.bmp", TYPE_MEDIAN);
	}
*/

	/*
	第四次作业：图像变换
	*/


	//图像缩放

	//transform("3-3.bmp", "scale.bmp", TRANSFORM_SCALE, 1.5, 1.5);

	//图像平移

	//transform("3-3.bmp", "shift.bmp", TRANSFORM_SHIFT, -20, -200);

	//图像镜像
	////水平
	//transform("3-3.bmp", "x-mirror.bmp", TRANSFORM_MIRROR, 1, 0);
	////垂直
	//transform("3-3.bmp", "y-mirror.bmp", TRANSFORM_MIRROR, -1, 0);

	//图像旋转

	transform("3-3.bmp", "rotate.bmp", TRANSFORM_ROTATE, PI/8, 0);

	system("pause");
	return 0;
}