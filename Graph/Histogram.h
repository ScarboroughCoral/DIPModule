#pragma once


void outputGrayscaleHistogram(const char * filename, double distribution[], INFOHEADER *origin);
void outputGrayscaleHistogramWithThresholdMark(const char * filename, double distribution[], INFOHEADER *origin,int threshold);