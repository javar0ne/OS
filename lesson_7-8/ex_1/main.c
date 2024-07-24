#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

/*
Scrivere un programma che crea uno zombie e poi esegue il
comando ps per verificare che il processo è uno zombie
*/

int main(int argc, char *argv[]) {
	execl("zombie", "zombie", NULL);
	
	execlp("/bin/ps", "ps", "aux", NULL);

	return 0;
}
