#include "virtual.h"
#include <stdio.h>
extern char arena[MEM_SIZE];

unsigned int to_int(char a,char b)
{
	unsigned int sum;

	sum = a;
	sum = sum << 8;
	sum = sum | b;
	return(sum);
}

t_car *copy_car(t_car *copy,t_car *car)
{
	int i = 0;
	int j = 0;
	copy->num = car->num;
	copy->carry = car->carry;
	copy->cycle_live = car->cycle_live;
	copy->time = car->time;
	copy->pc = car->pc;
	while(i < REG_NUMBER)
	{
		while(j < REG_SIZE)
		{
			copy->reg[i].reg[j] = car->reg[i].reg[j];
			j++;
		}
		j = 0;
		i++;
	}
	return(copy);
}

int *read_arg(int *arg,char mem,int size_dir)
{
	if ((mem & 0xc0) == 0x80)
		arg[0] = size_dir;
	if ((mem & 0xc0) == 0x40)
		arg[0] = T_REG;
	if ((mem & 0xc0) == 0xc0)
		arg[0] = T_IND;
	if ((mem & 0x30) == 0x20)
		arg[1] = size_dir;
	if ((mem & 0x30) == 0x10)
		arg[1] = T_REG;
	if ((mem & 0x30) == 0x30)
		arg[1] = T_IND;
	if ((mem & 0x0c) == 0x08)
		arg[2] = size_dir;
	if ((mem & 0x0c) == 0x04)
		arg[2] = T_REG;
	if ((mem & 0x0c) == 0x0c)
		arg[2] = T_IND;
	return(arg);
}

t_car *to_reg_from_int(t_car *car,int reg,unsigned int tr)
{
	int i = 0;
	while(i < 4)
	{
		car->reg[reg].reg[REG_SIZE - i - 1] = tr & 0x000000ff;
		i++;
		tr = tr >> 8;
	}
	return(car);
}

unsigned int to_int_size(int start, int size)
{
	int i = 0;
	unsigned int solve = 0;
	unsigned int n = 0;
	while(i < size)
	{
		printf(" ARENA %d ",arena[start + i]);
		n = (unsigned int)arena[start + i];
		n = n & 0x000000ff;
		printf(" N %i ", n);
		solve = solve | n;
		printf(" solve %i", n);
		i++;
		if( i < size)
			solve = solve << 8;
	}
	printf("\n");
	return(solve);
}

void copy_to_arena(int start,unsigned int copy)
{
	int i = 0;
	while(i < 4)
	{
		arena[start + i] = copy & 0x000000ff;
		i++;
		copy = copy >> 8;
	}
}

unsigned int to_int_from_reg(t_car *car,int reg)
{
	unsigned int solve = 0;
	unsigned int n = 0;
	int i = 0;
	while(i < REG_SIZE)
	{
		printf(" regggg |%d|",car->reg[reg].reg[i]);
		n = (unsigned int)car->reg[reg].reg[i];
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

	printf(" star code %d", car->num);
	//car->num = to_int_size(car->pc + 1, 4);
	printf(" new code %d", car->num);
	car->pc = (car->pc + 5) % MEM_SIZE;
	return(car);
}

t_car	*ft_ld(t_car *car)
{
	//if ()
	int *arg;
	unsigned int in1;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if (arg[0] == 4 && arg[1] == 1)
	{
		in1 = to_int_size(car->pc + 2, 4);
		if ((arena[car->pc + 1] & 0xc0) == 0xc0)
			in1 = arena[in1 % IDX_MOD];
		if (in1 == 0)
			car->carry = 1;
		else
			car->carry = 0;
		car = to_reg_from_int(car,arena[car->pc + 6], in1);
	}
	else
		car->carry = 0;
	car->pc = (car->pc + 2 + arg[0] + arg[1]) % MEM_SIZE;
	return(car);
}

t_car	*ft_st(t_car *car)
{
	//if ()
	int *arg;
	unsigned int in1;
	unsigned int in2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if (arg[0] == 1 && arg[1] == 4)
	{
		in1 = arena[car->pc + 2];
		in1 = in1 & 0x000000ff;
		in2 = to_int_size(car->pc + 3, 4);
		in1 = to_int_from_reg(car,in1);
		copy_to_arena((car->pc + (in2 % IDX_MOD)) % MEM_SIZE ,in1);
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1]) % MEM_SIZE;
	return(car);
}

