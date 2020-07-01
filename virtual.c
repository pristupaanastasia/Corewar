#include "virtual.h"
#include <stdio.h>

char arena[MEM_SIZE];
extern t_op    op_tab[17];
t_champ read_champ(char *s, t_champ champ)
{
    char *line;
    int fd;
    int k;
	int j=0;
	line = malloc(2);
	line[1] = '\0';
	champ.buf = (char*)malloc(HEAD_SIZE + 1);
    if ((fd = open(s,O_RDONLY)) == -1)
        exit(0);
	
    off_t endfile = lseek(fd,0,SEEK_END);
    lseek(fd,0,0);
    while(lseek(fd, 0, SEEK_CUR) != endfile)
    {
       if((k = read(fd,line,1)) == -1)
	   	exit(0);
		champ.buf[j] = line[0];
		j++;
    }
	champ.buf[j]='\0';
	free(line);
	return(champ);
}
void print_mem(unsigned int n)
{
	int i =0;
	printf("\n mem");
	while(i<32)
	{
		if(n & 0x80000000)
			printf("1");
		else
			printf("0");
		i++;
		n=n<<1;
	}
	printf("\n");
}

void print_char(char k)
{
	int i = 0;
	while(i < 8)
	{
		if (k & 0x80)
			printf("1");
		else
			printf("0");
		i++;
		k = k << 1;
	}
}

t_champ parse(t_champ champ)
{
	int i = 0;
	/*if ((champ.buf[0] & 0xea) == 0xea && (champ.buf[1] & 0x83) == 0x83 && (champ.buf[2] & 0xf3) == 0xf3)
		printf(" I %d",champ.buf[0]);
	else
		exit(0);
	i = 3;
	*/
	champ.mem.magic = 0x00000000;
	champ.mem.prog_size = 0;
	unsigned int n = 0;
	int j =0;
	while(i< 4)
	{
		n = (unsigned int)champ.buf[i];
		n = n & 0x000000ff;
		//printf("n %x\n",n);
		champ.mem.magic = champ.mem.magic | n ;
		//print_mem(champ.mem.magic);
		i++;
		if (i < 4)
			champ.mem.magic = champ.mem.magic << 8;
	}
	printf("magic %x\n",champ.mem.magic);
	while (j < PROG_NAME_LENGTH)
	{
		champ.mem.prog_name[j] = champ.buf[i];
		i++;
		j++;
	}
	i = i+4;
	printf("name %s",champ.mem.prog_name);
	j =0;
	while (j < 4)
	{
		n = (unsigned int)champ.buf[i];
		n = n & 0x000000ff;
		champ.mem.prog_size = champ.mem.prog_size | n ;
		printf("prod\n");
		print_mem(champ.mem.prog_size);
		i++;
		j++;
		if (j < 4)
			champ.mem.prog_size = champ.mem.prog_size << 8;
	}
	printf("prog_size %d\n",champ.mem.prog_size);
	j =0;
	if (champ.mem.prog_size > CHAMP_MAX_SIZE)
	{
		printf("error\n");
		exit(0);
	}
	while (j < COMMENT_LENGTH)
	{
		champ.mem.comment[j] = champ.buf[i];
		i++;
		j++;
	}
	printf("comment %s\n",champ.mem.comment);
	i = i+4;
	j=0;
	champ.code = malloc(champ.mem.prog_size + 1);
	while(j < champ.mem.prog_size)
	{
		champ.code[j] = champ.buf[i];
		i++;
		j++;
	}
	champ.code[j] = '\0';
	j = 0;
	printf("code \n");
	while(j < champ.mem.prog_size)
		printf("%i ",champ.code[j++]);
	printf("\n");
	/*while(i< HEAD_SIZE)
	{
		printf("%c-%d",champ.buf[i],i);
		i++;
	}*/
	/*while(champ.filech[2] & 0xff)
	{
		if (champ.filech[2] & 0x80)
			printf("1");
		else
			printf("0");
		champ.filech[2] = champ.filech[2] << 1;
	}*/
	printf("\n");
	free(champ.buf);
	return(champ);
}
/*unsigned int translate_reg(t_reg regist)
{
	unsigned int solve = 0;
	unsigned int buf = 0;
	int i = 0;
	while(i < REG_SIZE)
	{
		buf = regist.reg[i];
		buf = buf & 0x000000ff;
		solve = solve | buf;
		i++;
		if (i < REG_SIZE)
			solve = solve << 8;
	}
	return(solve);
}
*/
t_car *rewrite_car(t_car *car)
{
	t_car *copy;
	t_car *start;
	copy = car;
	start = copy->next;
	while(car->next)
	{
		car = car->next;
	}
	car->next = copy;
	copy->next = NULL;
	return(start);
}

t_car *time_to_die(t_car *car)
{
	t_car *new;

	new = car->next;
	free(car);
	return(new);
}

t_car *check_die(t_car *car, int cycle, int cycles_to_die,t_core *champ)
{
	t_car *buf;
	buf = car;
	while (car && (car->cycle_live < cycle - cycles_to_die || (cycles_to_die <= 0 )))
	{
		printf("champ->player->num %d\n", car->num);
		car = time_to_die(car);
		champ->num_ch = champ->num_ch - 1;
	}
	buf = car;
	while(car->next)
	{
		while (car->next && (car->next->cycle_live < cycle - cycles_to_die || (cycles_to_die <= 0 )))
		{
			car->next = time_to_die(car->next);
			champ->num_ch = champ->num_ch - 1;
		}
		car = car->next;
	}
	return(buf);
}

