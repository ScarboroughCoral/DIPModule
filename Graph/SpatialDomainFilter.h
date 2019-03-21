#pragma once

#define TYPE_AVERAGE 1
#define TYPE_MEDIAN 2

void SpatialDomainFilter(const char * src,const char * output,int type);
void AverageProcessing(const char * src, const char * output);
void MedianFiltering(const char * src, const char * output);