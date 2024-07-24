#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>

/*
Scrivere un programma in C Posix in ambiente Unix/Linux che
esplori una directory specificata dall'utente da riga di comando
per trovare e stampare i nomi di tutti i file regolari che abbiano i
permessi di lettura e scrittura per il proprietario ed il gruppo
*/

char check_file(struct stat buff);

int main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *dir;
	struct stat buff;

	if(argc != 2) {
		printf("invalid number of parameters provided! terminating..\n");
		exit(-1);
	}	

	printf("path provided `%s`\n", argv[1]);

	if((dp = opendir(argv[1])) == NULL) {
		printf("error while opening folder `%s`! terminating..\n", argv[1]);
		exit(-1);
	}

	while((dir = readdir(dp)) != NULL) {
		stat(dir->d_name, &buff);

		if(check_file(buff)) {
			printf("%s\n", dir->d_name);
			//check_file(buff);
		}
	}

	return 0;
}

char check_file(struct stat buff) {
	/*printf("%d\n", S_ISREG(buff.st_mode));
	printf("%d\n", buff.st_mode & S_IRUSR);
	printf("%d\n", buff.st_mode & S_IWUSR);
	printf("%d\n", buff.st_mode & S_IRGRP);
	printf("%d\n\n", buff.st_mode & S_IWGRP);*/
	
	return S_ISREG(buff.st_mode) &&
		buff.st_mode & S_IRUSR &&
		buff.st_mode & S_IWUSR &&
		buff.st_mode & S_IRGRP &&
		buff.st_mode & S_IWGRP;
}
