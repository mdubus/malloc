#include "../includes/malloc.h"

void	ft_putnbr(size_t nbr)
{
	char	size[21];
	
	ft_utoa_base_r(size, nbr, 10);
	ft_putstr(size);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
