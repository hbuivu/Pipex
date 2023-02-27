#include "pipex.h"

void	print_args(char **list)
{
	int i = 0;

	while (list[i])
	{
		printf(list[i]);
		i++;
	}
}