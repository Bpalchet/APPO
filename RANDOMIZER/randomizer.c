/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpalchet <bpalchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:26:39 by bpalchet          #+#    #+#             */
/*   Updated: 2025/02/27 16:10:16 by bpalchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>

void clear_input_buffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
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

void ft_savefile(char *filename, int *array, size_t n)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }
    if (fwrite(&n, sizeof(size_t), 1, file) != 1) //salva dimensione array
    {
        perror("Errore nella scrittura della dimensione");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    if (fwrite(array, sizeof(int), n, file) != n)
    {
        perror("Errore nella scrittura dell'array");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

int *ft_loadfile(char *filename, size_t *n)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Errore nell'apertura del file");
        return NULL; // Ritorna NULL se il file non esiste
    }
    if (fread(n, sizeof(size_t), 1, file) != 1)
    {
        perror("Errore nella lettura della dimensione");
        fclose(file);
        return (NULL);
    }
    int *array = malloc(*n * sizeof(int));
    if (!array)
    {
        perror("Errore di allocazione memoria");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    if (fread(array, sizeof(int), *n, file) != *n)
    {
        perror("Errore nella lettura dell'array");
        free(array);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    printf("\n");
    fclose(file);
    return (array);
}

void ft_print_titoli(char **titoli, int *array, int num_titoli)
{
    int i = 0;
    
    while (i < num_titoli)
    {
        touppercase(titoli[i]);
        if (array[i] == 0)
        {
            printf("%s\n", titoli[i]);
            i++;
        }
        else
        {
            write(1, "\n", 1);
            i++;
        }
    }
    write(1, "---EOF---", 9);
    write(1, "\n\n", 2);
    return;
}

size_t ft_openfile(int fd)
{
    size_t fileSize;
    struct stat fileStat;
    
    if (fd == -1)
    {
        printf("Errore nell'apertura del file in lettura.\n");
        return (1);
    }
    if (fstat(fd, &fileStat) == -1)
    {
        printf("Errore nel determinare la dimensione del file.\n");
        close(fd);
        return (1);
    }
    fileSize = fileStat.st_size;
    return (fileSize);
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
        printf("Errore durante la lettura del file.\n");
        free(buffer);
        close(fd);
        return (NULL);
    }
    buffer[bytesRead] = '\0';
    return (buffer);
}

int main (void)
{
    char filename[100], file[100], playagain, save, load;
	int *array;
    int fd, r = 0, j = 0, k = 0;
    size_t num_titoli = 0, i = 0, cont = 0, fileSize;
    char *buffer;
    char **titoli;
	
    printf("Inserisci il nome del file della materia da ripassare = ");
    scanf(" %s", file);
    fd = open(file, O_RDONLY);
	fileSize = ft_openfile(fd);
    buffer = ft_buffer(fd, fileSize);
    close(fd);
    while (buffer[j] != '\0')
    {
        if (buffer[j] == '\n')
            num_titoli++;
        j++;
    }
    printf("I Titoli disponibili tratti dal file '%s' sono %ld:\n", file, num_titoli);
    printf("\nVuoi partire da un salvataggio esistente? (s/n): ");
    clear_input_buffer();
    scanf("%c", &load);
    while (load != 's' && load != 'n')
    {
        printf("Input non valido! Vuoi aprire il file salvato? (s/n): ");
        clear_input_buffer();
        scanf("%c", &load);
    }
    if (load == 's')
    {
        printf("\nDammi il nome del file da aprire o premi <ENTER> per default 'save.sav'?: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL)
        {
            perror("Errore nella lettura dell'input");
            return(0);
        }
        filename[strcspn(filename, "\n")] = '\0'; // Rimuove il '\n' finale se presente
        if (filename[0] == '\0')
            strcpy(filename, "save.sav");
        array = ft_loadfile(filename, &num_titoli);
        if (array == NULL)
        {
            printf("Errore nel caricamento del file salvato.\n");
            return (1);
        }
        while (i < num_titoli)
            {
                if (array[i] == 1)
                    cont++;
                i++;
            }
    }
    else if (load == 'n')
	    array = (int *)calloc(num_titoli, sizeof(int));
    titoli = (char **)malloc(num_titoli * sizeof(char *));
    if (titoli == NULL)
    {
        printf("Errore: Allocazione della memoria per i titoli fallita.\n");
        free(buffer);
        return (1);
    }
    // Popola l'array dei titoli
    i = 0;
    j = 0;
    while (i < num_titoli)
    {
        titoli[i] = (char *)malloc(100 * sizeof(char)); // Dimensione fissa per ogni titolo
        if (titoli[i] == NULL)
        {
            printf("Errore: Allocazione della memoria per il titolo %ld.\n", i);
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
    system("clear"); //sostituire con cls per Windows
    do
	{
		srand(time(NULL));
    	while (1)
		{
            r = rand() % num_titoli;
            printf("CAPITOLI DA RIPETERE:\n\n");
            ft_print_titoli(titoli, array, num_titoli);
			if (array[r] == 1)
                system("clear"); //sostituire con cls per Windows
            else if (array[r] == 0 && cont < num_titoli)
			{
				array[r] = 1;
                printf("Capitolo da ripetere adesso =\t%s\n\n", titoli[r]);
				printf("Totale Capitoli = %ld\t", num_titoli);
				printf("Capitoli Ripetuti = %ld\t", cont);
				printf("Ancora da ripetere = %ld:\n", num_titoli - cont);
				cont++;
				break ;
			}
			if (cont == num_titoli)
			{
				printf("Capitoli tutti ripetuti. Bravo!!!\n");
                free(titoli); // Libera l'array di puntatori
/*                printf("\nPremi Invio per chiudere..."); //inserire questo commento prima di compilazione x Windows
                while (getchar() != '\n'); // Svuota il buffer
                    getchar(); // Attende un input dall'utente */
				exit (0);
			}
		}
        printf("\nCapitolo successivo? (s/n): ");
        clear_input_buffer();
    	scanf("%c", &playagain);
        system("clear"); //sostituire con cls per Windows
    	while (playagain != 's' && playagain != 'n')
    	{
        	printf("Input non valido. Capitolo successivo? (s/n): ");
            clear_input_buffer();
        	scanf("%c", &playagain);
    	}
    } while (playagain == 's'); // Cerca un nuovo titolo se l'utente inserisce 's'
    printf("\nVuoi salvare lo stato di avanzamento del ripasso? (s/n): ");
    clear_input_buffer();
    scanf("%c", &save);
    while (save != 's' && save != 'n')
    {
        printf("Input non valido: solo 's' o 'n'. Vuoi salvare? (s/n): ");
        clear_input_buffer();
        scanf("%c", &save);
    }
    if (save == 's')
    {
        printf("\nDammi il nome del file da salvare o premi <ENTER> per default 'save.sav'?: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL)
        {
            perror("Errore nella lettura dell'input");
            return(0);
        }
        filename[strcspn(filename, "\n")] = '\0'; // Rimuove il '\n' finale se presente
        if (filename[0] == '\0')
            strcpy(filename, "save.sav");
        ft_savefile (filename, array, num_titoli);
        printf("\nStato di avanzamento ripasso salvato sul file '%s'\n", filename);
    }
    free (array);
    i = 0;
    while (i < num_titoli)
    {
        free(titoli[i]); // Libera ogni stringa
        i++;
    }
	free(titoli); // Libera l'array di puntatori
/*    printf("\nPremi Invio per chiudere...");
    while (getchar() != '\n'); // Svuota il buffer
        getchar(); // Attende un input dall'utente*/
    return (0);
}
