#include "../header/virtual.h"
#include <stdio.h>

char arena[MEM_SIZE];
extern t_op    op_tab[17];

void game_start(t_core *champ)
{
	int cycle =0;
	//unsigned int prog_count;
	unsigned int i =1;
	int cycles_to_die = CYCLE_TO_DIE;
	int nbr_live =0;
	int checks = 0;
	int last = 0;
	int end_cycle = cycles_to_die;
	t_car *buf;
	int num_champ = champ->num_ch;
	t_car *start = champ->player;
	//printf("Introducing contestants...\n");
	while (champ->player && cycle != champ->d_cycle)
	{
		//if (cycle == 0)
		//	printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",champ->champions[i-1].num, champ->champions[i-1].mem.prog_size, champ->champions[i-1].mem.prog_name,champ->champions[i-1].mem.comment);
		if ((cycles_to_die <= 0) || (cycle == end_cycle))
		{
			champ->player = check_die(champ->player,cycle,cycles_to_die,champ);//нужно прописывать условия в операциях если коды будут не правильными!!!!
			start = champ->player;
			//printf("cycle_co die %d\n",cycles_to_die);
			if (nbr_live >= NBR_LIVE || checks >= MAX_CHECKS)
			{
				cycles_to_die = cycles_to_die - CYCLE_DELTA;
				checks = 0;
			}
			else
			{
				checks++;
			}
			end_cycle = cycle + cycles_to_die;
			nbr_live = 0;
		}
		if (champ->player && champ->player->time < 1)
		{
			if (arena[champ->player->pc]  > 0 && arena[champ->player->pc]  < 17)
				champ->player->time = op_tab[arena[champ->player->pc] - 1].time;
			else
				champ->player->time = 0;
		}
		if (champ->player && champ->player->time > 0)
			champ->player->time = champ->player->time - 1;
		if (champ->player && champ->player->time == 0)
		{
			if (arena[champ->player->pc] == 1)
			{
				champ->player->cycle_live = cycle;
				nbr_live++;
			}
			if(arena[champ->player->pc] == 15 || arena[champ->player->pc] == 12)
				champ->num_ch = champ->num_ch + 1;
			if (arena[champ->player->pc]  > 0 && arena[champ->player->pc]  < 17)
			{
				//printf("fff %d",arena[champ->player->pc]);
				op_tab[arena[champ->player->pc] - 1].f(champ->player);
			}
			else
				champ->player->pc = (champ->player->pc + 1) % MEM_SIZE;
		}
		if (champ->player)
		{
			champ->player = champ->player->next;
			i++;
		}
		if (!champ->player)//|| num_champ == i)
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