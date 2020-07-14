#ifndef VIRTUAL_H
# define VIRTUAL_H

#include <fcntl.h>	/* open() and O_XXX flags */
#include <sys/stat.h>	/* S_IXXX flags */
#include <sys/types.h>	/* mode_t */
#include <unistd.h>	
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "op.h"
#include <errno.h>

#define HEAD_SIZE COMMENT_LENGTH+PROG_NAME_LENGTH+CHAMP_MAX_SIZE+10

typedef struct	s_champ
{
	char			*buf;
	head_t			mem;
	char			*code;
	int				num;
}				t_champ;

typedef struct	s_reg
{
	char			reg[REG_SIZE];
}				t_reg;

typedef struct	s_car
{
	int				num;
	unsigned int	carry;
	int				cycle_live;
	unsigned		int pc;
	int				time;
	t_reg			reg[REG_NUMBER + 1];
	struct s_car	*next;

}				t_car;

typedef struct	s_core
{
	int				num_ch;
	t_car			*player;
	t_champ			champions[4];
	int				dump;
	int				d_cycle;
}				t_core;

typedef struct	s_op
{
	char			*name;
	int				oper;
	int				arg[3];
	int				num;
	int				time;
	char			*tr;
	int				key_arg;
	int				re_carry;
	t_car *(*f)(t_car *car);
}				t_op;


t_car	*ft_live(t_car *car);
t_car	*ft_ld(t_car *car);
t_car	*ft_st(t_car *car);
t_car	*ft_add(t_car *car);
t_car	*ft_sub(t_car *car);
t_car	*ft_and(t_car *car);
t_car	*ft_or(t_car *car);
t_car	*ft_xor(t_car *car);
t_car	*ft_zjmp(t_car *car);
t_car	*ft_fork(t_car *car);
t_car	*ft_ldi(t_car *car);
t_car	*ft_sti(t_car *car);
t_car	*ft_lld(t_car *car);
t_car	*ft_lldi(t_car *car);
t_car	*ft_lfork(t_car *car);
t_car	*ft_aff(t_car *car);
void	print_arena();
void	print_char(char k);
void	copy_to_arena(int start,int copy);
int		to_int_from_reg(t_car *car,int reg);
t_car	*to_reg_from_int(t_car *car,int reg,int tr);
int		to_int(char a,char b);
t_car	*copy_car(t_car *copy,t_car *car);
int		*read_arg(int *arg,char mem,int size_dir);
t_car	*to_reg_from_int(t_car *car,int reg,int tr);
int		to_int_size(int start, int size);
t_car	*ft_live(t_car *car);
t_car	*ft_ld(t_car *car);
t_car	*ft_lldi(t_car *car);
t_car	*ft_lfork(t_car *car);
t_car	*ft_aff(t_car *car);
t_car	*ft_fork(t_car *car);
t_core	*init_champ(int n,char **argv);
int		*parse_num(int *nums,char **argv,int n);
void	game_start(t_core *champ);
void	arena_set(t_core *champ);
void	print_arena(int num);
t_core *parse(t_core *champ, int num);
t_core *read_champ(char *s, t_core *core, int num);
void print_mem(unsigned int n);
void print_char(char k);
void print_hello(t_core *champ);
t_car *check_die(t_car *car, int cycle, int cycles_to_die,t_core *champ);
t_car *time_to_die(t_car *car);
t_car *init_reg(t_car *car);
unsigned int change_arena(t_champ champ, int n,int num_ch);
void ft_error(int ex,int code);
#endif