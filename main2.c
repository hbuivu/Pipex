#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char **argv, char **envp)
{
	// if (argc > 1)
	// {
	// 	int i = 0;
	// 	while (envp[i])
	// 	{
	// 		printf("%s\n", envp[i]);
	// 		i++;
	// 	}
	// }

	// char *str  = malloc(sizeof(char) * 5);
	char *args[] = {"which", "ls", NULL};
	execve("/usr/bin/which", args, envp);

	// char *args[3] = {"a", "which", NULL};

	// // args[2] == NULL;
	// // args[1] == "which";

	// printf("%s\n", args[1]);

	// argv is an array of argument strings passed to the new program. by convention 
	// the first of these strings should containe the FILENAME_MAXassociated with the 
	// file being executed.
}