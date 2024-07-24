#include<stdio.h>
#include<unistd.h>

#define READ 0
#define WRITE 1

/*
ercizio: scrivere un programma che esegua il comando di shell
“ls| sort| grep <pat>” con tre processi distinti
*/

int main(int argc, char *argv[]) {
	int fd1[2], fd2[2];

	pid_t pid_a, pid_b;
	
	pipe(fd1);
	pipe(fd2);

	pid_a = fork();

	if(pid_a == 0) {
		close(fd1[WRITE]);
		dup2(fd1[READ], 0);
		close(fd1[READ]);

		close(fd2[READ]);
		dup2(fd2[WRITE], 1);
		close(fd2[WRITE]);

		execlp("sort", "sort", NULL);		
	} else {
		pid_b = fork();

		if(pid_b == 0) {
			close(fd1[READ]);
			close(fd1[WRITE]);

			close(fd2[WRITE]);		
			dup2(fd2[READ], 0);
			close(fd1[READ]);

			execlp("grep", "grep", argv[1], NULL);
		} else {
			close(fd2[READ]);
			close(fd2[WRITE]);

			close(fd1[READ]);		
			dup2(fd1[WRITE], 1);
			close(fd1[WRITE]);
			
			execlp("ls", "ls", NULL);
		}
	}

	return 0;
}
