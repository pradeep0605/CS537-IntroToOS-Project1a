#include<stdio.h>
#include<stdlib.h>


void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *,
const void*));

int compare_func(const void *a, const void *b) {

	return ((*(int*)a) > (*(int*) b));
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

	qsort(arr, N, sizeof(int), compare_func);

	for (i = 0; i < N; ++i) {
		printf("%d\n", arr[i]);
	}

	return 0;
}
