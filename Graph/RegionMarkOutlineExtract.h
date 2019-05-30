#pragma once

void RegionMark(const char *from, const char *to);
void OutlineExtract(const char *from, const char *to);
void markRegion(unsigned  *markMatrix, unsigned i, unsigned j, int width, int height, int tag);