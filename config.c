#include <stdio.h>
#include "config.h"

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
        break;
    case 2:
        ROWS = MEDIUM_ROWS;
        COLS = MEDIUM_COLS;
        MINES = MEDIUM_MINES;
        break;
    case 3:
        ROWS = HARD_ROWS;
        COLS = HARD_COLS;
        MINES = HARD_MINES;
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
        }
        break;
    default:
        printf("Nieprawidłowy wybór. Ustawienie domyślne (łatwy).\n");
        ROWS = EASY_ROWS;
        COLS = EASY_COLS;
        MINES = EASY_MINES;
    }
}
