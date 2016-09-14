#include<stdio.h>
#include<stdlib.h>

#if 0
#define SWAP(a, b) do {\
		(a) ^= (b) ^= (a) ^= (b); \
		} while (0)

#else
#define SWAP(a, b) do { \
			tmp_swap = a; \
			a = b; \
			b = tmp_swap; \
		} while(0)
#endif

void quick_sort(int *arr, int N)
{
	int tmp_swap;
	int pivot = arr[0];
	int i = 0, j = N;
	/* if there are only 1 or less elements, then nothing to sort */
	if (N < 2)
		return;
	/* Optimized code to handle arrays with only two elements */
	if (N == 2) {
		if (arr[0] > arr[1]) {
			/* swapping two numbers would sort them */
			SWAP(arr[0], arr[1]);
		}
		return;
	}

	while (i < j) {
		while (arr[++i] < pivot && i < (N -  1));
		while (arr[--j] > pivot && j > 0);

		if (i < j) {
			SWAP(arr[i], arr[j]);
		}
	}

	SWAP(arr[0], arr[j]);
	/* Divide the array into two parts and quick sort them
	 */
	quick_sort(&arr[0], j);
	quick_sort(&arr[j + 1], N - j - 1);
}

int main(int arg_count, char *arg_vector[])
{
	int N, i = 0;
	int *arr;

	scanf("%d", &N);
	if ((arr = (int *) malloc(sizeof(int) * N)) == NULL) {
		printf("Unable to allocate memory\n");
		exit(-1);
	}
	for (i = 0; i < N; ++i) {
		scanf("%d", &arr[i]);
	}

	quick_sort(arr, N);

	for (i = 0; i < N; ++i) {
		printf("%d\n", arr[i]);
	}

	return 0;
}
