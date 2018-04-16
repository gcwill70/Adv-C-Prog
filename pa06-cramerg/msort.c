#include "msort.h"
#include "student.h"
#include <stdio.h>

#ifndef OMIT_MSORT
void msort(Student * base, int nel, int (*compar)(const void *, const void *)) {
	
	//Base case: if the array has one or fewer elements, it's already sorted
	//so just return.

	//FILL IN
	if(nel < 2) {return;}	
	//Inductive case: split the array in two, sort the two pieces with msort,
	//merge the	sorted pieces
		
	//We're going to do this without explicitly creating the two separate arrays
	//We'll take advantage of the fact that to C, an array is just a pointer to
	//a region of memory. If we call msort on base, but pass in a smaller number
	//of elements, it will sort just that subarray. Similarly, if we call msort
	//but pass in the address of an element in the middle of the array, it will
	//sort the array *starting* from that element.
		
	//1. Find the midpoint of the array
		
	//FILL IN
	int mid = nel/2;
	//2a. Sort the first half of the array (remember to adjust the # elements)
	
	//FILL IN
	msort(base,mid,compar);
	//2b. Sort the second half of the array. Pass in the address of the 
	//beginning of the second half of the array (remember to use the right # of 
	//elements)
	
	//FILL IN
	msort(&base[mid],nel-mid,compar);
	
	//3a. Merge the two arrays (use merge)
	
	//FILL IN
	Student * merged = merge(base,mid,&base[mid],nel-mid,compar);
	//3b. Copy the merged array over top of the original array (use copy)
	//Don't forget to free the array you no longer need!
	
	//FILL IN
	copy(base,merged,nel);
	free(merged);
	return;
}
#endif

#ifndef OMIT_MERGE
Student * merge(Student * base1, int nel1, Student * base2, int nel2, int (*compar)(const void *, const void *)) {
	
	//1. Allocate space for the returned merged array
	
	//FILL IN
	Student * merged = malloc((nel1+nel2)*sizeof(Student));	
	//2. Create indices to keep track of where you are in the three arrays

	//FILL IN
	int i = 0; //index for merged array
	int j = 0;//index for base1
	int k = 0;//index for base2
	//3. Go through base1 and base2, and merge them into the returned array

	//FILL IN
	while(true) //the only way to exit is to reach the break
	{
		if (compar(&base1[j],&base2[k]) <= 0) //base1 element is smaller or equal
		{
			merged[i++] = base1[j++];
		}
		else //base2 element is larger
		{
			merged[i++] = base2[k++];
		}
		if (j >= nel1 || k >= nel2)
		{
			break;
		}
	}

	while (! (j >= nel1))//base2 got fully assigned to merged but base1 didnt
	{
		merged[i++] = base1[j++];		
	}
	while (! (k >= nel2))//base1 got fully assigned to merged but base2 didnt
	{
		merged[i++] = base2[k++];
	}

	//4. Return the merged array

	//FILL IN
	return merged;	
}


void copy(Student * to, Student * from, int nel) {
	/*
	An efficient implementation of this would use memcpy:
	memcpy(to, from, nel * width);

	We will do an element-by-element copy so you can see how it is done
	*/
	
	//loop over the from array and copy it byte by byte to the to array.
	for (int i = 0; i < nel; i++) {
		to[i] = from[i];
	}
	
	return;
}
#endif
