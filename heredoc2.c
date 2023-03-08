#include "pipex.h"

char	*here_doc(char *limiter)
{
	char	*temp;
	char	*str;
	char	*new_str;
	int		lim_len;

	str = NULL;
	temp = NULL;
	new_str = NULL;
	lim_len = ft_strlen(limiter); 
	while (1)
	{
		temp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(temp, limiter, lim_len) == 0)
			break;
		if (!str)
		{
			str = (char *)ft_calloc(ft_strlen(temp) + 1, sizeof(char));
			// if (!str)
			// 	//error
			ft_strlcpy(str, temp, ft_strlen(temp) + 1);
			free(temp);
		}
		else 
		{
			new_str = ft_strjoin(str, temp);
			free (str);
			free (temp);
			str = new_str; 
		}
	}
	free(temp);
	return (str);
}

int main(void)
{
	char *str = here_doc("LIM\n");
	printf("THE STRING IS: \n");
	printf("%s", str);
	free(str);
}