t_car	*ft_add(t_car *car)
{
	int *arg;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if (arg[0] == 1 && arg[1] == 1 && arg[2] == 1)
	{
		unsigned int reg1 = to_int_from_reg(car,arena[car->pc + 2]);
		unsigned int reg2 = to_int_from_reg(car,arena[car->pc + 3]);
		reg1 = reg1 + reg2;
		if (reg1 == 0)
			car->carry = 1;
		else
			car->carry = 0;
		car = to_reg_from_int(car, arena[car->pc + 4], reg1);
	}
	else
		car->carry = 0;
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}

t_car	*ft_sub(t_car *car)
{
	int *arg;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	if (arg[0] == 1 && arg[1] == 1 && arg[2] == 1)
	{
		unsigned int reg1 = to_int_from_reg(car,arena[car->pc + 2]);
		unsigned int reg2 = to_int_from_reg(car,arena[car->pc + 3]);
		reg1 = reg1 - reg2;
		if (reg1 == 0)
			car->carry = 1;
		else
			car->carry = 0;
		car = to_reg_from_int(car, arena[car->pc + 4], reg1);
	}
	else
		car->carry = 0;
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}

t_car	*ft_and(t_car *car)
{
	int *arg;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	unsigned int in1;
	unsigned int in2;
	if ((arena[car->pc + 1] & 0xc0) == 0x40)
	{
		in1 = to_int_from_reg(car,arena[car->pc + i++]);
	}
	if ((arena[car->pc + 1] & 0xc0) == 0x80)
		in1 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int_size(car->pc + i,4);
		in1 = arena[in1];
		i = i+ 4;
	}
	if ((arena[car->pc + 1] & 0x30) == 0x10)
		in2 = to_int_from_reg(car,arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x20)
		in2 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x30)
	{
		in2 = to_int_size(car->pc + i,4);
		in2 = arena[in1];
		i = i+ 4;
	}
	in1= in1 & in2;
	if (in1 == 0)
		car->carry = 1;
	else
		car->carry = 0;
	printf(" in %i\n",in1);
	if ((arena[car->pc + 1] & 0x0c) == 0x04)
		car = to_reg_from_int(car, car->pc + i, in1);
	else
		car->carry = 0;
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}

t_car	*ft_or(t_car *car)
{
	int *arg;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	unsigned int in1;
	unsigned int in2;
	if ((arena[car->pc + 1] & 0xc0) == 0x40)
	{
		in1 = to_int_from_reg(car,arena[car->pc + i++]);
	}
	if ((arena[car->pc + 1] & 0xc0) == 0x80)
		in1 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int_size(car->pc + i,4);
		in1 = arena[in1];
		i = i+ 4;
	}
	if ((arena[car->pc + 1] & 0x30) == 0x10)
		in2 = to_int_from_reg(car,arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x20)
		in2 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x30)
	{
		in2 = to_int_size(car->pc + i,4);
		in2 = arena[in1];
		i = i+ 4;
	}
	in1= in1 | in2;
	if (in1 == 0)
		car->carry = 1;
	else
		car->carry = 0;
	if ((arena[car->pc + 1] & 0x0c) == 0x04)
		car = to_reg_from_int(car, arena[car->pc + i], in1);
	else
		car->carry = 0;
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}
t_car	*ft_xor(t_car *car)
{
	int *arg;
	int i = 2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	unsigned int in1;
	unsigned int in2;
	if ((arena[car->pc + 1] & 0xc0) == 0x40)
	{
		in1 = to_int_from_reg(car,arena[car->pc + i++]);
	}
	if ((arena[car->pc + 1] & 0xc0) == 0x80)
		in1 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int_size(car->pc + i,4);
		in1 = arena[in1];
		i = i+ 4;
	}
	if ((arena[car->pc + 1] & 0x30) == 0x10)
		in2 = to_int_from_reg(car,arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x20)
		in2 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x30)
	{
		in2 = to_int_size(car->pc + i,4);
		in2 = arena[in1];
		i = i+ 4;
	}
	in1= in1 ^ in2;
	if (in1 == 0)
		car->carry = 1;
	else
		car->carry = 0;
	if ((arena[car->pc + 1] & 0x0c) == 0x04)
		car = to_reg_from_int(car, arena[car->pc + i], in1);
	else
		car->carry = 0;
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	free(arg);
	return(car);
}
t_car	*ft_zjmp(t_car *car)
{
	//if ()
	unsigned int indir;

	indir = to_int(arena[car->pc + 1],arena[car->pc + 2]);
	if (indir != 0 && car->carry == 1)
	{
		car->pc = (car->pc + (indir  % IDX_MOD)) % MEM_SIZE;
	}
	return(car);
}

