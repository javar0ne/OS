#include<stdio.h>
#include<fcntl.h>
#include <unistd.h>

int main() {
	struct stat buff;

	if(access("/opt", X_OK)) {
		printf("can access!\n");
	}
	
	return 0;
}
