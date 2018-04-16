#include <stdio.h>
#include <stdbool.h>

void cocktailsort(int* arr, int size);
void printArr(int* arr, int size);

int main() {

	int arr[] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
	printf("Unsorted Array:\n");
	printArr(arr, 20);
	cocktailsort(arr, 20);
	printf("Sorted Array:\n");
	printArr(arr, 20);

	return 0;
}

void cocktailsort(int* arr, int size) {
	int i; //current comparison index
	int last_i; //index of last swap
	int max_i = size - 2; //rightmost index where the last swap occurred
	int min_i = 0; //leftmost index where the last swap occurred
	
	int temp; //temp variable for swapping values
	bool bubbleUp = false; //bool for sort direction
	
	do { //while swaps are still being made
		last_i = -1;
		bubbleUp = !bubbleUp;
		if(bubbleUp) { //start from right
			for(i = min_i; i <= max_i; i++) { //for each element in the unsorted part of the array
				if(arr[i] > arr[i+1]) {
					//swap values
					temp = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = temp;		
					//record positon	
					last_i = i;
				}
			}
			max_i = last_i;
		} else { //start from left
			for(i = max_i; i >= min_i; i--) {
				if(arr[i] < arr[i-1]) {
					//swap values
					temp = arr[i];
					arr[i] = arr[i-1];
					arr[i-1] = temp;
					//record position
					last_i = i;
				}
			}
			min_i = last_i;
		}
	} while(last_i >= 0);
}

void printArr(int* arr, int size) {
	int i;
	for(i = 0; i < size; i++) {
		printf("%d", arr[i]);
		if(i == size - 1) {
			printf("\n");
		} else {
			printf(", ");
		}
	}
}
