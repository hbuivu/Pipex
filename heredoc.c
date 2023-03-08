int	ft_pipex_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == (char)c)
			break ;
		i++;
	}
	if (i > ft_strlen(s))
		return (-1);
	return (i);
}

int	detect_limiter(char *limiter, char *str)
{
	int		n;
	int		i;
	int		index;
	char	first_letter;
	

	n = ft_strlen(limiter);
	first_letter = limiter[0];
	index = 0;
	while (str)
	{
		i = ft_pipex_strchr(str, first_letter); //modify strchr so it returns the index of the first letter?
		if (i == -1)
			return (-1);
		index += i;
		str += i;
		if (ft_strncmp(limiter, str, n) == 0)
			return (index);
		else
			str++;
			index++;
	}
	return (-1);
	
	//find length of limiter (for use in ft_strncmp);
	//use ft_strchr to find the first letter of limiter
	//use ft_strncmp to see if from that pointer, the word matches
	//if not, move pointer to the next occurence and repeat
	//returns -1 if limiter not found
	//returns index at start of limiter if found

}

char	*here_doc(char *limiter)
{
	char	*buf;
	char	*str;
	char	*temp;
	int		i;
	int		r;

	buf = (char *)ft_calloc(101, sizeof(char));
	if (!buf)
		//error
	str = NULL;
	temp = NULL;
	r = read(STDIN_FILENO, buf, 100);
	while (r > 0)
	{
		if (!str)
			//str = buffer;
		else 
			new_str = ft_strjoin(str, buf);
			free(str);
			&str = new_str;
			new_str = NULL;
		i = detect_limiter(str);
		if (i > -1)
			break;
		clean(buf);
		r = read(STDIN_FILENO, buf, 100);
	}
	//remove limiter from str;
	//free buf

}