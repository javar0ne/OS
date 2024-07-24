#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>

/*
Scrivere un programma C Posix, in ambiente Unix/Linux che
implementi la seguente comunicazione:
	• Un processo padre genera un numeri casuali nell’intervallo [1,10] e li invia
	 ad un processo figlio fino a quando scade un timer di N secondi, con N
	 fornito da riga di comando
	• Il processo figlio normalizza i numeri nell’intervallo [0,1] e li restituisce al
	 processo padre, comunicandogli l’ultimo numero inviato con un segnale
	 SIGUSR1
	• Il padre, ricevuto il segnale termina il processo figlio e stampa i numeri
	 normalizzati
*/


void sigusr1_hdl(int signo);
void sigusr2_hdl(int signo);

int running = 1;

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("incorrect number of parameters provided! terminating..\n");
		exit(1);
	}	

	int num;
	int child_idx = 0;
	int n;
	float *nums;
	int fd1[2], fd2[2];
	pid_t pid;

	pipe(fd1);
	pipe(fd2);
	
	n = atoi(argv[1]);
	printf("provided timer of %d seconds\n", n);
	
	nums = (float *) malloc(n * sizeof(float));	
	
	signal(SIGUSR1, sigusr1_hdl);
	signal(SIGUSR2, sigusr2_hdl);

	pid = fork();

	if(pid == 0) {
		float normalized;
		char buff[500];
		
		close(fd1[1]);
		close(fd2[0]);

		while(running) {
			if(read(fd1[0], buff, 500) > 0) {
				printf("got %s\t", buff);
				normalized = atof(buff) / 10;
				printf("normalized %f\n", normalized);
	
				snprintf(buff, 500, "%f", normalized);
				write(fd2[1], buff, 500);
			} 
		}

	} else {
		int i = 0;
		char buff[500];

		close(fd1[0]);
		close(fd2[1]);

		srand(time(NULL));
		
		while(i<n) {
			num = rand() % 11;

			nums[i++] = num;
			
			snprintf(buff, 500, "%f", nums[i-1]);
			write(fd1[1], buff, 500);

			read(fd2[0], buff, 500);

			nums[i-1] = atof(buff);	

			sleep(1);	
		}

		kill(pid, SIGUSR1);
		pause();

		for(int j = 0; j < n; j++) {
			printf("%f\n", nums[j]);
		}
	}


	return 0;
}

void sigusr1_hdl(int signo) {
	running = 0;
	kill(getppid(), SIGUSR2);
}

void sigusr2_hdl(int signo) {}
