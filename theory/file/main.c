#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define BUF_SIZE 256

int main() {
	int fd = open("input.txt", O_RDWR | O_APPEND);
	char buff[BUF_SIZE];

	if(fd != -1) printf("opened!\n");	
	else printf("not opened!\n");	

	//int curr_cursor = lseek(fd, 10, SEEK_SET);
	
	read(fd, buff, BUF_SIZE);	
	printf("%s", buff);

	int dup_fd = dup(fd);

	int written = write(dup_fd, "di minchia!!", 12);
	if(written == -1) printf("error while writing!\n");
	else if(written < 12) printf("not all bytes written!\n");
	else printf("all written!!");

	close(dup_fd);
	close(fd);

	return 0;
}
