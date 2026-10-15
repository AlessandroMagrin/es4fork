#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Errore fork");
        exit(1);
    }

    if (pid == 0) {
        // === PROCESSO FIGLIO ===
        int n, i, numeroprimo = 1;

        printf("Inserisci un numero:\n ");
        scanf("%d", &n);

        // Controllo se è primo
        if (n <= 1) numeroprimo = 0;
        //partiamo con i divisori da 2
        //se un divisore è maggiore della radice quadrata del numero allora ce ne sarà uno anche prima
        for (i = 2; i * i <= n; i++) {
            if (n % i == 0)
                numeroprimo = 0;
        }

        // Esce con codice diverso in base alla regola
        if (numeroprimo) {
            exit(1); // Codice 1: Primo
        } else if (n % 2 == 0) {
            exit(2); // Codice 2: Pari (e non primo)
        } else {
            exit(3); // Codice 3: Dispari (e non primo)
        }
    }

    //processo padre
    //wait(&status) aspetta il figlio e ne prende le informazioni dentro la variabile statis
    int status;
    wait(&status);

    // Estrae direttamente il codice di uscita del figlio
    int codice = WEXITSTATUS(status);

    printf("Il figlio è uscito con il codice: %d\n", codice);


    if (codice == 1) {
        printf("Il numero inserito era PRIMO!\n");
    } else if (codice == 2) {
        printf("Il numero inserito era PARI.\n");
    } else if (codice == 3) {
        printf("Il numero inserito era DISPARI.\n");
    }

    return 0;
}