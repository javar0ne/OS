#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>

/*
Scrivere un programma che accetta un intero n da riga di comando,
crea n thread e poi aspetta la loro terminazione
	• Ciascun thread aspetta un numero di secondi casuale tra 1 e 10, poi
	 incrementa una variabile globale intera ed infine ne stampa il valore
*/

void* random_sleep(void *arg);

int main(int argc, char *argv[]) {
	if(argc != 2) {
		printf("not the exact number of parameters passed\n");
		exit(-1);
	}

	srand(time(NULL));
	int num = atoi(argv[1]);
	pthread_t threads[num];
	
	for(int i = 0; i < num; i++) {
		pthread_create(&threads[i], NULL, random_sleep, NULL);
	}

	for(int i = 0; i < num; i++) {
		pthread_join(threads[i], NULL);
	}
	
	return 0;
}

void* random_sleep(void *arg) {
	int n = rand() % 11;

	sleep(n);

	printf("%ld (%d) - terminating after waiting %ds..\n", pthread_self(), getpid(), n);
}
