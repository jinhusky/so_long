/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 00:25:58 by kationg           #+#    #+#             */
/*   Updated: 2025/03/09 23:46:50 by kaijing          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_finddec(int n)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	ft_putdec(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	else
	{
		if (n < 0)
		{
			count += ft_putchar('-');
			n = -n;
		}
		else if (n == 0)
			return (ft_putchar('0'));
		count += ft_finddec(n);
		if (n > 9)
			ft_putdec(n / 10);
		ft_putchar(n % 10 + '0');
	}
	return (count);
}

int	find_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	ft_putunsigned(unsigned int n)
{
	int	count;

	count = find_unsigned(n);
	if (n == 0)
		return (ft_putchar('0'));
	if (n > 9)
		ft_putunsigned(n / 10);
	ft_putchar(n % 10 + '0');
	return (count);
}
