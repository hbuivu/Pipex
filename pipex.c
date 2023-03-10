#include "pipex.h"

void	child1(int *fd, t_mlist *m, char **envp)
{
		dup2(fd[1], STDOUT_FILENO);
		if (close(fd[0]) == -1)
			pipex_error(CLOSE_ERR, m);
		if (close(fd[1]) == -1)
			pipex_error(CLOSE_ERR, m);
		execve(m->exec_list[0].path, m->exec_list[0].commands, envp);
		pipex_error(EXEC_ERR, m);
}

void	child2(int *fd, t_mlist *m, char **envp)
{
		if (dup2(fd[0], STDIN_FILENO) < 0) 
			pipex_error(DUP_ERR, m); 
		if (dup2(m->file2, STDOUT_FILENO) < 0)
			pipex_error(DUP_ERR, m);
		if (close(fd[0]) == -1)
			pipex_error(CLOSE_ERR, m);
		if (close(fd[1]) == -1)
			pipex_error(CLOSE_ERR, m);
		execve(m->exec_list[1].path, m->exec_list[1].commands, envp);
		pipex_error(EXEC_ERR, m);
}

void	simple_pipex(t_mlist *m, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (dup2(m->file1, STDIN_FILENO) < 0)
		pipex_error(DUP_ERR, m);
	if (pipe(fd) < 0)
		pipex_error(PIPE_ERR, m);
	pid1 = fork();
	if (pid1 < 0)
		pipex_error(FORK_ERR, m);
	if (pid1 == 0)
		child1(fd, m, envp);
	pid2 = fork();
	if (pid2 < 0)
		pipex_error(FORK_ERR, m);
	if (pid2 == 0)
		child2(fd, m, envp);
	if (close(fd[0]) == -1)
		pipex_error(CLOSE_ERR, m);
	if (close(fd[1]) == -1)
		pipex_error(CLOSE_ERR, m);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argv, char **argc, char **envp)
{
	t_mlist	*m;

	m = NULL;
	if (argv != 5)
		pipex_error(INVALID_ARG, m);
	if (access(argc[1], F_OK) < 0 || access(argc[1], R_OK) < 0)
		pipex_error(NO_FILE, m);
	m = init_mlist(argv, argc, envp);
	simple_pipex(m, envp);
	free_mlist(m);
	return (0);
}

