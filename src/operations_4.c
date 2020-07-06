#include "../header/virtual.h"
extern char arena[MEM_SIZE];
t_car	*ft_st(t_car *car)
{
	//if ()
	int *arg;
	int in1;
	int in2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if (arg[0] == 1 && (arg[1] == 1 || arg[1] == 2))
	{
		if (arena[car->pc + 2] > 0 && arena[car->pc + 2] <= REG_NUMBER)
			in1 = to_int_from_reg(car,arena[car->pc + 2]);
		if (arg[1] == 1)
		{
			if (arena[car->pc + 3] > 0 && arena[car->pc + 3] <= REG_NUMBER)
			{
				//in2 = to_int_from_reg(car,arena[car->pc + 3]);
				car = to_reg_from_int(car,arena[car->pc + 3],in1);
			}
		}
		else
		{
			in2 = to_int(arena[car->pc + 3],arena[car->pc + 4]);
			//in2 = arena[car->pc + in1 % IDX_MOD];
			if (arena[car->pc + 2] > 0 && arena[car->pc + 2] <= REG_NUMBER)
			{
				if ((car->pc + (in2 % IDX_MOD)) % MEM_SIZE >=0)
					copy_to_arena((car->pc + (in2 % IDX_MOD)) % MEM_SIZE ,in1);
				else
					copy_to_arena( MEM_SIZE - 1 + (car->pc + (in2 % IDX_MOD)) % MEM_SIZE ,in1);
			}
		}
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1]) % MEM_SIZE;
	return(car);
}

t_car	*ft_add(t_car *car)
{
	int *arg;
	int reg1 = 0;
	int reg2 = 0;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if (arena[car->pc + 2] > 0 && arena[car->pc + 2] <= REG_NUMBER && arena[car->pc + 3] > 0 && arena[car->pc + 3] <= REG_NUMBER && arena[car->pc + 4] > 0 && arena[car->pc + 4] <= REG_NUMBER && arg[0] == 1 && arg[1] == 1 && arg[2] == 1)
	{
		reg1 = to_int_from_reg(car,arena[car->pc + 2]);
		reg2 = to_int_from_reg(car,arena[car->pc + 3]);
		reg1 = reg1 + reg2;
		if (reg1 == 0)
			car->carry = 1;
		else
			car->carry = 0;
		car = to_reg_from_int(car, arena[car->pc + 4], reg1);
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}

t_car	*ft_sub(t_car *car)
{
	int *arg;
	int reg1 = 0;
	int reg2 = 0;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if (arena[car->pc + 2] > 0 && arena[car->pc + 2] <= REG_NUMBER && arena[car->pc + 3] > 0 && arena[car->pc + 3] <= REG_NUMBER && arena[car->pc + 4] > 0 && arena[car->pc + 4] <= REG_NUMBER && arg[0] == 1 && arg[1] == 1 && arg[2] == 1)
	{
		reg1 = to_int_from_reg(car,arena[car->pc + 2]);
		reg2 = to_int_from_reg(car,arena[car->pc + 3]);
		reg1 = reg1 - reg2;
		if (reg1 == 0)
			car->carry = 1;
		else
			car->carry = 0;
		car = to_reg_from_int(car, arena[car->pc + 4], reg1);
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}
