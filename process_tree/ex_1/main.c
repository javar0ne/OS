#include<stdio.h>
#include<unistd.h>

int glob=20;
int pid=0;
int main() {
	int i=0;
	for (i=2;i<4;i++) {
		printf("%d\n", i);
		pid=fork();
		if (pid==0) {
			glob=glob*2;
			sleep(i+1);
		}
		glob=glob-1;
		printf("Valore di glob=%d\n",glob);
	}
}
