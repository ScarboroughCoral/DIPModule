#pragma once


typedef struct bitmapFileHeader {
	unsigned char type[2];
	unsigned size;
	unsigned char resvered1[2];
	unsigned char reserved2[2];
	unsigned offset;
} BMFILEHEADER;

typedef struct rgb {
	unsigned char r;
	unsigned char b;
	unsigned char g;
}RGBITEM;


typedef struct bitMapInfoHeader {
	unsigned infoHeaderSize;
	unsigned long width;
	unsigned long height;
	unsigned short planes;
	unsigned short colorCount;
	unsigned isCompressed;
	unsigned sizeImage;
	unsigned long xPelsPerMeter;
	unsigned long yPelsPerMeter;
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