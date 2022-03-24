#include <stdio.h>
#include <stdlib.h>

void bad_input() {
	printf("bad input\n");
	exit(0);
}

void swap (int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void QuickSort (int *arr, int left, int right) {
	int left_bound = left;
	int right_bound = right;
	int pin = arr[left + rand()%(right-left+1)];
	while (1) {
		while(arr[right] > pin) {
			right--;
		}
		while (arr[left] < pin) {
			left++;
		}
		if (left < right) {
			swap(&arr[left], &arr[right]);
			left++;
			right--;
		}
		else {
            break;
        }
}
	int mid = left;	
	left = left_bound;
	right = right_bound;
	if (mid - 1 - left > 0) {
        	QuickSort(arr, left, mid - 1);
    	}
	if (right - mid > 0) {
        	QuickSort(arr, mid, right);
    	}
}

int main() {
	int n;
	if (scanf("%i", &n) != 1 || n < 0) {
		bad_input();
	}
	int *arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		if (scanf("%i", &arr[i]) != 1) {
			bad_input();
		}
	}
	if (n > 1)  QuickSort(arr, 0, n-1);
	for (int i = 0; i < n; i++){
		printf("%i ", arr[i]);
	}
	printf("\n");
        free(arr);
	return 0;
}
