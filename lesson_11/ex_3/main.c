#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

/*
Scrivere un programma in C e Posix sotto Linux che, preso un argomento intero positivo da riga di
comando, genera due figli A e B e:
	- se l'argomento è PARI invia un segnale SIGUSR1 alla ricezione del quale il figlio A calcola il cubo
	del numero passato come argomento da linea di comando, mentre il figlio B stampa un messaggio
	di arrivederci e termina.
	- se l'argomento è DISPARI invia un segnale SIGUSR2 alla ricezione del quale il figlio B calcola il
	reciproco del numero passato come argomento, attende per un numero di secondi pari al doppio
	del numero passato come argomento ed invia un segnale SIGUSR1 al processo A dopodiché
	termina l'esecuzione. Il figlio A, invece, attende la ricezione del segnale SIGUSR1, stampa un
	messaggio e termina
*/

int num;
pid_t pid_a,pid_b;

void sigusr1_pari_A_handler(int);
void sigusr1_dispari_A_handler(int);
void sigusr2_dispari_B_handler(int);

int main(int argc, char *argv[]) {
	printf("inserire un numero: ");
	scanf("%d", &num);

	if(num%2==0) {
		signal(SIGUSR1, sigusr1_pari_A_handler);
		pid_a = fork();
		
		if(pid_a == 0) {
			pause();
		} else {
			pid_b = fork();
			
			if(pid_b == 0) {
				printf("figlio B, num pari.\n");
			} else {
				kill(pid_a, SIGUSR1);
			}
		}
	} else {
		signal(SIGUSR1, sigusr1_dispari_A_handler);
		signal(SIGUSR2, sigusr2_dispari_B_handler);
		
		pid_a = fork();
		
		if(pid_a == 0) {
			pause();
			exit(0);
		} else {
			pid_b = fork();

			if(pid_b == 0) {
				pause();
				exit(0);
			} else {
				kill(pid_b, SIGUSR2);
			}
		}
	}

	return 0;
}

void sigusr1_pari_A_handler(int signal) {
	printf("figlio A, num pari. il cubo di num: %d\n", num*num*num);
}

void sigusr2_dispari_B_handler(int signal) {
	printf("figlio B, num dispari. il reciproco di num: %f\n", 1/(float)num);

	sleep(num*2);

	kill(pid_a, SIGUSR1);
}

void sigusr1_dispari_A_handler(int signal) {
	printf("figlio A, num dispari.\n");
}
