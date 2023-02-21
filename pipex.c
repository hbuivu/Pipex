#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	fork();
	fork();
	printf("Hello\n");
}

