#include "../header/virtual.h"
#include <stdio.h>

extern char arena[MEM_SIZE];

t_car	*ft_zjmp(t_car *car)
{
	//if ()
	int indir;

	indir = to_int(arena[car->pc + 1],arena[car->pc + 2]);
	if (indir != 0 && car->carry == 1)
	{
		//printf("car %d PRIG\n",car->num);
		car->pc = (car->pc + (indir  % IDX_MOD)) % MEM_SIZE;
		if (car->pc < 0)
			car->pc = MEM_SIZE + car->pc;
	}
	else
	{
		car->pc = (car->pc + 3) % MEM_SIZE;
	}
	return(car);
}

t_car	*ft_ldi(t_car *car)
{

	int *arg;
	int i = 2;
	int in1;
	int in2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],2);
	if ((arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int(arena[car->pc + i],arena[car->pc + i + 1]);
		in1 = to_int_size(car->pc + in1 % IDX_MOD,4);
		i = i + 2;
	}
	if ((arena[car->pc + 1] & 0xc0) == 0x80)
		in1 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0xc0) == 0x40)
	{
		if (arena[car->pc + i] > 0 && arena[car->pc + i] <= REG_NUMBER)
			in1 = to_int_from_reg(car,arena[car->pc + i++]);
	}
	if ((arena[car->pc + 1] & 0x30) == 0x20)
		in2 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x10)
	{
		if (arena[car->pc + i] > 0 && arena[car->pc + i] <= REG_NUMBER)
			in2 = to_int_from_reg(car,arena[car->pc + i++]);
	}
	in1 = to_int_size(car->pc + (in1 + in2) % IDX_MOD,4);
	if (arena[car->pc + i] > 0 && arena[car->pc + i] <= REG_NUMBER)
		car = to_reg_from_int(car,arena[car->pc + i], in1);
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}
t_car	*ft_sti(t_car *car)
{
	int *arg;
	int in1;
	int in2;
	int reg1;
	int i = 3;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],2);
	if (arena[car->pc + 2] < REG_NUMBER)
	{
		if ((arena[car->pc + 1] & 0x30) == 0x20)
			in1 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
		if ((arena[car->pc + 1] & 0x30) == 0x10)
		{
			if (arena[car->pc + i] > 0 && arena[car->pc + i] <= REG_NUMBER)
				in1 = to_int_from_reg(car,arena[car->pc + i++]);
		}
		if ((arena[car->pc + 1] & 0x30) == 0x30)
		{
			in1 = to_int(arena[car->pc + i],arena[car->pc + i + 1]);
			in1 = to_int_size(car->pc + in1 % IDX_MOD,4);
			i = i + 2;
		}
		if ((arena[car->pc + 1] & 0x0c) == 0x08)
			in2 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
		if ((arena[car->pc + 1] & 0x0c) == 0x04)
		{
			if (arena[car->pc + i] > 0 && arena[car->pc + i] <= REG_NUMBER)
				in2 = to_int_from_reg(car,arena[car->pc + i++]);
		}
		if (arena[car->pc + 2] > 0 && arena[car->pc + 2] <= REG_NUMBER)
		{
			reg1 = to_int_from_reg(car,arena[car->pc + 2]);
		//printf(" REG %i\n",reg1);
		//printf(" arena %d\n",arena[car->pc + 2]);
		//printf(" ar1 %d ar2 %d ar3 %d\n",arg[0],arg[1], arg[2]);
			if ((car->pc +  (in1 + in2) % IDX_MOD) % MEM_SIZE >= 0)
				copy_to_arena( (car->pc +  (in1 + in2) % IDX_MOD) % MEM_SIZE, reg1);
			else
				copy_to_arena( MEM_SIZE -1 + (car->pc +  (in1 + in2) % IDX_MOD) % MEM_SIZE, reg1);
		}
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	//printf("\n sti!!! \n");
	//print_arena();
	free(arg);
	return(car);
}

t_car	*ft_lld(t_car *car)
{
	car->carry = 1;
	int *arg;
	int in1;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if (arg[0] == 4)
	{
		in1 = to_int_size(car->pc + i, 4);
		i = i + 4;
	}
	if (arg[0] == 2)
	{
		in1 = to_int(arena[car->pc + i],arena[car->pc + i + 1]);
		i = i + 2;
		in1 = to_int_size(car->pc + in1,4);
	}
	if (arena[car->pc + i] > 0 && arena[car->pc + i] <= REG_NUMBER)
		car = to_reg_from_int(car,arena[car->pc + i], in1);
	car->pc = (car->pc + 2 + arg[0] + arg[1]) % MEM_SIZE;
	free(arg);
	return(car);
}
