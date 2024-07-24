#include<stdio.h>
#include<unistd.h>

/*
Realizzare un programma in C e Posix sotto Linux che realizzi una
struttura di processi ad albero ternario, tale che ogni processo si
metta in attesa che i suoi figli terminino. Ogni figlio termina dopo
aver atteso per un numero di secondi pari al livello dell'albero al
quale si trova, allo scadere del quale stampa a schermo la stringa
"Concluso! e comunica la genitore la sua terminazione.
*/

void closing() {
	printf("%d (%d) - terminating..\n", getpid(), getppid());
}

int main(int argc, char *argv[]) {
	pid_t pid_1, pid_2, pid_3;
	
	for(int i=2;i<=3;i++) {
		pid_1 = fork();
		
		if(pid_1 > 0) {
			pid_2 = fork();
			
			if(pid_2 > 0) {
				pid_3 = fork();
				
				if(pid_3 == 0) {
					sleep(i);
					closing();
				}
			} else {
				sleep(i);
				closing();
			}
		} else if(pid_1 == 0) {
			sleep(i);
			closing();
		}
	}	

	

	return 0;
}
