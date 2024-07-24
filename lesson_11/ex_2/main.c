#include<stdio.h>
#include<unistd.h>
#include<signal.h>

/*
Scrivere un programma C che riceva in input da tastiera due
numeri interi, a e b, e ne stampi a video:
	• la somma "a+b" solo quando riceve il segnale SIGUSR2
	• la differenza "a-b" quando riceve il segnale SIGUSR1
	• Il programma esce quando riceve SIGINT
*/

void sigusr1_handler(int);
void sigusr2_handler(int);

int a,b;

int main(int argc, char *argv[]) {
	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);
	
	while(1) {
		printf("inserire a:");
		scanf("%d",&a);

		printf("inserire b:");
		scanf("%d",&b);

		pause();
	}

	return 0;
}


void sigusr1_handler(int signal) {
	printf("La differenza tra %d e %d e': %d\n", a, b, a-b);
}

void sigusr2_handler(int signal) {
	printf("La somma tra %d e %d e': %d\n", a, b, a+b);
}
