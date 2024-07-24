#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include "config.h"

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("low number of params! terminating..\n");
		exit(-1);
	}
	
	char pipe_somma[25];
	strcat(pipe_somma, PREFIX_FIFO_SUM);
	strcat(pipe_somma, argv[1]);

	printf("%s\n", pipe_somma);

	int fd = open(argv[1], O_RDONLY);
	int fd_somma = open(pipe_somma, O_WRONLY);
	char buff[BUF_SIZE];
	int somma = 0;

	while(read(fd, buff, 10) > 0) {
		printf("ricevuto %s\n", buff);
		somma += atoi(buff);

		snprintf(buff, 10, "%d", somma);
		write(fd_somma, buff, 10);
	}

	return 0;
}
