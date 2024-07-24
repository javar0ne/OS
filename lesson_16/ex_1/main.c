#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>

/*
Scrivere un programma che, presa una directory da riga di comando,
provveda a scorrerla allo scopo di stampare i nomi di tutti i file regolari
e le loro dimensioni, se questi hanno i diritti di scrittura e lettura per il
proprietario e per gli altri.
*/

int main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *dirp;

	if((dp = opendir(argv[1])) == NULL) {
		printf("can't open directory %s\n", argv[1]);
		exit(-1);
	}

	while((dirp = readdir(dp)) != NULL) {
		struct stat buf;	

		if(strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0) {
			if(stat(dirp->d_name, &buf) < 0) {
				printf("lstat error!\n");

				exit(-1);
			}
		} else {
			/*char path[100];
			strcpy(path, "");
			strcat(path, argv[1]);
			strcat(path,"/");
			strcat(path, dirp->d_name);

			printf("%s\n", path);*/

			if(stat(argv[1], &buf) < 0) {
				printf("lstat error!\n");

				exit(-1);
			}
		}
		
		printf("%d\t", S_ISREG(buf.st_mode));
		printf("%s\n", dirp->d_name);
	}

	closedir(dp);

	exit(0);
}