t_car	*ft_ldi(t_car *car)//че то здесь какой то пиздец
{

	int *arg;
	int i = 2;
	unsigned int in1;
	unsigned int in2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],2);
	if ((arena[car->pc + 1] & 0xc0) == 0xc0)
	{
		in1 = to_int_size(car->pc + i, 4);
		in1 = arena[in1 % IDX_MOD];
		i = i + 4;
	}
	if ((arena[car->pc + 1] & 0xc0) == 0x80)
		in1 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0xc0) == 0x40)
		in1 = to_int_from_reg(car,arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x20)
		in2 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
	if ((arena[car->pc + 1] & 0x30) == 0x10)
		in2 = to_int_from_reg(car,arena[car->pc + i++]);
	in1 = arena[(in1 + in2) % IDX_MOD];
	car = to_reg_from_int(car,arena[car->pc + 6], in1);
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	return(car);
}
t_car	*ft_sti(t_car *car)//здесь тоже
{
	int *arg;
	unsigned int in1;
	unsigned int in2;
	unsigned int reg1;
	int i = 3;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],2);
	if (arena[car->pc + 2] < REG_SIZE)
	{
		if ((arena[car->pc + 1] & 0x30) == 0x20)
			in1 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
		if ((arena[car->pc + 1] & 0x30) == 0x10)
			in1 = to_int_from_reg(car,arena[car->pc + i++]);
		if ((arena[car->pc + 1] & 0x30) == 0x30)
		{
			in1 = to_int_size(car->pc + i, 4);
			in1 = arena[in1];
			i = i + 4;
		}
		if ((arena[car->pc + 1] & 0x0c) == 0x08)
			in2 = to_int(arena[car->pc + i++],arena[car->pc + i++]);
		if ((arena[car->pc + 1] & 0x0c) == 0x04)
			in2 = to_int_from_reg(car,arena[car->pc + i++]);
		reg1 = to_int_from_reg(car,arena[car->pc + 2]);
		printf(" REG %i\n",reg1);
		printf(" arena %d\n",arena[car->pc + 2]);
		copy_to_arena((in1 + in2) % IDX_MOD, reg1);
	}
	car->pc = (car->pc + 2 + arg[0] + arg[1] + arg[2]) % MEM_SIZE;
	printf("\n sti!!! \n");
	print_arena();
	free(arg);
	return(car);
}

t_car	*ft_lld(t_car *car)
{
	car->carry = 1;
	int *arg;
	unsigned int in1;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	in1 = to_int_size(car->pc + 2, 4);
	if ((arena[car->pc + 1] & 0xc0) == 0xc0)
		in1 = arena[in1];
	in1 = in1 % IDX_MOD;
	car = to_reg_from_int(car,arena[car->pc + 6], in1);
	car->pc = (car->pc + 2 + arg[0] + arg[1]) % MEM_SIZE;
	return(car);
}
t_car	*ft_lldi(t_car *car)
{
	car->carry = 1;
	int *arg;
	unsigned int in1;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],4);
	in1 = to_int_size(car->pc + 2, 4);
	if ((arena[car->pc + 1] & 0xc0) == 0xc0)
		in1 = arena[in1];
	car = to_reg_from_int(car,arena[car->pc + 6], in1);
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
	unsigned int in1;
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

	i = 0;
	if (arena[car->pc + 2] <= REG_NUMBER && arena[car->pc + 2] > 0)
	{
		while(i < REG_SIZE)
		{
			write(1,&car->reg[arena[car->pc + 2]].reg[i],1);
			i++;
		}
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
	unsigned int in1;
	in1 = to_int(arena[car->pc + 1],arena[car->pc + 2]);
	copy = copy_car(copy,car);
	copy->pc = (car->pc + (in1 % IDX_MOD)) % MEM_SIZE;
	car->pc = (car->pc + 3) % MEM_SIZE;
	while(car->next)
	{
		car = car->next;
	}
	car->next = copy;
	return(start);
}