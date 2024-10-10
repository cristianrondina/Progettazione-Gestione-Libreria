#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXCHAR 1000
#define MAX_LIBRI 100

enum CategoriaLibro
{
    NARRATIVA = 1,
    SAGGISTICA,
    SCIENZE,
    ARTE
};

struct Libro
{
    char titolo[50];
    char autore[50];
    int anno;
    float prezzo;
    enum CategoriaLibro categoria;
};

void LetturaFile(struct Libro libri[], int *count)
{
    FILE *fp;
    char lettura[MAXCHAR];

    fp = fopen("libreria.csv", "r");
    if (fp == NULL)
    {
        printf("Errore nell'apertura del file\n");
        return;
    }
    while (fgets(lettura, MAXCHAR, fp) != NULL)
    {
        if (*count >= MAX_LIBRI)
        {
            printf("Massimo numero di libri raggiunto\n");
            break;
        }

        char *token = strtok(lettura, ",");
        if (token != NULL)
        {
            strcpy(libri[*count].titolo, token);
            token = strtok(NULL, ",");
            if (token != NULL)
            {
                strcpy(libri[*count].autore, token);
                token = strtok(NULL, ",");
                if (token != NULL)
                {
                    libri[*count].anno = atoi(token);
                    token = strtok(NULL, ",");
                    if (token != NULL)
                    {
                        libri[*count].prezzo = atof(token);
                        token = strtok(NULL, ",");
                        if (token != NULL)
                        {
                            libri[*count].categoria = atoi(token);
                        }
                    }
                }
            }
        }
        (*count)++;
    }
    fclose(fp);
}

void StampaLibri(const struct Libro libri[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("\nTitolo: %s, Autore: %s, Anno: %d, Prezzo: %.2f, Categoria: %d\n",
               libri[i].titolo, libri[i].autore, libri[i].anno, libri[i].prezzo, libri[i].categoria);
    }
}

void StampaLibriPerCategoria(const struct Libro libri[], int count, enum CategoriaLibro categoria)
{
    printf("Libri nella categoria %d:\n", categoria);
    for (int i = 0; i < count; i++)
    {
        if (libri[i].categoria == categoria)
        {
            printf("Titolo: %s, Autore: %s, Anno: %d, Prezzo: %.2f\n",
                   libri[i].titolo, libri[i].autore, libri[i].anno, libri[i].prezzo);
        }
    }
}

struct Libro *CercaLibro(const struct Libro libri[], int count, const char *titolo)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(libri[i].titolo, titolo) == 0)
        {
            return &libri[i];
        }
    }
    return NULL; // Non trovato
}

enum CategoriaLibro LeggiCategoria()
{
    int scelta;
    printf("\nInserisci la categoria (1: Narrativa, 2: Saggistica, 3: Scienze, 4: Arte): ");
    scanf("%d", &scelta);
    return (enum CategoriaLibro)scelta;
}

int main()
{
    struct Libro libri[MAX_LIBRI];
    int count = 0;

    LetturaFile(libri, &count);
    printf("ECCO TUTTI I LIBRI PRESENTI NELLA LIBRERIA");
    StampaLibri(libri, count);

    // Chiedere all'utente di inserire la categoria
    enum CategoriaLibro categoria = LeggiCategoria();
    StampaLibriPerCategoria(libri, count, categoria);

    // Chiedere all'utente di inserire il titolo del libro da cercare
    char titoloDaCercare[50];
    printf("\nInserisci il titolo del libro da cercare: ");
    scanf(" %[^\n]", titoloDaCercare); // Leggi fino al carattere di nuova linea

    struct Libro *libroCercato = CercaLibro(libri, count, titoloDaCercare);
    if (libroCercato)
    {
        printf("\nLibro trovato: %s, Autore: %s, Anno: %d, Prezzo: %.2f\n",
               libroCercato->titolo, libroCercato->autore, libroCercato->anno, libroCercato->prezzo);
    }
    else
    {
        printf("Libro non trovato\n");
    }

    return 0;
}
