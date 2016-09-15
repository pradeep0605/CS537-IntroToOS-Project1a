#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct {
	int *arr;
	int N;
} quick_sort_partition;
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

void* quick_sort(void *arg)
{
	int tmp_swap;
	quick_sort_partition *p = (quick_sort_partition *) arg;
	quick_sort_partition p1, p2;
	int *arr = p->arr;
	int N = p->N;
	pthread_t partition1_thread, partition2_thread;

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
	p1.arr = &arr[0];
	p1.N = j;
	p2.arr = &arr[j + 1];
	p2.N = N - j - 1;
	if (N > 1000000) {
		if (pthread_create(&partition1_thread, NULL,
			quick_sort, (void *)&p1)) {
			printf("Error in creating partition1 thread\n");
		}
		if (pthread_create(&partition2_thread, NULL,
			quick_sort, (void *)&p2)) {
			printf("Error in creating partition2 thread\n");
		}
		pthread_join(partition1_thread, NULL);
		pthread_join(partition2_thread, NULL);
	} else {
		quick_sort((void*) &p1);
		quick_sort((void*) &p2);
	}
	
}

int main(int arg_count, char *arg_vector[])
{
	int N, i = 0;
	int *arr;
	int ret = 0;
	pthread_t sort_thread;
	quick_sort_partition p;

	scanf("%d", &N);
	if ((arr = (int *) malloc(sizeof(int) * N)) == NULL) {
		printf("Unable to allocate memory\n");
		exit(-1);
	}
	for (i = 0; i < N; ++i) {
		scanf("%d", &arr[i]);
	}

	p.arr = arr;
	p.N = N;
	if (ret = pthread_create(&sort_thread, NULL, quick_sort, (void *)&p)) {
		printf("Error creating thread = %d", ret);
	}

	pthread_join(sort_thread, NULL);

	for (i = 0; i < N; ++i) {
		printf("%d\n", arr[i]);
	}

	return 0;
}
