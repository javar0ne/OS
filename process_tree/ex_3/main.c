#include<stdio.h>
#include<unistd.h>

int glob=5;
int pid=0;

int main() {
	int i=0;
	for (i=1;i<3;i++) {
		pid=fork();

		if (pid==0) {
			glob=glob*2;
			sleep(i+1);
		}

		glob=glob+1;
	}
	printf("Valore di glob=%d\n",glob);

	return 0;
}
