#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	int glob = 3;
	int pid = 10;

	if (fork() == 0) {
		glob -= 2;
	} else {
		glob--;
		
		if (!fork()) {
			if (pid > 0) {
				pid = fork();
				glob--;
			}
		}
	}
	printf("Valore di glob=%d\n", glob);

}
