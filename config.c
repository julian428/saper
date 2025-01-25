#include <stdio.h>
#include "config.h"
#include "board.h"

// Funkcja do zapisywania wyniku
void saveScore(const char *name, int score)
{
    FILE *file = fopen("scores.txt", "a");
    if (file == NULL)
    {
        printf("Nie można otworzyć pliku wyników.\n");
        return;
    }
    fprintf(file, "%s %d\n", name, score);
    fclose(file);
}

// Funkcja do wyświetlania top 5 wyników
void showTopScores()
{
    FILE *file = fopen("scores.txt", "r");
    if (file == NULL)
    {
        printf("Brak zapisanych wyników.\n");
        return;
    }

    typedef struct
    {
        char name[50];
        int score;
    } Player;

    Player players[100];
    int count = 0;

    // Wczytaj wyniki z pliku
    while (fscanf(file, "%s %d", players[count].name, &players[count].score) == 2)
    {
        count++;
    }
    fclose(file);

    // Posortuj wyniki malejąco
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (players[i].score < players[j].score)
            {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    // Wyświetl top 5
    printf("\n--- TOP 5 NAJLEPSZYCH WYNIKÓW ---\n");
    for (int i = 0; i < count && i < 5; i++)
    {
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score);
    }
}

void chooseDifficulty()
{
    int choice;
    printf("Wybierz poziom trudności:\n");
    printf("1. Łatwy (9x9, 10 min)\n");
    printf("2. Średni (16x16, 40 min)\n");
    printf("3. Trudny (16x30, 99 min)\n");
    printf("4. Własna plansza\n");
    printf("Twój wybór: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        ROWS = EASY_ROWS;
        COLS = EASY_COLS;
        MINES = EASY_MINES;
        difficulty = 1;
        break;
    case 2:
        ROWS = MEDIUM_ROWS;
        COLS = MEDIUM_COLS;
        MINES = MEDIUM_MINES;
        difficulty = 2;
        break;
    case 3:
        ROWS = HARD_ROWS;
        COLS = HARD_COLS;
        MINES = HARD_MINES;
        difficulty = 3;
        break;
    case 4:
        printf("Podaj liczbę wierszy: ");
        scanf("%d", &ROWS);
        printf("Podaj liczbę kolumn: ");
        scanf("%d", &COLS);
        printf("Podaj liczbę min: ");
        scanf("%d", &MINES);
        if (MINES >= ROWS * COLS)
        {
            printf("Za dużo min na planszy! Ustawienie domyślne (łatwy).\n");
            ROWS = EASY_ROWS;
            COLS = EASY_COLS;
            MINES = EASY_MINES;
            difficulty = 1;
        }
        else
        {
            difficulty = 0; // Własny poziom trudności
        }
        break;
    default:
        printf("Nieprawidłowy wybór. Ustawienie domyślne (łatwy).\n");
        ROWS = EASY_ROWS;
        COLS = EASY_COLS;
        MINES = EASY_MINES;
        difficulty = 1;
    }
}
