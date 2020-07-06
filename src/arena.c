#include "../header/virtual.h"
#include <stdio.h>

char arena[MEM_SIZE];
extern t_op    op_tab[17];

t_car *init_champions(t_car *player,int j,t_core *champ)
{
	player->num = champ->champions[j].num;
	player->pc = change_arena(champ->champions[j],player->num,champ->num_ch);
	player->time = -1;
	player = init_reg(player);
	player = to_reg_from_int(player, 1, - player->num);
	player->next = malloc(sizeof(t_car));
	return(player);
}

void arena_set(t_core *champ)
{
	int i =champ->num_ch;
	int j =champ->num_ch - 1;
	int car = 0;
	champ->player = malloc(sizeof(t_car));
	t_car *start;
	start = champ->player;
	while(i >0)
	{
		while(j > -1)
		{
			if (i == champ->champions[j].num)
			{
				champ->player = init_champions(champ->player,j,champ);
				champ->player = champ->player->next;
				champ->player->num = -1;
				
			}
			j--;
		}
		j=champ->num_ch - 1;
		i--;
	}
	champ->player = NULL;
	champ->player = start;
	while (start)
	{
		if (start->next->num == -1)
			start->next = NULL;
		start = start->next;
	}
}

void print_addres(int i)
{
	ft_printf("\n");
	if (i < 0x10)
		ft_printf("0x000%x : ",i);
	else
	{
		if (i < 0x100)
			ft_printf("0x00%x : ",i);
		else
			(i < 0x1000) ? ft_printf("0x0%x : ",i) : ft_printf("0x%x : ",i);// sega in ldi_bug_in_zaz_corewar 
	}
}

void print_arena(int num)
{
	int i;
	unsigned int buf;

	i = 0;
	buf = 0;
	ft_printf("0x000%x : ",i);
	while(i < MEM_SIZE)
	{
		buf = arena[i];
		buf = buf & 0x000000ff;
		if (buf != 0)
			(buf < 16) ? ft_printf("0%x ",buf) : ft_printf("%x ",buf);
		else
			ft_printf("00 ");
		if ((i + 1) % (num) ==0 && i!=0 && (i + 1) != MEM_SIZE)
		{
			print_addres(i + 1);
		}
		i++;
	}
	ft_printf("\n");
}
