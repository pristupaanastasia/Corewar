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

t_car	*ft_live(t_car *car)
{
//	car->time = op_tab[0].time;
	car->pc = car->pc + 6;
	return(car);
}

t_car	*ft_ld(t_car *car)
{
	//if ()
	return(car);
}

t_car	*ft_st(t_car *car)
{
	//if ()
	return(car);
}

t_car	*ft_add(t_car *car)
{
	//if ()
	return(car);
}

t_car	*ft_sub(t_car *car)
{
	//if ()
	return(car);
}

t_car	*ft_and(t_car *car)
{
	//if ()
	return(car);
}

t_car	*ft_or(t_car *car)
{
	//if ()
	return(car);
}
t_car	*ft_xor(t_car *car)
{
	//if ()
	return(car);
}
t_car	*ft_zjmp(t_car *car)
{
	//if ()
	return(car);
}
t_car	*ft_ldi(t_car *car)
{
	//if ()
	return(car);
}
t_car	*ft_sti(t_car *car)
{
	printf("\n kod \n");
	print_char(arena[car->pc]);
	printf("\n kod  tipov\n");
	int *arg;
	unsigned int in1;
	unsigned int in2;
	arg = malloc(sizeof(int) * 3);
	arg = read_arg(arg,arena[car->pc + 1],2);
	print_char(arena[car->pc + 1]);
	printf("\n");
	print_char(arena[car->pc + 1]& 0x0c);
	
	printf("\n arg %d %d %d \n",arg[0],arg[1],arg[2]);
	printf("\n arg n1\n");
	print_char(arena[car->pc + 2]);
	if (arena[car->pc + 2] < REG_SIZE )
	{
		in1 = to_int(arena[car->pc + 3],arena[car->pc + 4]);
		in2 = to_int(arena[car->pc + 5],arena[car->pc + 6]);
		car = to_reg_from_int(car,arena[car->pc + 2], in1 + in2);
	}
	printf("REG %x\n",car->reg[arena[car->pc + 2]].reg[REG_SIZE -1]);
	printf("\n arg n2\n");
	print_char(arena[car->pc + 3]);
	print_char(arena[car->pc + 4]);
	printf("\n arg n3\n");
	print_char(arena[car->pc + 5]);
	print_char(arena[car->pc + 6]);
	//if ()
	free(arg);
	return(car);
}

t_car	*ft_lld(t_car *car)
{
	//if ()
	return(car);
}
t_car	*ft_lldi(t_car *car)
{
	//if ()
	return(car);
}
t_car	*ft_lfork(t_car *car)
{
	//if ()
	return(car);
}
t_car	*ft_aff(t_car *car)
{
	//if ()
	return(car);
}
t_car	*ft_fork(t_car *car)
{
	//if ()
	return(car);
}