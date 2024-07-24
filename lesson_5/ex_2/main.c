#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

/*
Modificare l'esercizio 1 in modo che prenda l'input dal file “testfile” e scriva l'output nel file “outputfile”
• Utilizzare le funzioni per la duplicazione dei file descriptor
• TUTTE LE READ SU STANDARD INPUT
• TUTTE LE WRITE SU STANDARD OUTPUT
*/

int main() {
	int in_fd = open("testfile", O_RDONLY);
	int out_fd = open("outputfile", O_CREAT | O_WRONLY);

	char sum_c[100];
	char num[2]; 
	int num1, num2;	
	while(1) {
		int sum;
		int bytes_read;

		bytes_read = read(in_fd, &num, 2);
		
		if(num[0] == '-' && num[1] == '1') break;		

		num[bytes_read] = '\0';
		num1 = num[0] - '0'; 
		
		read(in_fd, &num, 2);
		num2 = num[0] - '0';	

		sum = num1 + num2;
		
		snprintf(sum_c, 100, "La somma di %d e %d e': %d\n", num1, num2, sum);

		write(STDOUT_FILENO, sum_c, 100);
	}
	return 0;
}
