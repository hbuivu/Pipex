#include "pipex.h"

// int main(void)
// {
// 	pid_t pid;
// 	pid = fork();
// 	printf("Hello\n");
// 	printf("%i\n", pid);
// 	return (0);
// }

// #define   MAX_COUNT  200
// #define   BUF_SIZE   100

// int  main(void)
// {
//      pid_t  pid;
//      int    i;
//      char   buf[BUF_SIZE];

//      fork();
//      pid = getpid();
//      for (i = 1; i <= MAX_COUNT; i++) {
//           sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
//           write(1, buf, strlen(buf));
//      } 
// 	 //Why use write and not printf?
// 	 //printf is "buffered" - it will group output of a process together
// 	 //while buffering for parent process, child might also use printf
// 	 //since output is not sent to screen immediately, you maynot get the right order of the expected result 
// }

void	fork2(char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		char *args[] = {"ls", "-la", NULL};
		execve("/usr/bin/ls", args, envp);
	}
	else
	{
		wait(NULL);
		printf("fork2 finished processing\n");
	}
}

int main(int argv, char ** argc, char **envp)
{
	(void)argv;
	(void)argc;
	int pid = fork();
	if (pid == 0)
	{
		fork2(envp);
		char *args[] = {"which", "ls", NULL};
		execve("/usr/bin/which", args, envp);
	}
	else 
	{
		wait(NULL);
		printf("finished fork\n");
	}
}
