#include<stdio.h>
#include<unistd.h>

int main() {
	int glob = 6;
	pid_t pid = 0;
	
	while (!pid) {
		if (!fork())
			glob -= 3;
		else {
			glob--;
			if ((pid=fork()) == 0){
				pid =1;
				fork();
				glob--;
			}
		}

		if(!glob)
			pid=10;
	}

	printf("Valore di glob=%d\n", glob);

}
