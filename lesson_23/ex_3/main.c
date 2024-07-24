#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>

/*
Scrivere un programma in C Posix in ambiente Unix/Linux che
data una directory da riga di comando cerchi tutti i file con un
numero di hard link >1 e ne stampi i nomi e i permessi del
proprietario
*/

int main(int argc, char *argv[]) {
	DIR *dp;
	struct stat buff;
	struct dirent *dir;	
		
	if(argc != 2) {
		printf("incorrect number of parameters! terminating..\n");
		exit(-1);
	}	

	printf("checking folder %s\n\n", argv[1]);

	if((dp = opendir(argv[1])) == NULL) {
		printf("error while opening folder `%s`! terminating..\n", argv[1]);
	}

	while((dir = readdir(dp)) != NULL) {
		stat(dir->d_name, &buff);
		
		if(buff.st_nlink > 1) {
			printf("file name: %s\n", dir->d_name);

			printf("owner permission: ");
			printf( buff.st_mode & S_IRUSR ? "r" : "-");
			printf(buff.st_mode & S_IWUSR ? "w" : "-");
			printf(buff.st_mode & S_IXUSR ? "x" : "-");
			printf("\n\n");
		}
	}

	

	return 0;
}
