#include "../header/virtual.h"
#include <stdio.h>

char arena[MEM_SIZE];
extern t_op    op_tab[17];


int *parse_num(int *nums,char **argv,int n)
{
	int i =0;
	int j = 0;
	int max;
	int flag = 0;
	while (i < 4)
	{
		nums[i++] = -1;
	}
	i=1;
	while(i <= n)
	{
		if (ft_strstr(argv[i],".cor"))
		{
			j++;
		}
		if (ft_strequ(argv[i],"-n") == 1)
		{
			i++;
			nums[j] = ft_atoi(argv[i]);
		}
		i++;
	}
	i = 1;
	max = j;
	j = 0;
	while (i <= max)
	{
		while(j < max)
		{
			if (nums[j] == i)
				flag = 1;
			j++;
		}
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
	return(nums);
}

t_core *init_champ(int n,char **argv)
{
	t_core *champ;
    int i;
    int num;

    champ = malloc(sizeof(t_core));
    //champ->champions = malloc(sizeof( t_champ) * 4);
	champ->player = NULL;
	i=1;
	num = 0;
	champ->d_cycle = -1;
	//printf("N %d|\n",n);
	int *nums;
	nums = malloc(4 * sizeof(int));
	nums = parse_num(nums,argv,n);
	while (i <= n)
	{
		if (ft_strequ(argv[i],"-dump"))
		{
			champ->dump = 64;
			i++;
			champ->d_cycle = ft_atoi(argv[i]);
		}
		if (ft_strequ(argv[i],"-d"))
		{
			champ->dump = 64;
			i++;
			champ->d_cycle = ft_atoi(argv[i]);
		}
		if (ft_strstr(argv[i],".cor"))
		{
			champ->champions[num].num = nums[num];//proverka
			champ->champions[num] = read_champ(argv[i],champ->champions[num]);
			champ->champions[num] = parse(champ->champions[num]);
			num++;
		}
		i++;
	}
	champ->num_ch = num;
    return(champ);
}

int main(int arc,char **argv)
{
    t_core *champ;
	//printf("Introducing contestants...\n");
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