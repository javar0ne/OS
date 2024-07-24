#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<limits.h>

#define PATH_SIZE 100

/*
Scrivere un programma in C e Posix sotto Linux che stampa in
output il nome del link simbolico presente nella directory corrente
che si riferisce al file regolare di taglia più grande
*/

int main() {
	DIR *dp;
	struct dirent *drn;
	struct stat buff;
	char cwd[PATH_SIZE];
	char biggest_file_name[256];
	int biggest_file_size = INT_MIN;
	

	getcwd(cwd, PATH_SIZE);	
	
	printf("current folder `%s`\n", cwd);

	if((dp = opendir(cwd)) == NULL) {
		printf("error while opening folder `%s`", cwd);
		exit(-1);
	}

	while((drn = readdir(dp)) != NULL) {
		lstat(drn->d_name, &buff);

		if(S_ISLNK(buff.st_mode)) {	
			stat(drn->d_name, &buff);	
			
			if(buff.st_size > biggest_file_size) {
				biggest_file_size = buff.st_size;
				strcpy(biggest_file_name, drn->d_name);
			}
				
			printf("link name `%s` with size `%ld`\n", drn->d_name, buff.st_size);
		}
	}

	closedir(dp);

	printf("biggest regulare file linked is the file `%s` with size `%d`\n", biggest_file_name, biggest_file_size);
	

	return 0;
}
