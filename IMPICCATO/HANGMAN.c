#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

char    *ft_suggerimento(char *title)
{
    if (title[0] == 'F')
        return ("Film");
    else if (title[0] == 'P')
        return ("Proverbio o modo di dire");
    else if (title[0] == 'L')
        return ("Libro e autore");
    else if (title[0] == 'S')
        return ("Avvenimento storico");
    else if (title[0] == 'C')
        return ("Canzone e interprete");
    else if (title[0] == 'I')
        return ("Indovinello");
    else if (title[0] == 'B')
        return ("Barzellette e freddure");
}

int ft_punti(int punti)
{
    char letter;
    int check;

    if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U')
        punti--;
    if (check == 0)
        punti--;
    return (punti);
}

char    *touppercase (char *str)
{
    while (*str)
    {
        *str = toupper((unsigned char) *str);
        str++;
    }
    return (str);
}

char    *ft_hangman (char *hidden_title, char *title)
{
    char    letter;
    char    frase[80];
    int cont = 0;
    int check = 0;
    size_t len = 0;
    
    while (1)
    {
        printf("\nDammi una lettera MAIUSCOLA o premi '>' ed INVIO per indovinare ---> ");
        if (scanf(" %c", &letter) != 1)
        {
            printf("\nErrore: devi inserire una lettera o '>'");
            // Pulisce il buffer di input
            while (getchar() != '\n');
        }
        else if (!(isupper(letter) || letter == '>'))
        {
            printf("\nDigita solo lettere maiuscole o premi '>', per favore");
            while (getchar() != '\n');
        }
        else
            break;
    }
    if (letter == '>')
    {
        printf("\nProva ad indovinare la frase ---> ");
        getchar(); // Consuma il carattere di newline rimasto nel buffer
        fgets(frase, sizeof(frase), stdin);
        len = strlen(frase);
        if (len > 0 && frase[len - 1] == '\n')
            frase[len - 1] = '\0';
        if (strcmp(frase, title) == 0)
        {
            printf("\nComplimenti! Hai indovinato la frase!!!\n");
            strcpy(hidden_title, title); // Copia la frase completa in hidden_title
            return (hidden_title);
        }
        else 
            printf("\nSpiacente, la frase e' sbagliata.\n");
    }
    while (hidden_title[cont] != '\0')
    {
        if (title[cont] == letter)
        {
            hidden_title[cont] = letter;
            check = 1;
        }
        cont++;
    }
    /*if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'O' || letter == 'U')
        punti--;
    if (check == 0)
        punti--;*/
    return (hidden_title);
}

char    *ft_buffer(int fd, size_t fileSize)
{
    char    *buffer;
    ssize_t bytesRead;
    
    buffer = (char *)malloc(fileSize + 1); // +1 per il terminatore
    if (buffer == NULL) {
        printf("Errore nell'allocazione della memoria.\n");
        close(fd);
        return (NULL);
    }
    bytesRead = read(fd, buffer, fileSize);
    if (bytesRead == -1)
    {
        printf("Errore durante la lettura del file: %s\n", strerror(errno));
        free(buffer);
        close(fd);
        return (NULL);
    }
    buffer[bytesRead] = '\0';
    return (buffer);
}

char *ft_hidden_title(char *title1)
{
    int i = 0;
    char *h_title;
    size_t len = 0;

    len = strlen(title1);
    h_title = (char*)malloc((len + 1) * sizeof(char));
    if (h_title == NULL)
    {
        printf("Errore: Allocazione della memoria fallita.\n");
        return (NULL);
    }
    //h_title[0] = ' ';
    while (i < len)
    {
        if ((title1[i] >= 'A' && title1[i] <= 'Z') || (title1[i] >= 'a' && title1[i] <= 'z'))
            h_title[i] = '-';
        else
            h_title[i] = title1[i];
        i++;
    }
    h_title[i] = '\0';
    return (h_title);
}

char *ft_random_title(char **titoli, int num_titoli)
{
    int r = 0;

    srand(time(NULL));
    r = rand() % num_titoli;
    return (strdup (titoli[r]));
}

int main(void)
{
    int fd;
    int num_titoli = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int punti = 5;
    char *buffer;
    char **titoli;
    char *title;
    char title1[80];
    char    *suggerimento;
    char *hidden_title;
    char playagain;
    size_t fileSize;
    struct stat fileStat;

    do {
    fd = open("TITLES.TXT", O_RDONLY);
    if (fd == -1)
    {
        printf("Errore nell'apertura del file in lettura: %s\n", strerror(errno));
        return (1);
    }
    if (fstat(fd, &fileStat) == -1)
    {
        printf("Errore nel determinare la dimensione del file.\n");
        close(fd);
        return (1);
    }
    fileSize = fileStat.st_size;
    buffer = ft_buffer(fd, fileSize);
    close(fd);
    while (buffer[j] != '\0')
    {
        if (buffer[j] == '\n')
            num_titoli++;
        j++;
    }
    //printf("I Titoli disponibili sono %d\n\n", num_titoli);
    titoli = (char **)malloc(num_titoli * sizeof(char *));
    if (titoli == NULL)
    {
        printf("Errore: Allocazione della memoria per i titoli fallita.\n");
        free(buffer);
        return 1;
    }
    // Popola l'array dei titoli
    i = 0;
    j = 0;
    while (i < num_titoli)
    {
        titoli[i] = (char *)malloc(80 * sizeof(char)); // Dimensione fissa per ogni titolo
        if (titoli[i] == NULL)
        {
            printf("Errore: Allocazione della memoria per il titolo %d.\n", i);
            while (i > 0)
                free(titoli[--i]);
            free(titoli);
            free(buffer);
            return (1);
        }
        k = 0;
        while (buffer[j] != '\n' && buffer[j] != '\0')
        {
            titoli[i][k] = buffer[j];
            j++;
            k++;
        }
        titoli[i][k] = '\0'; // Terminatore della stringa
        j++; // Salta il carattere '\n'
        i++;
    }
    free(buffer);
    i = 0;
    while (i < num_titoli)
    {
        touppercase(titoli[i]);
        //printf("Titolo %d : %s\n", i + 1, titoli[i]);
        i++;
    }
    title = ft_random_title(titoli, num_titoli);
    //printf("Titolo scelto = %s\n", title);
    strcpy(title1, title + 1);
    //printf("Titolo scelto senza iniziale = %s\n", title1);
    //printf ("Titolo selezionato : %s\n", title);
    hidden_title = ft_hidden_title(title1);
    suggerimento = ft_suggerimento(title);
    printf("Ecco la frase nascosta da indovinare: %s", hidden_title);
    printf("   (Suggerimento: %s)\n", suggerimento);
    printf("I punti a tua disposizione sono %d", punti); 
    while ((strcmp(hidden_title, title) != 0))
    {
        if (punti > 0)
        {
            hidden_title = ft_hangman(hidden_title, title1);
            punti = ft_punti(punti);
            if (strcmp(hidden_title, title1) == 0)
            {
                printf("Indovinato! La frase nascosta era %s", hidden_title);
                break;
            }
            printf("La frase nascosta : %s\n", hidden_title);
            printf("Punti rimanenti: %d", punti);
        }
        else if (punti <= 0)
        {
            printf("\nMi dispiace, punti esauriti. Il gioco finisce qui.\n");
            printf("La frase nascosta era: %s", title1);
            break;       
        }
    }
    i = 0;
    while (i < num_titoli)
    {
        free(titoli[i]); // Libera ogni stringa
        i++;
    }
    free(titoli); // Libera l'array di puntatori
    free(title);
    free(hidden_title);
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
    return (0);
}