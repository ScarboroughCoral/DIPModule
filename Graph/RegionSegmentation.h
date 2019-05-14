#pragma once

typedef struct {
	unsigned x;
	unsigned y;
} Point;


void regionSegmentSeed(const char * src, const char * dest, Point* seeds,int length,int t);
void regionSegmentWithoutSeed(const char * src, const char * dest);