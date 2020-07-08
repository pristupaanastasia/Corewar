#include "../header/virtual.h"
extern char arena[MEM_SIZE];
void	copy_to_arena(int start,int copy)
{
	int i = 0;
	while(i < 4)
	{
		//printf("do %d| ",arena[start + 3 - i]);
		arena[start + 3 - i] = (char)(copy & 0x000000ff);
		//printf("posle %d ",arena[start + 3 - i]);
		i++;
		copy = copy >> 8;
	}
//	printf("\n");
}

int		to_int_from_reg(t_car *car,int reg)
{
	int solve = 0;
	int n = 0;
	int i = 0;
	while(i < REG_SIZE)
	{
		n = (int)car->reg[reg].reg[i];
		n = n & 0x000000ff;
		solve = solve | n;
		i++;
		if( i < REG_SIZE)
			solve = solve << 8;
	}
	return(solve);
}


t_car	*ft_live(t_car *car)
{
//	car->time = op_tab[0].time;
	int k = - to_int_size(car->pc + 1,4);
	if (k > 0)
		car->num = k;
	car->pc = (car->pc + 5) % MEM_SIZE;
	return(car);
}

t_car	*ft_ld(t_car *car)
{
	int *arg;
	int in1 = 0;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if ((arg[0] == 4 || arg[0] == 2) && arg[1] == 1)
	{
		if (arg[0] == 4)
		{
			in1 = to_int_size(car->pc + 2, 4);
			i = i+ 4;
		}
		else
		{
			in1 = to_int(arena[car->pc + 2],arena[car->pc + 3]);
			in1 = (car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0 ? to_int_size((car->pc + in1 % IDX_MOD) % MEM_SIZE,
			4) : to_int_size(MEM_SIZE - 1 + (car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
			i = i + 2;
		}
		if (arena[car->pc + i] > 0 && arena[car->pc + i] <= REG_NUMBER)
			car = to_reg_from_int(car,arena[car->pc + i], in1);
		car->carry = in1 == 0 ? 1 : 0;
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1]) % MEM_SIZE;
	free(arg);
	return(car);
}
