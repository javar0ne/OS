#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

/*
Scrivere un programma C in cui un processo crea un processo figlio
	• Il processo figlio calcola la sequenza di Fibonacci di ordine n (n<=12)
	 Quando termina restituisce il valore calcolato come codice di
	 terminazione
	• Il padre attende la terminazione del figlio ed esamina lo stato di
	 terminazione
	• Se lo stato di terminazione è relativo ad una terminazione con successo e il codice di
	 terminazione è un valore minore di 50
	• Crea un secondo figlio che esegue il comando ls –al a.out
	• Attende il secondo figlio, stampa un messaggio e termina
	• Altrimenti, stampa un messaggio e termina
*/

int fibonacci(int n) {
	if(n < 2) return 1;

	return fibonacci(n-1) + fibonacci(n-2);
}

int main(int argc, char *argv[]) {
	pid_t pid;
	int n;

	printf("Inserire un valore compreso tra 0 e 12: ");
	scanf("%d", &n);
	
	if(n < 0) n = 0;
	else if(n > 12) n = 12;


	pid = fork();
	
	if(pid == 0) {
		int fibo = fibonacci(n);

		exit(fibo);
	} else {
		int status_code;
		
		waitpid(pid, &status_code, 0);
		
		if(WIFEXITED(status_code)) {
			int exit_code = WEXITSTATUS(status_code);

			if(exit_code < 50) {
				pid = fork();

				if(pid == 0) {
					execlp("ls", "-la", "a.out", NULL);
				} else {
					waitpid(pid, NULL, 0);

					printf("Ho finito!\n");
				}
			}
		} else {
			printf("Ho finito (no ls)\n");
		}		

	}
	
	
	return 0;
}
