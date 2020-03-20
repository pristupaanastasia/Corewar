#ifndef VIRTUAL_H
# define VIRTUAL_H

# define REG_NUMBER 8
# define  REG_SIZE 8
#include <fcntl.h>	/* open() and O_XXX flags */
#include <sys/stat.h>	/* S_IXXX flags */
#include <sys/types.h>	/* mode_t */
#include <unistd.h>	
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "op.h"

typedef struct s_champ
{
    char *name;
    char *comment;
    int num;
    int fd;
    char *ins;

}               t_champ;

typedef struct s_car
{
    int num;
    int carry;

}               t_car;

typedef struct s_core
{
    int     num_ch;
    t_champ *champions;
    void *arena;

}               t_core;
#endif