#ifdef SELECTION_SORT
#include "pa01.h"
void selectSort(int * arr, int size)
//arr : the array to be sorted
//size : the number of elements in the array

// In each iteration, the number of elements to be sorted shrinks by one
// i.e., one element is at the correct position.
//
// Among the remaining elements, find the smallest value and put it 
// before the other unsorted elements
{

	//TODO: Fill this in to complete PA01.
	//LOCAL VARIABLES
	int i = 0; //master index pointer to iterate through arr once
	int j = 0; //sub-index to determine the minimum value to the right of arr[i]
	int k = 0; //index to point to the min value that is to the right of arr[i];

	//CODE
	
	for (i = 0; i < size; i++) //iterate through arr
	{
		//find the minimum value (arr[k]) to the right of arr[i]
		k = i; //the index of the current minimum value is i initially
		for (j = i; j < size; j++) //iterate throught the remainder of arr
		{
			if (arr[j] < arr[k]) //determine if the currently-checked arr value is less than arr[k]
			{
				k = j; //update k to be location of newly-found min value
			}		
		} //k is now pointing to the minimum value that is in the unsorted part of arr

		//swap arr[k] with arr[i] if arr[k] < arr[i]
		if (arr[k] < arr[i])
		{
			swap(&arr[i],&arr[k]);
		}
	}
}
#endif
