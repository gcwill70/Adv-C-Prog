#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int** getMatrix(int* rows, int* cols, char name);
void printMatrix(int** arr, int rows, int cols);
int** matrixMult(int** arr1, int rows1, int cols1, int** arr2, int rows2, int cols2);
void freeMatrix( int** arr, int rows);

int main () {
	int rowsA = 0;
	int colsA = 0;
	int rowsB = 0;
	int colsB = 0;
	
	printf("\nMatrix Multiplier\n A x B = C\n");
	
	//generate matrices
	int** matrixA = getMatrix(&rowsA, &colsA, 'A');
	int** matrixB = getMatrix(&rowsB, &colsB, 'B');

	//print matrices to the user	
	printf("Matrix A:\n");
	printMatrix(matrixA, rowsA, colsA);
	printf("Matrix B:\n");
	printMatrix(matrixB, rowsB, colsB);

	//get the answer
	int** matrixC = matrixMult(matrixA, rowsA, colsA, matrixB, rowsB, colsB);
	
	//print the answer
	printf("Matrix C:\n");
	printMatrix(matrixC, rowsA, colsB);

	//free everything
	freeMatrix(matrixA, rowsA);
	freeMatrix(matrixB, rowsB);
	freeMatrix(matrixC, rowsA);

	return 0;
}

int** getMatrix(int* rows, int* cols, char name) {
	bool err = false;
	
	printf("Enter the number of rows for matrix %c.\n", name);
	do {
		err = false;
		scanf("%d", rows);
		if(*rows < 1) {
			printf("Error: the number of rows must be > 0.\n");
			err = true;
		} else if (*rows > 10) {
			printf("Error: the number of rows must be < 10.\n");
			err = true;
		}
	}while(err);

	printf("Enter the number of columns for matrix %c.\n", name);
	do {
		err = false;
		scanf("%d", cols);
		if(*cols < 1) {
			printf("Error: the number of columns must be > 0.\n");
			err = true;
		} else if (*cols > 10) {
			printf("Error: the number of columns must be < 10.\n");
			err = true;
		}
	}while(err);
	int** arr = malloc(sizeof(int*)*(*rows));
	int i = 0;
	for(i = 0; i < *rows; i++) {
		arr[i] = malloc(sizeof(int)*(*cols));
	}

	int j = 0;
	for(i = 0; i < *rows; i++) {
		for(j = 0; j < *cols; j++) {
			arr[i][j] = rand() % 20;
		}
	}

	return arr;
}

void printMatrix(int** arr, int rows, int cols) {
	if(arr == NULL) {return;}

	int i = 0;
	int j = 0;

	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}

int** matrixMult(int** arr1, int rows1, int cols1, int** arr2, int rows2, int cols2) {
	if(cols1 != rows2) {
		printf("Error: the number of columns in A must match the number of rows in B. Exiting...\n");
		freeMatrix(arr1, rows1);
		freeMatrix(arr2, rows2);
		return NULL;
	}

	//malloc return array
	int** ret = malloc(sizeof(int*)*rows1);
	int i = 0; //row index for ret and arr1
	for(i = 0; i < rows1; i++) {
		ret[i] = malloc(sizeof(int)*cols2);
	}
	 
	int j = 0; //col index for ret and arr2
	int k = 0; //col index for arr1 AND row index for arr2
	for(i = 0; i < rows1; i++) { //for each row in ret
		for(j = 0; j < cols2; j ++) { //for each column in ret
			ret[i][j] = 0; //initialize the return element
			//sum the first row in A with the first column in B
			for(k = 0; k < cols1; k++) {
				ret[i][j] = ret[i][j] + arr1[i][k]*arr2[k][j];
			}
		}
	}
	
	return ret;
}

void freeMatrix(int** arr, int rows) {
	if (arr == NULL) {return;}

	int i = 0;
	for(i = 0; i < rows; i++) {
		free(arr[i]);
	}
	free(arr);
}
