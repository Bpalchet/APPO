#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *ft_indovina (int *buffer, int *result, int conta)
{
    char input[4]; //la stringa di input dei numeri da indovinare
    int guess[3]; // l'array di numeri da indovinare
    int check[3] = {0, 0, 0};
    int i = 0;
    int cont = 0;
    int flag = 0; //flag che verifica la presenza di numeri nel posto sbagliato
    int j = 0;    //cont. dei numeri giusti nel posto giusto
    int k = 0;    //cont. numeri giusti nel posto sbagliato
    
    printf("\nInserisci tre numeri tra 0 e 9 e premi [ENTER]:\n");
    scanf("%3s", input); // Legge una stringa di massimo 3 caratteri

    // Trasforma ogni carattere in un numero intero usando while
    while (i < 3)
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
    while (i < 3)
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
    while (i < 3)
    {
        if (guess[i] != buffer[i])
        {
            while (cont < 3)
            {
                if (i != cont)
                {
                    if (guess[i] == buffer[cont] && check[cont] == 0)
                    {
                        flag++;
                        break;
                    }
                }
                cont++;
            }
            if (flag > 0)
            {
                k++;
                flag = 0;                
            }
        }
        i++;
        cont = 0;
    }
    result[1] = k;
    printf("%i)\t%i, %i, %i ---> ", conta, guess[0], guess[1], guess[2]);
    return(result);
}

int main(void)
{
    int buffer[3];
    int result[2] = {0, 0};

    int conta = 0;
    int i = 0;

    srand(time(NULL));
    while (i < 3)
    {
        buffer[i] = rand() % 10;
        i++;
    }
    //printf("Ecco la terzina da indovinare: %i, %i, %i\n", buffer[0], buffer[1], buffer[2]);
    while (result[0] != 3)
    {
        conta++;
        ft_indovina(buffer, result, conta);
        if ((result[0] != 3))
            printf("%i-%i", result[0], result[1]);
        else if (result[0] == 3)
        {
            printf("Bravo, la terzina da indovinare era: %i, %i, %i\n", buffer[0], buffer[1], buffer[2]);
            printf("\nHai indovinato al tentativo nr. %i", conta);
            return (0);
        }
    }
    return(0);
}