#pragma once


typedef struct bitmapFileHeader {
	unsigned char type[2];
	unsigned char size[4];
	unsigned char resvered1[2];
	unsigned char reserved2[2];
	unsigned char offset[4];
} BMFILEHEADER;

typedef struct rgb {
	unsigned char b;
	unsigned char g;
	unsigned char r;
}RGBITEM;


typedef struct bitMapInfoHeader {
	unsigned infoHeaderSize;
	long width;
	long height;
	unsigned short planes;
	unsigned short colorCount;
	unsigned isCompressed;
	unsigned sizeImage;
	long xPelsPerMeter;
	long yPelsPerMeter;
	unsigned colorUsed;
	unsigned colorImportant;
}INFOHEADER;

typedef struct RGBQUAD {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char reserved;

}RGBQUAD ;

void BMPResolver();