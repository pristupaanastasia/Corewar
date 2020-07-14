#include "../header/virtual.h"
extern char g_arena[MEM_SIZE];
t_car	*ft_and(t_car *car)
{
	int *arg;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,g_arena[car->pc + 1],4);
	int in1;
	int in2;
	if ((g_arena[car->pc + 1] & 0xc0) == 0x40)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			in1 = to_int_from_reg(car,g_arena[car->pc + i++]);
	}
	if ((g_arena[car->pc + 1] & 0xc0) == 0x80)
	{
		in1 = to_int_size(car->pc + i,4);
		i = i + 4;
	}
	if ((g_arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int(g_arena[car->pc + i],g_arena[car->pc + i + 1]);
		if ((car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0)
			in1 = to_int_size((car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		else
			in1 = to_int_size(MEM_SIZE  +(car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		i = i+ 2;
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x10)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			in2 = to_int_from_reg(car,g_arena[car->pc + i++]);
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x20)
	{
		in2 = to_int_size(car->pc + i,4);
		i = i + 4;
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x30)
	{
		in2 = to_int(g_arena[car->pc + i],g_arena[car->pc + i + 1]);
		if ((car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0)
			in2 = to_int_size((car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		else
			in2 = to_int_size(MEM_SIZE  +(car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		i = i+ 2;
	}
	in1= in1 & in2;
	if (in1 == 0)
		car->carry = 1;
	else
		car->carry = 0;
	//printf(" in %i\n",in1);
	if ((g_arena[car->pc + 1] & 0x0c) == 0x04)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			car = to_reg_from_int(car, g_arena[car->pc + i], in1);
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}

t_car	*ft_or(t_car *car)
{
	int *arg;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,g_arena[car->pc + 1],4);
	int in1 = 0;
	int in2 = 0;
	if ((g_arena[car->pc + 1] & 0xc0) == 0x40)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			in1 = to_int_from_reg(car,g_arena[car->pc + i++]);
	}
	if ((g_arena[car->pc + 1] & 0xc0) == 0x80)
	{
		in1 = to_int_size(car->pc + i,4);
		i = i + 4;
	}
	if ((g_arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int(g_arena[car->pc + i],g_arena[car->pc + i + 1]);
		if ((car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0)
			in1 = to_int_size((car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		else
			in1 = to_int_size(MEM_SIZE  + (car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		i = i+ 2;
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x10)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			in2 = to_int_from_reg(car,g_arena[car->pc + i++]);
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x20)
	{
		in2 = to_int_size(car->pc + i,4);
		i = i + 4;
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x30)
	{
		in2 = to_int(g_arena[car->pc + i],g_arena[car->pc + i + 1]);
		if ((car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0)
			in2 = to_int_size((car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		else
			in2 = to_int_size(MEM_SIZE  + (car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		i = i+ 2;
	}
	in1= in1 | in2;
	if (in1 == 0)
		car->carry = 1;
	else
		car->carry = 0;
	if ((g_arena[car->pc + 1] & 0x0c) == 0x04)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			car = to_reg_from_int(car, g_arena[car->pc + i], in1);
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}
t_car	*ft_xor(t_car *car)
{
	int *arg;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,g_arena[car->pc + 1],4);
	int in1;
	int in2;
	if ((g_arena[car->pc + 1] & 0xc0) == 0x40)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			in1 = to_int_from_reg(car,g_arena[car->pc + i++]);
	}
	if ((g_arena[car->pc + 1] & 0xc0) == 0x80)
	{
		in1 = to_int_size(car->pc + i,4);
		i = i + 4;
	}
	if ((g_arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int(g_arena[car->pc + i],g_arena[car->pc + i + 1]);
		if ((car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0)
			in1 = to_int_size((car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		else
			in1 = to_int_size(MEM_SIZE  +(car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		i = i+ 2;
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x10)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			in2 = to_int_from_reg(car,g_arena[car->pc + i++]);
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x20)
	{
		in2 = to_int_size(car->pc + i,4);
		i = i + 4;
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x30)
	{
		in2 = to_int(g_arena[car->pc + i],g_arena[car->pc + i + 1]);
		if ((car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0)
			in2 = to_int_size((car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		else
			in2 = to_int_size(MEM_SIZE  +(car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		i = i+ 2;
	}
	in1= in1 ^ in2;
	if (in1 == 0)
		car->carry = 1;
	else
		car->carry = 0;
	if ((g_arena[car->pc + 1] & 0x0c) == 0x04)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			car = to_reg_from_int(car, g_arena[car->pc + i], in1);
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}