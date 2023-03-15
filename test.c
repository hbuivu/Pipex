#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argv, char **argc, char **envp)
{
	char *path = "/usr/bin/sh";
	char *args[5] = {"sh", "-c", "type -t type", NULL}; //why does this give an error?????
	if (execve(path, args, envp) == -1)
		printf("%s\n", strerror(errno));
}