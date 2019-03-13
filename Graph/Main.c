#include <stdlib.h>
#include "BMPHelper.h"


int main(){
	
	
	/*
	第一次作业：BMP文件处理
	*/
	//BMPResolver();

	/*
	第二次作业：直方图处理
	*/
	//HistogramStatic();
	BMFILEHEADER header;
	INFOHEADER info;

	RGBQUAD ** palette = malloc(sizeof(RGBQUAD*));
	unsigned char **a = malloc(sizeof(unsigned char *));

	BMPReader8("grayHistogram.bmp", &header, &info, palette, a);
	BMPWriter8("8result.bmp", &header, &info, palette, a);

	
	
	system("pause");
	return 0;
}