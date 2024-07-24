#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>

int main() {
	struct stat * buff;

	stat("/etc", buff);
	
	printf("%d\n", buff->st_gid);
	
	if(S_ISDIR(buff->st_mode)) {
		printf("is a folder!\n");
	} else if (S_ISREG(buff->st_mode)) {
		printf("is a regular file!\n");
	}
	

	return 0;
}
