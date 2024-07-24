#include<stdio.h>
#include<unistd.h>

/*
ercizio: scrivere un programma che esegua il comando di shell 
“ls- R | grep <pat>” dove <pat> è un pattern inserito dall’utente
*/

int main(int argc, char *argv[]) {
	int fd[2];
	pid_t pid;

	pipe(fd);

	pid = fork();

	if(pid == 0) {
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);		

		execlp("grep", "grep", argv[1], NULL);
	
	} else {
		close(fd[0]);
		dup2(fd[1], 1);		
		close(fd[1]);
		
		execlp("ls", "ls", "-R", NULL);
	}

	return 0;
}
