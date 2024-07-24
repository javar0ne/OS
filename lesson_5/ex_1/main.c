#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/*
Scrivere un programma C che:
	• Prende in input coppie di interi utilizzando la system call read
	• Calcola la somma degli interi
	• Stampa a video il risultato utilizzando la write
	• Termina quando il primo input e' -1
	• Assumere che gli interi consistano di una sola cifra
*/

int main() {
	char num[4]; 
	int num1, num2;	
	while(1) {
		char sum_c[4];		
		int sum;
		int bytes_read;

		bytes_read = read(STDIN_FILENO, &num, 4);
		
		if(num[0] == '-' && num[1] == '1') break;		

		num[bytes_read] = '\0';
		num1 = num[0] - '0'; 
		
		read(STDIN_FILENO, &num, 4);
		num2 = num[0] - '0';	

		sum = num1 + num2;
		
		snprintf(sum_c, 99, "%d\n", sum);

		write(STDOUT_FILENO, sum_c, 4);
	}
	return 0;
}
