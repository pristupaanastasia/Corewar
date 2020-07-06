
#include "../header/virtual.h"
extern char arena[MEM_SIZE];
int to_int(char a,char b)
{
	int sum;

	sum = 0;
	sum = a;
	sum = sum & 0x000000ff;
	sum = sum << 8;
	sum = sum | (b & 0x000000ff);
	if (sum > 0x00007fff)
		sum = sum | 0xfffff000;
	return(sum);
}

t_car *copy_car(t_car *copy,t_car *car)
{
	int i = 0;
	int j = 0;
	copy->num = car->num;
	copy->carry = car->carry;
	copy->cycle_live = car->cycle_live;
	copy->time = -1;
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
		arg[0] = IND_SIZE;
	if ((mem & 0x30) == 0x20)
		arg[1] = size_dir;
	if ((mem & 0x30) == 0x10)
		arg[1] = T_REG;
	if ((mem & 0x30) == 0x30)
		arg[1] = IND_SIZE;
	if ((mem & 0x0c) == 0x08)
		arg[2] = size_dir;
	if ((mem & 0x0c) == 0x04)
		arg[2] = T_REG;
	if ((mem & 0x0c) == 0x0c)
		arg[2] = IND_SIZE;
	return(arg);
}

t_car *to_reg_from_int(t_car *car,int reg,int tr)
{
	int i = 0;
	//printf(" TR %d\n",tr);
	//printf(" REG %d\n",reg);
	while(i < 4)
	{
		car->reg[reg].reg[REG_SIZE - i - 1] = tr & 0x000000ff;
		//printf(" reg   |%d|\n",car->reg[reg].reg[REG_SIZE - i - 1]);
		i++;
		tr = tr >> 8;
	}
	return(car);
}

int to_int_size(int start, int size)
{
	int i = 0;
	int solve = 0;
	int n = 0;
	while(i < size)
	{
		//printf(" ARENA %d ",arena[start + i]);
		n = (int)arena[start + i];
		n = n & 0x000000ff;
		//printf(" N %i ", n);
		solve = solve | n;
		//printf(" solve %i", n);
		i++;
		if( i < size)
			solve = solve << 8;
	}
	//printf("\n");
	return(solve);
}