#include<stdio.h>
#include<math.h>
#include<stdlib.h>


int main()
{	
	int n;
	scanf("%d", &n);
	if (n < 0) {
		printf("Wrong input ! How can n be negative ! Be sensible\n");
	}
	printf("%d\n", n);
	srand(time(NULL));
	while(n--) {
		printf("%d\n", rand()); 
	}
}
