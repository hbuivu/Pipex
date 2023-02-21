void	free_split(char **list)
{
	int	i;

	i = 0;
	while(list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}