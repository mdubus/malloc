/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdubus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 16:42:53 by mdubus            #+#    #+#             */
/*   Updated: 2019/02/01 16:28:04 by mdubus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	temp;

	len = ft_strlen(str);
	if (len <= 1)
		return (str);
	i = len - 1;
	j = 0;
	while (j < (len / 2))
	{
		temp = str[j];
		str[j] = str[i];
		str[i] = temp;
		j++;
		i--;
	}
	return (str);
}

char	*ft_utoa_base_r(char *buf, unsigned long long n, unsigned base)
{
	char	*charset;
	size_t	i;

	if (base > 16)
		return (NULL);
	charset = "0123456789abcdef";
	i = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n != 0)
	{
		buf[i++] = charset[n % base];
		n /= base;
	}
	buf[i] = '\0';
	return (ft_strrev(buf));
}

void	print_address(uintptr_t ptr)
{
	char	s[19];

	s[0] = '0';
	s[1] = 'x';
	ft_utoa_base_r(&s[2], ptr, 16);
	write(1, s, ft_strlen(s));
}
