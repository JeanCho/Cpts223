/***************************************************************************
 *
 *  Sorting algorithms and counting work - Merge sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented mergesort
 *
 */

#ifndef __INSTRUMENTED_MS_H
#define __INSTRUMENTED_MS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;


void merge(vector<int> &a, vector<int> & tmpArray, int leftPos, int rightPos, int rightEnd, SortStats & stats)
{
	int leftEnd = rightPos -1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos +1; 

	while(leftPos <= leftEnd && rightPos <=rightEnd)
	{
		if(a[leftPos] <= a[rightPos])
		{
			tmpArray[tmpPos++]  = move(a[leftPos++]);
			stats.moves++;
			stats.compares++;
		}
		else
		{
			tmpArray[tmpPos++] = move(a[rightPos++]);
			stats.moves++;
			stats.compares++;
		}
		
	}

	while(leftPos<= leftEnd)
	{
		tmpArray[tmpPos++] = move(a[leftPos++]);
		stats.moves++;
		stats.compares++;
	}
	while(rightPos <= rightEnd)
	{
		tmpArray[tmpPos++] = move(a[rightPos++]);
		stats.moves++;
		stats.compares++;
	}

	for(int i =0; i<numElements; ++i, --rightEnd)
	{
		a[rightEnd] = move(tmpArray[rightEnd]);
		stats.moves++;
		stats.compares++;
	}
}

void mergeSort(vector<int> &a, vector<int> &tmpArray, int left, int right, SortStats & stats)
{
	if(left <right)
	{
		int center = (left+right)/2;
		mergeSort(a, tmpArray, left, center,stats);
		mergeSort(a,tmpArray, center+1, right, stats);
		merge(a,tmpArray,left,center+1,right, stats);
	}
}
void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    clock_t time_begin = clock();		// Please leave in place for stats

	// Begin sorting algorithm

	// Begin your merge sort code here
	// You're free to add more functions if you like, but vector<int> a must be sorted when done
	// NOTE: you must update stats with comparisons and moves as your algorithm runs
	//  The best example of updating the stats is available in the file:
	//  instrumentedBubbleSort.h
	vector<int> temporary = a;
	int left =0;
	int right = a.size()-1;
	
	mergeSort(a,temporary, left, right ,stats);
	// End sorting algorithm

    clock_t time_end = clock();			// Please leave in place for stats
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}



#endif
