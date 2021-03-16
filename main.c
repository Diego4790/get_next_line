#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    char    *line;
    int     fd;
    int     ret;

    line = NULL;
	fd = open("/Users/dileleux/get_next_line/Get_Next_Line_Tester/test/64bit_paragraph.txt", O_RDONLY);

	while ((ret = get_next_line(fd, &line)) == 1)
	{	
		printf("return = %d '%s'\n", ret, line);
    	if (ret == 0 || ret == -1)
			break ;
	}
	if (ret == 0)
		printf("return = %d '%s'\n", ret, line);
	if (ret < 0)
		printf("Return is -1 => ERROR\n");
	
	free(line);
    close(fd);
    return (0);
}
