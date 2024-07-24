#include<stdio.h>
#include<unistd.h>

int main() {
	int glob=6;
	int pid=0;
	
	fork();
	
	for (int i=1; i<2; i++) {
		if(!fork()){
			glob=glob*2;
			pid=1;
		}
		
		if(pid)
			fork();
		
		glob=glob-1;
	}
	
	printf("Valore di glob=%d\n",glob);

	return 0;
}
