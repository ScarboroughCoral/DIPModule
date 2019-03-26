#pragma once

#define TRANSFORM_SCALE 1
#define TRANSFORM_SHIFT 2
#define TRANSFORM_MIRROR 3
#define TRANSFORM_ROTATE 4
#define TRANSFORM_TRANSPARENT 5


void transform(const char * from, const char * to, int type,double x,double y);

void scale(const char * from, const char * to, double xScale,double yScale);

void shift(const char * from, const char * to, int xoffset, int yoffset);

void mirror(const char * from, const char * to,int direction);

void rotate(const char * from, const char * to, double angle);


