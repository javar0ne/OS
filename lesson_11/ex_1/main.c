#include<stdio.h>
#include<signal.h>
#include<unistd.h>
/*
 *Scrivere un programma che intercetta CTRL-c ed invece di terminare scrive su stdout “non voglio terminare”
 * */

void interrupt_handler(int);
void suspend_handler(int);

int canRun=1;

int main() {
	signal(SIGINT, interrupt_handler);
	signal(SIGTSTP, suspend_handler);

	while(canRun) {
		printf("in attesa di un segnale\n");
		pause();
	}

	return 0;
}

void interrupt_handler(int signal) {
	printf("\nnon voglio terminare!\n");
}

void suspend_handler(int signal) {
	canRun=0;
	printf("\ntermino :(\n");
}
