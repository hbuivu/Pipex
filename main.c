
//./pipex file1 cmd1 cmd2 file2
// < infile ls -l | wc -l > outfile
//use cmd1 on file 1 
//the output of cmd1-file1 is then given as an input to cmd2
//the output of cmd1-file1-cmd2 is then written to outfile

//read from infile
//execute cmd1 with infile as input
//send output to cmd2
//write to outfile

//use dup to swap infile with stdin
//run cmd1 on stdin
//output is written to fd[1]


// int dup2(int oldfd, int newfd);
// execve(cmd, mycmdargs, envp)



// int main(int argc, char **argv)
// {
// 	pid_t	id; 
// 	int 	fd[2];
// 	int		infile;
// 	int		outfile;

// 	if (pipe(fd) < 0)
// 		perror("pipe error");
// 		return(1);
// 	id = fork();
// 	if (id < 0 )
// 		perror("fork error");
// 		return(1);

// 	else if (id == 0) //child proces
// 		close(fd[0]); //close write end of pipe
// 		infile = open(file1, O_RDONLY); //open file1 and create its fd
// 		if (infile < 0)
// 			perror("read error");
// 			exit(1);
// 		if(dup2(0, infile) < 0 || dupe2(1, fd[1]) < 0) //use dup2 to switch stdin and infile, also switch stdout and fd[1]
// 			perror("dupe error");
// 			return(1);
// 		close(fd[1]);
// 		//pa

// 	else //parent process
// 		close(fd[1]); //close read end of pipe
// 		outfile = open(file2, O_CREAT | O_WRONLY); //open file2 and create its fd
// 		if (outfile < 0)
// 			perror("read error");
// 			exit(1);
// 		if (dup2(0, fd[0]) < 0 || dup2(1, outfile) < 0) //switch out stdin and stdout
// 			perror("dup2 error");
// 			exit(1);
// 		close(fd[0]);
// 		wait(NULL);		
// }

// //use ft_split to get array of argv

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *args[] = {"ls", "-la", NULL};
	int	fd;

	fd = open("newfile", O_CREAT | O_WRONLY|O_TRUNC);
	
	execve("/usr/bin/ls", args, NULL);
}

//can I use which command to find the correct path?
//make my own popen function?
	//open a process by:
		//creating pipe
		//forking
		//invoking shell

//first, find path for which by iterating through envp
	//while (envp[i])
		// char *cmd = ft_join(envp[i], "which");
		// execve(cmd, {"which", "which"}, envp); 
		// free(cmd);