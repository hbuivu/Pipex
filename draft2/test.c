#include "pipex.h"
#include "utils.c"

// typedef struct tlist
// {
// 	char *str;
// } tlist;

// typedef struct slist
// {
// 	tlist	*structlist;

// } slist;

// int main(void)
// {
// 	slist *s;

// 	s = (slist *)ft_calloc(1, sizeof(slist));
// 	s->structlist = ft_calloc(5, sizeof(tlist));
// 	for (int i = 0; i < 5; i++)
// 	{
// 		s->structlist[i].str = (char *)ft_calloc(2, sizeof(char));
// 		ft_strlcpy(s->structlist[i].str, "a", 2);
// 	}
// 	for (int j = 0; j < 6; j++)
// 	{
// 		printf("%s\n", s->structlist[j].str);
// 	}
// }

char	**get_PATHS(char **envp)
{
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break;
	if (envp[i] == NULL)
		return (NULL); 
	//move pointer over past =sign
	while (*(envp[i]) != '/')
		envp[i]++;
	paths = ft_split(envp[i], ':');
	if (!paths)
		return (NULL);
	return (paths);
}

// char	*find_path(t_mlist *m, char *arg) //char **envp
// {
// 	int		i;
// 	int		f;
// 	int		x;
// 	char	*path;

// 	while (m->paths[i])
// 	{
// 		path = ft_strjoin_char(m->paths[i], arg, '/');
// 		f = access(path, F_OK);
// 		x = access(path, X_OK);
// 		if (f == 0 && x == 0)
// 			break;
// 		else if (f == 0 && x < 0)
// 			pipex_error(NO_PATH, m);
// 		free(path);
// 		i++;
// 	}
// 	printf("%s\n", path);
// 	if (f == 0 && x == 0)
// 		return (path);
// 	return (NULL);
// }

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	char	*buffer;
	int		k;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	k = ft_strlen(s1) + ft_strlen(s2) + 2;
	buffer = (char *)malloc(sizeof(char) * k);
	if (!buffer)
		return (NULL);
	i = ft_strlcpy(buffer, s1, k);
	buffer[i] = c;
	ft_strlcat(buffer, s2, k);
	return (buffer);
}


int main(int argv, char **argc, char **envp)
{
	(void)argv;
	char **PATHS;
	char **args;

	PATHS = get_PATHS(envp);
	args = ft_split(argc[2], ' ');

	int		i;
	int		f;
	int		x;
	char	*path;

	printf("arg: %s\n", args[0]);
	while (PATHS[i])
	{
		path = ft_strjoin_char(PATHS[i], args[0], '/');
		printf("path tried: %s\n", path);
		f = access(path, F_OK);
		x = access(path, X_OK);
		if (f == 0 && x == 0)
			break;
		else if (f == 0 && x < 0)
			printf("file found but not executable");
			// pipex_error(NO_PATH, m);
		free(path);
		i++;
	}
	printf("f: %i x: %i\n", f, x);
	printf("%s\n", path);
	// if (f == 0 && x == 0)
	// 	return (path);
	// return (NULL);
	return (0);

}