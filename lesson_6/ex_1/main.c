#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

#define PATH_SIZE 100

/*
Creare un link simbolico con il comando ln -s. Scrivere un
programma che selezioni il link nella directory e stampi a video il
nome del file.
*/


int main() {
	DIR *dp;
	struct dirent *drn;
	struct stat buff;
	char cwd[PATH_SIZE];
	char symlink_path[PATH_SIZE];

	getcwd(cwd, PATH_SIZE);

	strcpy(symlink_path, cwd);
	strcat(symlink_path, "/symlink");
	
	symlink("/tmp", symlink_path);

	if((dp = opendir(cwd)) == NULL) {
		printf("error while opening folder!\n");
		exit(-1);
	}

	while((drn=readdir(dp)) != NULL) {
		if(lstat(drn->d_name, &buff) < 0) {
			printf("error while retrieving stat for `%s`", drn->d_name);	
		}

		if(S_ISLNK(buff.st_mode)) printf("found link `%s`\n", drn->d_name);
		else printf("`%s` not a link\n", drn->d_name);
	}
	
	closedir(dp);
	exit(0);
}
