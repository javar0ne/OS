#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

/*
Scrivere un programma C che:
	• Crea un processo figlio, stampa il messaggio “In attesa” ed attende la
	 terminazione del figlio.
	• Il figlio esegue il comando “ls -l”
	• Quando il figlio termina, il padre visualizza il
	 messaggio “nuovo figlio” e crea un secondo processo figlio.
	• Il secondo figlio aspetta per 5 secondi, stampa a video un messaggio e
	 termina.
	• Quando il processo figlio termina, il padre stampa a video il pid del
	 processo terminato
*/

int main(int argc, char *argv[]) {	
	pid_t pid = fork();

	if(pid == 0) {
		//execlp("ls", "-l", NULL);
		execlp("ls", "-l", NULL);
	} else {
		printf("In attesa\n");
		waitpid(pid, NULL, 0);
		
		printf("Nuovo figlio\n");
		
		pid = fork();

		if(pid == 0) {
			sleep(5);
		} else {
			waitpid(pid, NULL, 0);

			printf("Figlio terminato `%d`\n", pid);
		}
	}

	return 0;
}
