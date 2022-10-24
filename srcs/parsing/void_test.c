#include <unistd.h>

void	print_str(char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	print_upper(char *s)
{
	int	i = 0;

	while (s[i])
	{
		if (s[i] >= 97 && s[i] <= 122)
			s[i] -= 32;
		i++;
	}
	if (i)
		return (print_str(s));
	else
		return ;
}

#include <string.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	char *ret;
	if (ac != 2)
		return (1);
	ret = strdup(av[1]);
	print_upper(ret);
	free(ret);
	return (0);
}