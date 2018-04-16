#include <stdio.h>
void insertion(int*arr, int size);
void insertion2(int*arr, int size);
int main () {
	int arr[] = {16,34,7,12,90,54,8,2};
	
	insertion(arr, 8);
	int i = 0;
	for (i = 0; i < 8; i++) {
		printf("%d\n", arr[i]);
	}
	return 0;
}

void insertion (int* arr, int size) {
	int j, i, temp_r;
	for (j = 1; j < size; j++) {
		temp_r = arr[j];
		i = j;
		while (i > 0 && arr[i-1] > temp_r) {
			arr[i] = arr[i-1];
			i--;
		}
		arr[i] = temp_r;
	}
}

void insertion2 (int* arr, int size) {
	int j, i, temp_r;
	for (j = size-1; j >= 1; j--) {
		if (arr[j] < arr[j-1]) {
			temp_r = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = temp_r;
		}
	}
	for (j = 2; j < size; j++) {
		temp_r = arr[j];
		i = j;
		while (arr[i-1] > temp_r) {
			arr[i] = arr[i-1];
			i--;
		}
		arr[i] = temp_r;
	}
}
