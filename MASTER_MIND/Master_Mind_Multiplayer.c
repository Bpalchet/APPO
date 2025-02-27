#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int ft_giocatori(void)
{
    int giocatori = 0;
    
    while (giocatori != 1 && giocatori != 2)
    {
        printf("\nQuanti giocatori [1 o 2]? ");
        // Controlla se l'input è valido
        if (scanf("%d", &giocatori) != 1)
        {
            printf("\nErrore: devi inserire un numero!");
            // Pulisce il buffer di input
            while (getchar() != '\n');
                giocatori = 0; // Reset della variabile per continuare il loop
        }
        else if (giocatori != 1 && giocatori != 2)
        {
            printf("\nDigita solo 1 o 2 per favore");
            giocatori = 0; // Reset della variabile per continuare il loop
        }
    }
    return (giocatori);
}

int *ft_indovina (int *buffer, int *result, int conta, int num)
{
    char input[num + 1]; //la stringa di input dei numeri da indovinare
    int guess[num]; // l'array di numeri da indovinare
    int check[num]; // l'array flag della posizione con numero giusto
    int i = 0;
    int cont = 0;
    int j = 0;    //contatore dei numeri giusti nel posto giusto
    int k = 0;    //contatore numeri giusti nel posto sbagliato
    
    memset(check, 0, sizeof(check));
    i = 0;
    printf("\nInserisci %i numeri tra 0 e 9 e premi [ENTER]:\n", num);
    scanf("%s", input);
    if (strlen(input) != num)
    {
        printf("Errore: Devi inserire esattamente %d cifre.\n", num);
        return (result);
    }
    // Trasforma ogni carattere in un numero intero usando while
    while (i < num)
    {
        if (input[i] >= '0' && input[i] <= '9') // Verifica che sia una cifra
            guess[i] = input[i] - '0';          // Converte il carattere in numero
        else
        {
            printf("Errore: Inserisci solo cifre tra 0 e 9.\n");
            return result;
        }
        i++;
    }
    i = 0;
    // verifica quanti numeri sono nel posto giusto    
    while (i < num)
    {
        if (guess[i] == buffer[i])
        {
            j++;
            check[i] = 1;
        }
        i++;
    }
    result[0] = j;
    i = 0;
        // verifica quanti numeri sono nel posto sbagliato
    while (i < num)
    {
        if (guess[i] != buffer[i])
        {
            while (cont < num)
            {
                if (i != cont)
                {
                    if (guess[i] == buffer[cont] && check[cont] == 0)
                    {
                        k++;
                        check[cont] = 1;
                        break;
                    }
                }
                cont++;
            }
        }
        i++;
        cont = 0;
    }
    result[1] = k;
    i = 0;
    printf("TURNO %i)\t ", conta);
    while(i < num)
            {
                printf("%i ", guess[i]);
                i++;
            }
    printf("---> ");
    return(result);
}

int main(void)
{
    int *buffer;
    int *result;
    int *punteggio;
    char players [2][20];
    char playagain;
    int conta;
    int num;
    int i;
    int k;
    int giocatori;

    do {
    conta = 0;
    num = 0;
    i = 0;
    k = 0;
    result = (int *) malloc(2 * sizeof(int));
    punteggio = (int *) calloc(2, sizeof(int));
    giocatori = ft_giocatori(); 
    while (i < giocatori)
    {
        printf("\nNome giocatore %d? ", i + 1);
        scanf("%s", &players[i]);
        i++;
    }
    printf("\nQuanti numeri vuoi indovinare? ");
    scanf("%d", &num); // Definisce il numero di caratteri da indovinare   
    buffer = (int *)malloc(num * sizeof(int));
    srand(time(NULL));
    i = 0;
    while (i < num)
    {
        buffer[i] = rand() % 10;
        i++;
    }
    i = 0;
    if (giocatori == 1)
    {
        while (result[0] != num)
        {
            conta++;
            ft_indovina(buffer, result, conta, num);
            if ((result[0] != num))
                printf("%i-%i", result[0], result[1]);
            else if (result[0] == num)
            {
                i = 0;
                printf("Bravo %s, il numero da indovinare era: ", players[0]);
                while(i < num)
                {
                    printf("%i ", buffer[i]);
                    i++;
                }
                printf("\nHai indovinato al tentativo nr. %i", conta);
            }
        }
    }
    else if (giocatori == 2)
    {
        while (result[0] != num)
        {
            if (k == 0)
                conta++;
            printf ("\nTocca a %s - Punteggio: %d", players[k], punteggio[k]);
            ft_indovina(buffer, result, conta, num);
            if ((result[0] != num))
            {
                printf("%i-%i", result[0], result[1]);
                punteggio[k] += (result[0] * 10) + (result[1] * 5);
                printf("\n%s adesso il tuo punteggio e': %d\n", players[k], punteggio[k]);
                if (k == 0)
                    k = 1;
                else if (k == 1)
                    k = 0;
            }
            else if (result[0] == num)
            {
                i = 0;
                printf("Bravo %s, il numero da indovinare era: ", players[k]);
                while(i < num)
                {
                    printf("%i ", buffer[i]);
                    i++;
                }
                printf("\nHai indovinato al tentativo nr. %i\n", conta);
                printf("Punteggio finale:\n");
                punteggio[k] += 30;
                printf("%s punti %d\n", players[0], punteggio[0]);
                printf("%s punti %d\n", players[1], punteggio[1]);
                if (punteggio[0] > punteggio[1])
                    printf("Bravo %s, hai vinto!\n", players[0]);
                else if (punteggio[0] < punteggio[1])
                    printf("Bravo %s, hai vinto!\n", players[1]);
                else if (punteggio[0] == punteggio[1])
                    printf("Avete pareggiato\n");
            }
        }
    }
    free(buffer);
    free(punteggio);
    free(result);
    printf("\nVuoi giocare ancora? (s/n): ");
    while (getchar() != '\n'); // Svuota il buffer per evitare problemi di input
    scanf("%c", &playagain);
    while (playagain != 's' && playagain != 'n')
    {
        printf("Input non valido. Vuoi giocare ancora? (s/n): ");
        while (getchar() != '\n'); // Svuota il buffer
        scanf("%c", &playagain);
    }
    } while (playagain == 's'); // Ripeti il gioco se l'utente inserisce 's'
    printf("\nGrazie per aver giocato! Alla prossima.\n");
    printf("\nPremi Invio per chiudere...");
    while (getchar() != '\n'); // Svuota il buffer
        getchar(); // Attende un input dall'utente
    return(0);
}