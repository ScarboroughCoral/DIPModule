#include "Algo.h"
#include <stdio.h>

void static swap(int a[], int i, int j)
{
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

int static partition(int a[], int left, int right, int povit)
{
	while (left <= right)
	{
		while (a[left] < povit) left++;
		while (a[right] > povit) right--;
		if (left <= right)
		{
			swap(a, left, right);
			left++;
			right--;
		}
	}
	return left;
}

void quicksort(int a[], int left, int right)
{
	if (left >= right) return;
	int povit = a[left + (right - left) / 2];
	int index = partition(a, left, right, povit);
	quicksort(a, left, index - 1);
	quicksort(a, index, right);
}