void game_start(t_core *champ)
{
	int cycle =0;
	//unsigned int prog_count;
	unsigned int i =0;
	int cycles_to_die = CYCLE_TO_DIE;
	int nbr_live =0;
	int checks = 0;
	int last = 0;
	int end_cycle = cycles_to_die;
	t_car *buf;
	while (champ->player)
	{
		if ((cycles_to_die <= 0) || (cycle == end_cycle))
		{
			champ->player = check_die(champ->player,cycle,cycles_to_die,champ);
			printf("cycle_co die %d\n",cycles_to_die);
			/*while (champ->player && (champ->player->cycle_live < cycle - cycles_to_die || (cycles_to_die <= 0 )) && (last = champ->player->num) ==champ->player->num)
			{
					printf("champ->player->num %d\n", champ->player->num);
					champ->player = time_to_die(champ->player);
					checks = 0;
					nbr_live = 0;
			}*/
			//if(champ->player)
			//	last = champ->player->num;

			if (nbr_live >= NBR_LIVE || checks >= MAX_CHECKS)
			{
				cycles_to_die = cycles_to_die - CYCLE_DELTA;
				checks = 0;
			}
			else
			{
				checks++;
			}
			end_cycle = cycle + cycles_to_die + 1;
			nbr_live = 0;
		}
		if (champ->player && champ->player->time < 0)
		{
			champ->player->time = op_tab[arena[champ->player->pc] - 1].time;
			//printf("\n char %d\n",champ->player->time);
			//printf("OPER %d\n",arena[champ->player->pc]);
				//champ->player->time = 
		}
		if (champ->player && champ->player->time == 0)
		{
			if (arena[champ->player->pc] == 1)
			{
				champ->player->cycle_live = cycle;
				nbr_live++;
			}
			if(arena[champ->player->pc] == 15 || arena[champ->player->pc] == 12)
				champ->num_ch = champ->num_ch + 1;
			op_tab[arena[champ->player->pc] - 1].f(champ->player);
			//printf("INSTR %s  player %d\n",op_tab[arena[champ->player->pc] - 1].name,champ->player->num);
		}
		if (champ->player)
		{
			champ->player->time = champ->player->time - 1;
			//printf("\n time %d\n",champ->player->time);
			i++;
			if (champ->player->next)
				champ->player = rewrite_car(champ->player);
			else
			{
				printf(" WIIIIN %d",champ->player->num);
				free(champ->player);
				champ->player = NULL;
			}
			if (!champ->player)
				printf("NOOOOOOOO");
			if (i % (champ->num_ch - 1) == 0)
				cycle++;
		}
		//prog_count = translate_reg(champ->player->pc);
		//champ->player = champ->player->next;
	}
	printf("last %d",last);
}

unsigned int change_arena(t_champ champ, int n,int num_ch)
{
	unsigned int start = (MEM_SIZE / num_ch) * (n-1);
	//t_reg init;
	//int j = REG_SIZE - 1;
	unsigned int i=0;
	while(i < champ.mem.prog_size)
	{
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
		//printf("i = %d|\n",i);
		while(j > -1)
		{
			printf("champ->champions[j] %d  j %d\n",champ->champions[j].mem.prog_size,j);
			if (i == champ->champions[j].num)
			{
				champ->player->num = champ->champions[j].num;
				champ->player->pc = change_arena(champ->champions[j],i,champ->num_ch);
				champ->player->time = -1;
				champ->player = init_reg(champ->player);
				printf("num %d|\n",champ->player->num);
				champ->player = to_reg_from_int(champ->player, 1, - champ->player->num);
				champ->player->next = malloc(sizeof(t_car));
				champ->player = champ->player->next;
				champ->player->num = -1;
				
			}
			//printf("num %d|\n",j);
			j--;
		}
		j=champ->num_ch - 1;
		i--;
	}
	champ->player = NULL;
	champ->player = start;
	while (start)
	{
		if (start->next->num != -1)
			start = start->next;
		else
		{
			start->next = NULL;
			start = start->next;
		}
	}
	print_arena();
}
void print_arena()
{
	int i =0;

	unsigned int buf = 0;
	while(i < MEM_SIZE)
	{
		buf = arena[i];
		buf = buf & 0x000000ff;
		printf("%x ",buf);
		if (i % 50 ==0 && i!=0)
			printf("\n");
		i++;
	}
	printf("\n");
}

t_core *init_champ(int n,char **argv)
{
	t_core *champ;
    int i;
    int num;

    i = 0;
    champ = malloc(sizeof(t_core));
    //champ->champions = malloc(sizeof( t_champ) * 4);
	champ->player = NULL;
	i=0;
	champ->num_ch = n;
	//printf("N %d|\n",n);
    if (n < MAX_PLAYERS)
    {
        i = 0;
        num = 1;
        while(i < n)
        {
            /*if (argv[i][0] == '-' &&  argv[i][1] == 'n')
            {
                i++;
                num--;
                champ->champions[num].num = atoi(argv[i]);//proverochka
            }
            else
            {*/
            //printf("%s\n",argv[num]);
               // printf("%s %d\n",champ->champions[i].name,i);
                champ->champions[i].num = num;//proverka
                champ->champions[i] = read_champ(argv[num],champ->champions[i]);
               champ->champions[i] = parse(champ->champions[i]);
           // }
            i++;
            num++;
        }
		//print_arena();
    }
    else
    {
        exit(0);
    }
    return(champ);
}

int main(int arc,char **argv)
{
    t_core *champ;
	printf("head %d \n",HEAD_SIZE);
    champ = init_champ(arc - 1,argv);
	arena_set(champ);
	game_start(champ);
	int i =0;
	while(i < champ->num_ch)
	{
		free(champ->champions[i].code);
		i++;
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