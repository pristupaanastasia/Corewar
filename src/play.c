#include "../header/virtual.h"
#include <stdio.h>

char arena[MEM_SIZE];
extern t_op    op_tab[17];

t_car *parse_func_champ(t_car *champ, t_core *core, int cycle)
{
	if (arena[champ->pc] == 1)
	{
		champ->cycle_live = cycle;
		//nbr_live++;
	}
	if(arena[champ->pc] == 15 || arena[champ->pc] == 12)
		core->num_ch = core->num_ch + 1;
	if (arena[champ->pc]  > 0 && arena[champ->pc]  < 17)
		op_tab[arena[champ->pc] - 1].f(champ);
	else
		champ->pc = (champ->pc + 1) % MEM_SIZE;
	return(champ);
}

t_car *time_oper(t_car *champ)
{
	if (champ && champ->time < 1)
		champ->time = arena[champ->pc]  > 0 && arena[champ->pc]  < 17 ? op_tab[arena[champ->pc] - 1].time : 0;
	if (champ && champ->time > 0)
		champ->time = champ->time - 1;
	return(champ);
}

void game_start(t_core *champ)
{
	int cycle =0;
	unsigned int i =1;
	int cycles_to_die = CYCLE_TO_DIE;
	int nbr_live =0;
	int checks = 0;
	int last = 0;
	int end_cycle = cycles_to_die;
	t_car *buf;
	int num_champ = champ->num_ch;
	t_car *start = champ->player;
	while (champ->player && cycle != champ->d_cycle)
	{
		if ((cycles_to_die <= 0) || (cycle == end_cycle))
		{
			champ->player = check_die(champ->player,cycle,cycles_to_die,champ);//нужно прописывать условия в операциях если коды будут не правильными!!!!
			start = champ->player;
			if (nbr_live >= NBR_LIVE || checks >= MAX_CHECKS)
			{
				cycles_to_die = cycles_to_die - CYCLE_DELTA;
				checks = 0;
			}
			else
				checks++;
			end_cycle = cycle + cycles_to_die;
			nbr_live = 0;
		}
		if (champ->player)
			champ->player = time_oper(champ->player);
		if (champ->player && champ->player->time == 0)
		{
			champ->player = parse_func_champ(champ->player,champ,cycle);
			if (arena[champ->player->pc] == 1)
				nbr_live++;
		}
		if (champ->player)
		{
			champ->player = champ->player->next;
			i++;
		}
		if (!champ->player || i == num_champ + 1)
		{
			num_champ = champ->num_ch;
			if (start)
				champ->player = start;
			cycle++;
			i = 1;
		}
	}
	if (champ->d_cycle == cycle)
	{
		print_hello(champ);
		print_arena(champ->dump);
	}
	//printf("last %d",last);
}