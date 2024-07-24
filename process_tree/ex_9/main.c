#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	int glob = 2;
	pid_t pid = 1;

	fork();

	pid=fork();

	if(pid) {
		while(glob){
			glob--;
			pid=fork();
		}
	} else if(fork()) {
		glob=10;
	}
		
	printf("Valore di glob=%d\n", glob);
}
