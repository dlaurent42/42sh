#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 1)
		return (1);
	while (++i < ac)
		printf("\\x%x", atoi(av[i]));
	printf("\n");
}
