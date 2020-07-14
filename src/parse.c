#include "../header/virtual.h"
#include <stdio.h>

char g_arena[MEM_SIZE];
extern t_op    g_op_tab[17];

void ft_error(int ex,int code)
{
	errno = ex;
	perror("Error");
	exit(code);
}

t_core *parse(t_core *champ, int num)
{
	int i = 0;
	champ->champions[num].mem.magic = 0x00000000;
	champ->champions[num].mem.prog_size = 0;
	unsigned int n = 0;
	int j =0;
	while(i< 4)
	{
		n = (unsigned int)champ->champions[num].buf[i];
		n = n & 0x000000ff;
		champ->champions[num].mem.magic = champ->champions[num].mem.magic | n ;
		i++;
		if (i < 4)
			champ->champions[num].mem.magic = champ->champions[num].mem.magic << 8;
	}
	if (champ->champions[num].mem.magic != 15369203)
		ft_error(EINVAL,-2);
	while (j < PROG_NAME_LENGTH)
		champ->champions[num].mem.prog_name[j++] = champ->champions[num].buf[i++];
	i = i+4;
	j =0;
	while (j++ < 4)
	{
		n = (unsigned int)champ->champions[num].buf[i++];
		n = n & 0x000000ff;
		champ->champions[num].mem.prog_size = champ->champions[num].mem.prog_size | n ;
		if (j < 4)
			champ->champions[num].mem.prog_size = champ->champions[num].mem.prog_size << 8;
	}
	j =0;
	if (champ->champions[num].mem.prog_size > CHAMP_MAX_SIZE || champ->champions[num].mem.prog_size < 1)
		ft_error(EFBIG,-1);
	while (j < COMMENT_LENGTH)
		champ->champions[num].mem.comment[j++] = champ->champions[num].buf[i++];
	i = i+4;
	j=0;
	champ->champions[num].code = malloc(champ->champions[num].mem.prog_size + 1);
	while(j < champ->champions[num].mem.prog_size)
		champ->champions[num].code[j++] = champ->champions[num].buf[i++];
	champ->champions[num].code[j] = '\0';
	j = 0;
	free(champ->champions[num].buf);
	return(champ);
}