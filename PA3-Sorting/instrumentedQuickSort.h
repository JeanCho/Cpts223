/***************************************************************************
 *
 *  Sorting algorithms and counting work - Quicksort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented quicksort
 *
 */

#ifndef __INSTRUMENTED_QS_H
#define __INSTRUMENTED_QS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

int partition(vector<int> &a, int low, int high, SortStats & stats )
{
	int pivot = a[high];
	int i =(low-1);

	for(int j = low; j <= high-1; j++)
	{
		if(a[j] <= pivot)
		{
			i++;
			swap(a[i],a[j]);
			stats.moves++;
			stats.compares++;
			
		}
	}
	swap(a[i+1],a[high]);
	stats.moves++;
	
	return (i+1);
}

void quickSort( vector<int> &a, int low, int high,SortStats & stats)
{
	if(low<high)
	{
		int pi = partition(a,low,high, stats);
		quickSort(a,low,pi-1,stats);
		quickSort(a,pi+1,high,stats);
	}
}

void instrumentedQuickSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();		// Please leave in place for stats


	// Begin sorting algorithm

	// Begin your quicksort code here
	// You're free to add more functions if you like, but vector<int> a must be sorted when done
	// NOTE: you must update stats with comparisons and moves as your algorithm runs
	//  The best example of updating the stats is available in the file:
	//  instrumentedBubbleSort.h

	// End sorting algorithm
	int low =0;
	int high = a.size()-1;
	quickSort(a, low, high, stats);
	clock_t time_end = clock();			// Please leave in place for stats
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}




#endif
