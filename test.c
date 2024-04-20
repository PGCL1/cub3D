
#include <stdio.h>
#include <stdlib.h>

int main()
{

	int	*n = malloc(sizeof(int) * 2);

	n[0] = 1;
	n[1] = 2;

	printf("%d\n", n[2]);
	return 0;
}