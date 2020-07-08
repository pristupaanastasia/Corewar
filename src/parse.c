#include "../header/virtual.h"
#include <stdio.h>

char arena[MEM_SIZE];
extern t_op    op_tab[17];

t_champ parse(t_champ champ)
{
	int i = 0;
	champ.mem.magic = 0x00000000;
	champ.mem.prog_size = 0;
	unsigned int n = 0;
	int j =0;
	while(i< 4)
	{
		n = (unsigned int)champ.buf[i];
		n = n & 0x000000ff;
		//printf("n %x\n",n);
		champ.mem.magic = champ.mem.magic | n ;
		//print_mem(champ.mem.magic);
		i++;
		if (i < 4)
			champ.mem.magic = champ.mem.magic << 8;
	}
	if (champ.mem.magic != 15369203)
	{
		errno = EINVAL;
		perror("Error");
		exit(-2);
	}
	while (j < PROG_NAME_LENGTH)
	{
		champ.mem.prog_name[j] = champ.buf[i];
		i++;
		j++;
	}
	i = i+4;
	j =0;
	while (j < 4)
	{
		n = (unsigned int)champ.buf[i];
		n = n & 0x000000ff;
		champ.mem.prog_size = champ.mem.prog_size | n ;
		i++;
		j++;
		if (j < 4)
			champ.mem.prog_size = champ.mem.prog_size << 8;
	}
	//printf("prog_size %d\n",champ.mem.prog_size);
	j =0;
	if (champ.mem.prog_size > CHAMP_MAX_SIZE || champ.mem.prog_size < 1)
	{
		if (champ.mem.prog_size < 1)
			errno = ENOTSUP;
		else
			errno = EFBIG;
		perror("Error");
		exit(-1);
	}
	while (j < COMMENT_LENGTH)
	{
		champ.mem.comment[j] = champ.buf[i];
		i++;
		j++;
	}
	//printf("comment %s\n",champ.mem.comment);
	i = i+4;
	j=0;
	champ.code = malloc(champ.mem.prog_size + 1);
	while(j < champ.mem.prog_size)
	{
		champ.code[j] = champ.buf[i];
		i++;
		j++;
	}
	champ.code[j] = '\0';
	j = 0;
	return(champ);
}