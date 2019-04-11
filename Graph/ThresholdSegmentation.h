#pragma once

#define THRESHOLD_SEED 1
#define THRESHOLD_ITERATION 2
#define THRESHOLD_OSTU 3
void ThresholdSegment(const char * from,const char * to,int type,double param);
void seed(const char * from, const char * to, double k);
void iteration(const char * from, const char * to, double e);
void ostu(const char * from, const char * to);
