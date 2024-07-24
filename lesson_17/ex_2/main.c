#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<fcntl.h>
#include<unistd.h>

/*
Scrivere un programma che prende in input un intero n, il nome di
un file di testo ed un carattere x
	• Il programma ha il compito di contare le occorrenze
	 del carattere x nel file di testo
	• Il programma esegue tale compito creando n thread, ognuno dei
	 quali esamina una porzione diversa del file di testo
	• ad esempio, se il file è lungo 1000 bytes ed n=4, il primo thread esa
	 minerà i primi 250 bytes, il secondo thread esaminerà i 250 bytes successi
	 vi, e così via
*/

void* read_chunk(void *arg);

int fd;
int occ = 0;
char x;

int main(int argc, char *argv[]) {
	if(argc != 4) {
		printf("parameters required do not match the provided ones, terminating..\n");
		exit(-1);
	}
	
	pthread_t *threads;
	int n = atoi(argv[1]);
	char *file_name = argv[2];
	int bytes_per_file;

	x = argv[3][0];

	printf("n: %d\n", n);
	printf("file name: %s\n", file_name);
	printf("x: %c\n", x);
	
	threads = (pthread_t *) malloc(sizeof(pthread_t) * n);
	
	fd = open(file_name, O_RDONLY);
	bytes_per_file = lseek(fd, 0, SEEK_END) / n;
	lseek(fd, 0, SEEK_SET);

	
	for(int i=0; i < n; i++) {
		pthread_create(&threads[i], NULL, read_chunk, &bytes_per_file);
	}
	
	for(int i=0; i < n; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("`%c` occorre `%d` volte\n", x, occ);

	return 0;
}

void* read_chunk(void *arg) {
	int *buf_size = (int *) arg;
	char *buf;
	buf = (char *) malloc(sizeof(char) * (*buf_size + 1));

	read(fd, buf, *buf_size);
	
	for(int i=0; i < *buf_size; i++) {
		if(buf[i] == x) occ++;		
	}
}
