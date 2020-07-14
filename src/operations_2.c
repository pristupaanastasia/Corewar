
#include "../header/virtual.h"
extern char	g_arena[MEM_SIZE];
t_car	*ft_lldi(t_car *car)
{
	car->carry = 1;
	int *arg;
	int in1;
	int in2;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,g_arena[car->pc + 1],4);
	if ((g_arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int(g_arena[car->pc + i],g_arena[car->pc + i + 1]);
		if ((car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0)
			in1 = to_int_size((car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		else
			in1 = to_int_size(MEM_SIZE  + (car->pc + in1 % IDX_MOD) % MEM_SIZE,4);
		i = i + 2;
	}
	if ((g_arena[car->pc + 1] & 0xc0) == 0x80)
		in1 = to_int(g_arena[car->pc + i++],g_arena[car->pc + i++]);
	if ((g_arena[car->pc + 1] & 0xc0) == 0x40)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			in1 = to_int_from_reg(car,g_arena[car->pc + i++]);
	}
	if ((g_arena[car->pc + 1] & 0x30) == 0x20)
		in2 = to_int(g_arena[car->pc + i++],g_arena[car->pc + i++]);
	if ((g_arena[car->pc + 1] & 0x30) == 0x10)
	{
		if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
			in2 = to_int_from_reg(car,g_arena[car->pc + i++]);
	}
	if ((car->pc + (in1 + in2)) % MEM_SIZE >= 0)
		in1 = to_int_size((car->pc + (in1 + in2)) % MEM_SIZE,4);
	else
		in1 = to_int_size(MEM_SIZE  + (car->pc + (in1 + in2)) % MEM_SIZE,4);
	if (g_arena[car->pc + i] > 0 && g_arena[car->pc + i] <= REG_NUMBER)
		car = to_reg_from_int(car,g_arena[car->pc + i], in1);
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
	in1 = to_int(g_arena[car->pc + 1],g_arena[car->pc + 2]);
	copy = copy_car(copy,car);
	if ((car->pc + in1) % MEM_SIZE >= 0)
		copy->pc = (car->pc + in1) % MEM_SIZE;
	else
		copy->pc = MEM_SIZE -1 + (car->pc + in1) % MEM_SIZE;
	car->pc = (car->pc + 3) % MEM_SIZE;
	while(car && car->next)
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
	if (g_arena[car->pc + 2] <= REG_NUMBER && g_arena[car->pc + 2] > 0)
	{
		num = to_int_from_reg(car,g_arena[car->pc + 2]);
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
	in1 = to_int(g_arena[car->pc + 1],g_arena[car->pc + 2]);
	copy = copy_car(copy,car);
	if ((car->pc + in1 % IDX_MOD) % MEM_SIZE >= 0)
		copy->pc = (car->pc + in1 % IDX_MOD) % MEM_SIZE;
	else
		copy->pc = MEM_SIZE  + (car->pc + in1 % IDX_MOD) % MEM_SIZE;
	car->pc = (car->pc + 3) % MEM_SIZE;
	while(car->next)
	{
		car = car->next;
	}
	car->next = copy;
	copy->next = NULL;
	return(start);
}