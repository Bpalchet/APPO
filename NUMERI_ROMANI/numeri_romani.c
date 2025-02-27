#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

char    *ft_scrivi(int c, char a, char b, char k)
{
    int i = 0;
    int j;
    int ten = c;
    char *buffer1;

    buffer1 = malloc(5 * sizeof(char)); // Alloca memoria dinamica (4 caratteri + '\0')
    if (!buffer1)
        return NULL;
    if (ten < 4)
        while (i != ten)
        {
            buffer1[i] = a;
            i++;
        }
    else if (ten == 4)
    {
        buffer1[i] = a;
        i++;
        buffer1[i] = b;
        i++;
    }
    else if (ten >= 5 && ten < 9)
    {
        buffer1[i] = b;
        i++;
        j = ten - 5;                     
        while (j != 0)
        {
            buffer1[i] = a;
            i++;
            j--;
        }
    }
    else if (ten == 9)
    {
        buffer1[i] = a;
        i++;
        buffer1[i] = k;
        i++;
    }
    buffer1[i] = '\0';
    return(buffer1);
}

char    *ft_converti(int numero)
{
    int u;
    int d;
    int c;
    int m;
    int j;
    char a;
    char b;
    char k;
    int i = 0;
    char *roman;
    char *buffer;

    buffer = malloc(5 * sizeof(char)); // Alloca memoria dinamica (4 caratteri + '\0')
    if (!buffer)
        return NULL;
    roman = malloc(21 * sizeof(char)); // Alloca memoria dinamica (20 caratteri + '\0')
    if (!roman)
        return NULL;
    u = numero % 10;
    d = (numero / 10) % 10;
    c = (numero / 100) % 10;
    m = (numero /1000) % 10;

    if (m != 0)
        while (i != m)
        {
            roman[i] = 'M';
            i++; 
        }
    if (c != 0)
    {
        a = 'C';
        b = 'D';
        k = 'M';
        buffer = ft_scrivi(c, a, b, k);
        j = 0;
        while (buffer[j] != '\0')
        {
            roman[i] = buffer[j];
            j++;
            i++;
        }
    }
    if (d != 0)
    {
        a = 'X';
        b = 'L';
        k = 'C';
        buffer = ft_scrivi(d, a, b, k);
        j = 0;
        while (buffer[j] != '\0')
        {
            roman[i] = buffer[j];
            j++;
            i++;
        }
    }
    if (u != 0)
    {
        a = 'I';
        b = 'V';
        k = 'X';
        buffer = ft_scrivi(u, a, b, k);
        j = 0;
        while (buffer[j] != '\0')
        {
            roman[i] = buffer[j];
            j++;
            i++;
        }
    }
    roman[i] = '\0';
    return (roman);
}

int main(void)
{
    int numero;
    char *roman;
    char othernr;

    do
    {
        printf("Inserisci il numero da convertire (max 9999): ");
        scanf("%d", &numero);
        if (numero > 9999)
        {
            printf ("Numero troppo grande da convertire. Programma abortito");
            return (0);
        }
        printf("Il numero da convertire e': %d\n", numero);
        roman = ft_converti(numero);
        printf("Il numero romano corrispondente e': %s\n", roman);
        printf("\nAltro numero da convertire? (s/n): ");
        while (getchar() != '\n'); // Svuota il buffer per evitare problemi di input
            scanf("%c", &othernr);
        while (othernr != 's' && othernr != 'n')
        {
            printf("Input non valido. Vuoi giocare ancora? (s/n): ");
            while (getchar() != '\n'); // Svuota il buffer
            scanf("%c", &othernr);
        }
    } while (othernr == 's'); // Ripeti il gioco se l'utente inserisce 's'
    printf("\nChiusura programma.\n");
    printf("\nPremi Invio per chiudere...");
    while (getchar() != '\n'); // Svuota il buffer
        getchar(); // Attende un input dall'utente
    return (0);
}