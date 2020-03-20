#include "virtual.h"
char *read_champ(char *s)
{
    char *line;
    char *buf;
    int fd;

    fd = open(s,O_RDONLY);
    buf = NULL;
    while(get_next_line(fd,&line))
    {
        if (!buf)
            buf = ft_strdup(line);
        else
        {
            buf = ft_strjoin(buf,line);
        }
    }
    return(buf);
}

t_core *init_champ(int n,char **argv)
{
    t_core *champ;
    int i;
    int num;

    if (n-1 < MAX_PLAYERS)
    {
        while(i < n - 1)
        {
            champ->champions[i].name = malloc(50);
            i++;
        }
        i = 1;
        num = 0;
        while(i < n)
        {
            if (argv[i][0] == '-' &&  argv[i][1] == 'n')
            {
                i++;
                num--;
                champ->champions[num].num = atoi(argv[i]);//proverochka
            }
            else
            {
                champ->champions[num].name = ft_strcpy(champ->champions[num].name,argv[i]);
                champ->champions[num].num = num;//proverka
                champ->champions[num].comment = read_champ(argv[i]);
            }
            i++;
            num++;
        }
    }
    else
    {
        exit(0);
    }
    
}

int main(int arc,char **argv)
{
    int i;

    i = 1;
    t_core *champ;

    champ = init_champ(arc,argv);
    champ->arena = malloc(MEM_SIZE);
    while ()
}