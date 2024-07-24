#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>

/*
 Si realizzi un programma C e Posix in ambiente Linux che, impiegando
la libreria Pthread, generi tre thread
	• I primi due thread sommano 1000 numeri generati casualmente ed ogni
	 volta incrementano un contatore
	• Il terzo thread attende che il contatore incrementato dai due thread
	 raggiunga un valore limite fornito da riga di comando, notifica l’avvenuta
	 condizione e termina
	• Utilizzare le variabili condizione
*/

int done_sum = 1;
int counter = 0;
int sum = 0;

void* calc_sum(void *arg);
void* check_condition(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int main(int argc, char *argv[]) {
	pthread_t threads[3];
	
	srand(time(NULL));

	pthread_create(threads, NULL, calc_sum, NULL);
	pthread_create(threads+1, NULL, calc_sum, NULL);
	pthread_create(threads+2, NULL, check_condition, NULL);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);

	return 0;
}

void* calc_sum(void* arg) {
	while(1) {
		pthread_mutex_lock(&mutex);

		while(done_sum == 0) pthread_cond_wait(&condition, &mutex);

		if(counter == 1000) {
			pthread_mutex_unlock(&mutex);
			break;
		}

		done_sum = 0;

		int num = rand() % 1001;
		sum += num;
		counter++;

		printf("generated `%d`, sum `%d`, counter `%d`\n", num, sum, counter);

		done_sum = 1;

		pthread_cond_signal(&condition);

		pthread_mutex_unlock(&mutex);
	}
}

void* check_condition(void* arg) {
	pthread_mutex_lock(&mutex);

	while(counter != 1000) pthread_cond_wait(&condition, &mutex);

	printf("Completed!\n");

	pthread_cond_signal(&condition);
	pthread_mutex_unlock(&mutex);
}
