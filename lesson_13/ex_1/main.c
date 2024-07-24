#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include "config.h"

/*
Scrivere un programma che gestisce il comportamento di un
padre e due figli (fpari e fdispari); il padre legge numeri positivi da
tastiera fino a che non arriva un numero negativo
• se il numero è pari lo manda al figlio pari
• altrimenti lo manda al figlio dispari
• I figli effettuano le somme parziali, quindi rimandano le somme al
padre che calcola la somma totale e la stampa a video.
*/

int main(int argc, char *argv[]) {
	int fd_pari, fd_somma_pari, somma_pari=0;
	int fd_dispari, fd_somma_dispari, somma_dispari=0;
	int somma = 0, num;
	char buff[BUF_SIZE];

	mkfifo(FIFO_EVEN, 0777);	
	mkfifo(FIFO_ODD, 0777);
	mkfifo(FIFO_EVEN_SUM, 0777);
	mkfifo(FIFO_ODD_SUM, 0777);

	fd_pari = open(FIFO_EVEN, O_WRONLY);
	fd_somma_pari = open(FIFO_EVEN_SUM, O_RDONLY);
	fd_dispari = open(FIFO_ODD, O_WRONLY);	
	fd_somma_dispari = open(FIFO_ODD_SUM, O_RDONLY);
	
	while(1) {
		printf("inserire num:");
		scanf("%d", &num);

		if(num == -1) break;
		
		snprintf(buff, 10, "%d", num);			

		if(num%2==0) {
			write(fd_pari, buff, 10);
			read(fd_somma_pari, buff, 10);

			somma_pari = atoi(buff);
		} else {
			write(fd_dispari, buff, 10);
			read(fd_somma_dispari, buff, 10);
			
			somma_dispari = atoi(buff);
		}
		
	}
	
	printf("somma pari %d - somma dispari %d\n", somma_pari, somma_dispari);
	somma = somma_pari + somma_dispari;

	printf("La somma totale e': %d\n", somma);

	unlink(FIFO_EVEN);
	unlink(FIFO_EVEN_SUM);
	unlink(FIFO_ODD);
	unlink(FIFO_ODD_SUM);
	
	return 0;
}
