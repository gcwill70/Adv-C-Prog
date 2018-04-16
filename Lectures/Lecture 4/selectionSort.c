#include <stdio.h>
void selectionSort (int* arr, int size);
int main() {
	int arr[] = {7,6,5,34,0,2,67,45,21,3};
	selectionSort(arr,10);
	int i;
	for (i = 0; i < 10; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}

void selectionSort(int* r, int size) {
	int i, max_index, j, temp;
	for (i = size-1; i > 0; i--) {
		max_index = 0;
		for (j = 0; j <= i; j++) {
			if (r[j] >= r[max_index]) {
				max_index = j;
			}
		}
		temp = r[i];
		r[i] = r[max_index];
		r[max_index] = temp;
	}
}
