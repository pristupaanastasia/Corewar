
#include "../header/virtual.h"
extern char arena[MEM_SIZE];
t_car	*ft_lldi(t_car *car)
{
	car->carry = 1;
	int *arg;
	int in1;
	int in2;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
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
	in1 = to_int_size(car->pc + (in1 + in2),4);
	if (arena[car->pc + i] > 0 && arena[car->pc + i] <= REG_NUMBER)
		car = to_reg_from_int(car,arena[car->pc + i], in1);
	car->pc = (car->pc + 2 + arg[0] + arg[1]) % MEM_SIZE;
	return(car);
}

t_car	*ft_lfork(t_car *car)
{
	t_car *start;
	t_car *copy;
	copy = malloc(sizeof(t_car));
	start = car;
	int i = 0;
	int j = 0;
	int in1;
	in1 = to_int(arena[car->pc + 1],arena[car->pc + 2]);
	copy = copy_car(copy,car);
	copy->pc = (car->pc + in1) % MEM_SIZE;
	car->pc = (car->pc + 3) % MEM_SIZE;
	while(car->next)
	{
		car = car->next;
	}
	car->next = copy;
	return(start);
}

t_car	*ft_aff(t_car *car)
{
	//if ()
	int i;
	int num;
	char *s;

	i = 0;
	if (arena[car->pc + 2] <= REG_NUMBER && arena[car->pc + 2] > 0)
	{
		num = to_int_from_reg(car,arena[car->pc + 2]);
		s = ft_itoa(num);
		write(1,s,ft_strlen(s));
		free(s);
	}
	car->pc = (car->pc + 3) % MEM_SIZE;
	return(car);
}

t_car	*ft_fork(t_car *car)
{
	//if ()
	t_car *start;
	t_car *copy;
	copy = malloc(sizeof(t_car));
	start = car;
	int i = 0;
	int j = 0;
	int in1;
	in1 = to_int(arena[car->pc + 1],arena[car->pc + 2]);
	copy = copy_car(copy,car);
	copy->pc = (car->pc + in1 % IDX_MOD) % MEM_SIZE;
	car->pc = (car->pc + 3) % MEM_SIZE;
	while(car->next)
	{
		car = car->next;
	}
	car->next = copy;
	copy->next = NULL;
	return(start);
}