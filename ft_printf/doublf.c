/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 20:41:10 by mriley            #+#    #+#             */
/*   Updated: 2019/08/29 18:37:58 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"
#include <limits.h>

char		*izdvatodestocd(double n, t_format f)
{
	int		i;
	char	*h;
	int		p;
	double g;

	i = 0;
	p = 6;
	g = n;
	n = n- (long long)n;
	if (f.prec > 0)
		p = f.prec;
	if (f.prec == 0 || f.prec == -1)
		p = 1;
	if (n < 0.0)
	{
		n = -n;
		g = -g;
	}
	if (((n > 0.5) || ((long long)g % 2 != 0 && n == 0.5))  && f.prec == 0 )
		return (ft_strdup("1.0"));
	h = (char*)malloc(p + 2);
	while (i < p)
	{
		n = n * 10;
		h[i++] = (int)n + '0';
		n = n - (int)n;
	}
	h[p] = '\0';
	h = ft_okruglyaem(h, n * 10);
	return (h);
}

void		toretryd_part_2(t_point *p, long long *i, t_format *ff)
{
	p->znak = ft_znakd(p->s);
	p->exp = ft_expd(p->s);
	p->mantissa = ft_mantissad(p->s);
	*i = izdestodvad(p->exp);
	p->mantissa = dvigaemd(*i, p->mantissa);
	p->g = todesd(p->mantissa);
	p->posle = dlinayadrob(p->mantissa, *ff);
}

void		ft_free(t_point p)
{
	free(p.mantissa);
	free(p.g);
	free(p.s);
	free(p.exp);
	free(p.zifra);
	free(p.toc);
}

void		ft_toretryd_bonus(t_point *p, char **stroka, t_format *ff)
{
	if (p->toc[1] == '.')
	{
		p->zifra = ft_peredelzel(p->zifra, ft_strlen(p->zifra));
		p->toc = tocotrub(p->toc);
	}
	if (ff->prec != 0)
	{
		*stroka = ft_strjoin(p->zifra, ".");
		free(p->zifra);
		p->zifra = *stroka;
		*stroka = ft_strjoin(p->zifra, p->toc);
		ft_free(*p);
		p->zifra = *stroka;
	}
}
char *func_infinity(char *string)
{
	if (ft_strcmp(string,"0111111111110000000000000000000000000000000000000000000000000000") == 0)
		return(ft_strdup("inf"));
	if (ft_strcmp(string,"1111111111110000000000000000000000000000000000000000000000000000") == 0)
		return(ft_strdup("-inf"));
	if (ft_strcmp(string,"0111111111110000000000000000000000000000000000000000000000000001") == 0)
		return(ft_strdup("nan"));
	if (ft_strcmp(string,"0111111111111000000000000000000000000000000000000000000000000001") == 0)
		return(ft_strdup("nan"));
	if (ft_strcmp(string,"0111111111111111111111111111111111111111111111111111111111111111") == 0)
		return(ft_strdup("nan"));
	if (ft_strcmp(string,"0111111111111000000000000000000000000000000000000000000000000000") == 0)
		return(ft_strdup("nan"));
	return (NULL);
}
char		*toretryd(va_list ap, t_format ff)
{
	double		n;
	long long	i;
	t_point		p;
	char		*stroka;


	if (ff.prec == 0)
		ff.prec = 6;
	if (ff.prec == -1)
		ff.prec = 0;
	if (ff.type == 2)
		return (toretry(ap, ff));
	n = va_arg(ap, double);
	p.s = ft_putbitd(&n, 8);
	if (func_infinity(p.s))
	{
		if (ff.prec ==0)
			ff.prec = -1;
		if (ff.prec == 6)
			ff.prec = 0;
		ff.sym = 's';
		return(func_infinity(p.s));
	}
	toretryd_part_2(&p, &i, &ff);
	p.zifra = ft_delaem(p.g, p.znak, p.mantissa);
	p.toc = todestocd(n, ff);
	ft_toretryd_bonus(&p, &stroka, &ff);
	if ((ff.flags & 1) && ft_strchr(p.zifra,'.') == NULL)
		return(ft_strjoin(p.zifra,"."));
	return (p.zifra);
}
