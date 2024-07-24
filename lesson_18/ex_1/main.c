#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

/*
Si realizzi un programma in C e Posix sotto Linux che, utilizzando la
libreria Pthread
• lancia n thread per cercare un elemento in una matrice nxn di caratteri
• Ognuno dei thread cerca l'elemento in una delle righe della matrice
• Non appena un thread ha trovato l'elemento cercato, rende note agli altri
thread le coordinate dell'elemento e tutti i thread terminano (sono
cancellati)
*/

#define N 5

void* find_element(void *args);

struct element_search {
	int *row;
	int row_idx;
	int element;
};

pthread_t threads[N];

int main() {
	int element;
	int matrix[N][N] = {
		{5,1,2,5,8},
		{11,25,8,54,61},
		{9,6,2,0,12},
		{15,41,25,27,3},
		{9,91,71,69,23}		
	};
	
	printf("Insert element to find:");
	scanf("%d", &element);

	for(int i=0;i<N;i++) {
		struct element_search *els = malloc(sizeof(struct element_search));
		els->row = matrix[i];
		els->row_idx = i;
		els->element = element;

		pthread_create(threads+i, NULL, find_element, els);
	}

	for(int i=0;i<N;i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}

void* find_element(void *args) {
	struct element_search *els = (struct element_search*) args;
	int found = 0;

	for(int j=0;j<N;j++) {
		if(*(els->row+j) == els->element) {
			found = 1;
			printf("%lu - %d found in %dx%d!\n", pthread_self(), els->element, els->row_idx, j);
			break;
		}
	}
	
	if(found) {
		for(int j=0;j<N;j++) {
			pthread_cancel(threads[j]);
		}
	}

	pthread_exit(NULL);
}

