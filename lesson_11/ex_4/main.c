#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>

#define BUF_SIZE 80

/*
Realizzare un programma C e Posix sotto Linux che con l'uso dei
segnali sincronizzi un processo padre ed un processo figlio che
scrivono e leggono, rispettivamente, un numero intero alla volta
(da 1 a n, dove n è passato da riga di comando) nella prima
posizione di un file temporaneo opportunamente creato
*/

void sigusr1_handler(int singal);
void sigusr2_handler(int signal);

int fd;
char buff[BUF_SIZE];	

int main(int argc, char *argv[]) {
	int n, i=1;	

	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);

	fd = open("tmp.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	
	printf("inserisci n:");
	scanf("%d", &n);

	
	pid_t pid = fork();

	if(pid == 0) {
		while(1) {
			pause();
		}
	} else {
		while(i <= n) {
			int written = snprintf(buff, BUF_SIZE, "%d", i);
			
			if(write(fd, buff, written) != written) {
				printf("error while writing in file!\n");
				exit(-1);
			} else {
				printf("%d - written %s\n", getpid(), buff);
			}
			
			kill(pid, SIGUSR1);
			pause();
			lseek(fd, 0, SEEK_SET);
			i++;
		}
	}
	
	close(fd);

	return 0;
}

void sigusr1_handler(int singal) {
	lseek(fd, 0, SEEK_SET);
	if(read(fd, buff, BUF_SIZE) <= 0) {
		printf("error while reading from file!\n");
	}
	
	printf("%d (%d) - read %s\n", getpid(), getppid(), buff);

	kill(getppid(), SIGUSR2);
}

void sigusr2_handler(int signal) {}
