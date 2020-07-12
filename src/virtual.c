#include "../header/virtual.h"
#include <stdio.h>

char arena[MEM_SIZE];
extern t_op    op_tab[17];


t_car *time_to_die(t_car *car)
{
	t_car *new;

	new = car->next;
	free(car);
	//car = NULL;
	return(new);
}

t_car *check_die(t_car *car, int cycle, int cycles_to_die,t_core *champ)
{
	t_car *buf;
	buf = car;
	int i;

	i = 0;
	while (car && (car->cycle_live < cycle - cycles_to_die || (cycles_to_die <= 0 )))
	{
		//printf("champ->player->num %d\n", car->num);
		if (car && !car->next)
		{
			print_hello(champ);
			ft_printf("Contestant %d has won !\n",car->num);
			/*while(i < champ->num_ch)
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
			free(champ);*/
			//exit(0);
			//return(NULL);
		}
		car = time_to_die(car);
		champ->num_ch = champ->num_ch - 1;
	}
	buf = car;
	while(car && car->next)
	{
		while (car && car->next && (car->next->cycle_live < cycle - cycles_to_die || (cycles_to_die <= 0 )))
		{
			//printf("champ->player->next->num %d\n", car->next->num);
			car->next = time_to_die(car->next);
			champ->num_ch = champ->num_ch - 1;
		}
		car = car->next;
	}
	return(buf);
}

unsigned int change_arena(t_champ champ, int n,int num_ch)
{
	unsigned int start = (MEM_SIZE / num_ch) * (n-1);
	//t_reg init;
	//int j = REG_SIZE - 1;
	unsigned int i=0;
	while(i < champ.mem.prog_size)
	{
	//	printf(" |%x|",champ.code[i]);
		arena[start + i] = champ.code[i];
		i++;
	}
	/*while(j > -1)
	{
		init.reg[j] = start & 0x000000ff;
		start = start >> 8;
		j--;
	}*/
	return(start);
}

t_car *init_reg(t_car *car)
{
	int i =0;
	int j =0;
	while(i <= REG_NUMBER )
	{
		while(j < REG_SIZE)
		{
			car->reg[i].reg[j] = '\0';
			j++;
		}
		j=0;
		i++;
	}
	return(car);

}
