#pragma once

#define Edge_Dectect_Type_PREWITT 1
#define Edge_Dectect_Type_SOBEL 2
#define Edge_Dectect_Type_LOG 3
#define Edge_Dectect_Type_CANNY 4


void EdgeDetection(const char * from, const char * to, int type);
void Prewitt(const char * from, const char * to);
void Sobel(const char * from, const char * to);
void Log(const char * from, const char * to);
void Canny(const char * from, const char * to);