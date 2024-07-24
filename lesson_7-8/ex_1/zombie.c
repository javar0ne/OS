#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
	if(fork()==0) {
		sleep(10);
	} 

	return 0;
}
