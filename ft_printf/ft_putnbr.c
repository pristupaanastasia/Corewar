/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:54:38 by smanhack          #+#    #+#             */
/*   Updated: 2019/04/07 18:54:39 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int fl;

	fl = 1;
	if (n < 0)
	{
		ft_putchar('-');
		fl = -1;
	}
	if (n / 10)
		ft_putnbr(n / 10 * fl);
	ft_putchar(n % 10 * fl + 48);
}