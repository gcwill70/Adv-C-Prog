#include <stdio.h>

void swap(char*, char*);
void permute (int, int);

char str[] = "ABC";

int main() {
        permute(0,2);
        return 0;
}

void swap (char* x, char* y) {
        char temp;
        temp = *x;
        *x = *y;
        *y = temp;
}

void permute(int i, int n) {
        int j;
        if (i == n) {
                printf("%s\n", str);
        }
        else {
                for (j = i; j <= n; j++) {
                        swap(&str[i], &str[j]);
                        permute(i+1, n);
                        swap(&str[i], &str[j]);
                }
        }
}
