/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriley <mriley@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:08:38 by mriley            #+#    #+#             */
/*   Updated: 2020/07/14 20:14:47 by mriley           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/virtual.h"
#include <stdio.h>

char	g_arena[MEM_SIZE];
extern t_op    g_op_tab[17];


int		*parse_num(int *nums,char **argv,int n)
{
	int i;
	int j;
	int max;
	int flag;

	i =0;
	j = 0;
	flag = 0;
	while (i < 4)
		nums[i++] = -1;
	i = 1;
	while(i <= n)
	{
		if (ft_strstr(argv[i],".cor"))
			j++;
		if (ft_strequ(argv[i],"-n") == 1)
			nums[j] = ft_atoi(argv[++i]);
		i++;
	}
	i = 1;
	max = j;
	j = 0;
	while (i <= max)
	{
		while(j < max)
			if (nums[j++] == i)
				flag = 1;
		if (flag == 1)
			i++;
		else
		{
			j = 0;
			while(nums[j] > 0 && j < max)
				j++;
			if (j < max)
				nums[j] = i;
			i++;
		}
		flag = 0;
		j=0;
	}
	return (nums);
}

t_core	*init_champ(int n,char **argv)
{
	t_core	*champ;
	int		i;
	int		num;
	int		*nums;

	champ = malloc(sizeof(t_core));
	champ->player = NULL;
	i = 1;
	num = 0;
	champ->d_cycle = -1;
	nums = malloc(4 * sizeof(int));
	nums = parse_num(nums,argv,n);
	champ->dump = 64;
	while (i <= n)
	{
		if (ft_strequ(argv[i], "-dump") || ft_strequ(argv[i], "-d"))
			champ->d_cycle = ft_atoi(argv[++i]);
		if (ft_strstr(argv[i], ".cor"))
		{
			champ->champions[num].num = nums[num];
			champ = read_champ(argv[i],champ,num);
			champ = parse(champ,num++);
		}
		i++;
	}
	champ->num_ch = num;
	free(nums);
	if (num == 0)
		ft_error(EINVAL, -2);
	return (champ);
}

int		main(int arc, char **argv)
{
	t_core	*champ;
	t_car	*buf;
	int		n;
	//printf("Introducing contestants...\n");
    champ = init_champ(arc - 1,argv);
	n = champ->num_ch;
	arena_set(champ);
	game_start(champ);
	int i =0;
	while(i < n)
	{
		free(champ->champions[i].code);
		i++;
	}
	while(champ->player)
	{
		buf = champ->player;
		champ->player = champ->player->next;
		free(buf);
	}
	free(champ);
   // printf("%d \n",arc);
   /* while (i <arc -1)
    {
         printf("%s \n",champ->champions[i].buf);
        i++;
    }*/
    return(0);
}