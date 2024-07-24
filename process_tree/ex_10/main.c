#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	int glob = 5;
	pid_t pid = 1;
	int counter = 2;
	while (counter > 0) {
		if (fork()) {
			glob -= 3;
		} else {
			glob--;
			if (fork() == 0) {
				if (pid > 0) {
					pid = fork();
					glob--;
				}
			}	
		}
		counter--;
	}
	printf("Valore di glob=%d\n", glob);

}
