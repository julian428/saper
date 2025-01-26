#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "board.h"
#include "config.h"

int difficulty;
int revealedFields;

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "f:")) != -1)
    {
        // Tryb wczytywania ruchów z pliku
        if (opt == 'f')
        {
            chooseDifficulty();
            initializeBoard();
            placeMines();

            const char *filename = argv[2];
            return processMovesFromFile(filename);
        }
    }

    // Tryb standardowy
    chooseDifficulty();
    initializeBoard();
    placeMines();

    printf("Witam w grze Saper!\n");

    while (1)
    {
        printBoard(display);
        char action;
        int x, y;
        printf("Podaj akcję (r - odkryj, f - flaga) oraz kolumnę (x) i wiersz (y) (np. r 1 0): ");
        if (scanf(" %c %d %d", &action, &x, &y) != 3)
        {
            printf("format ruchu to r/f x y");
        }

        if (action == 'r')
        {
            int result = reveal(y, x);

            if (result == -1)
            {
                printf("\nPrzegrałeś! Oto ukryta plansza:\n");
                printBoard(board);
                break;
            }

            if (checkWin())
            {
                printf("\nGratulacje! Wygrałeś!\n");
                printBoard(board);
                break;
            }
        }
        else if (action == 'f')
        {
            placeFlag(y, x);
        }
        else
        {
            printf("Nieprawidłowa akcja. Użyj 'r' lub 'f'.\n");
        }
    }

    int score = revealedFields * difficulty;
    printf("\nTwój wynik: %d (odsłonięte pola: %d * mnożnik: %d)\n", score, revealedFields, difficulty);

    if (difficulty != 0)
    {
        char playerName[50];
        printf("Podaj swoje imię: ");
        if (scanf("%s", playerName) == 1)
            saveScore(playerName, score);
    }

    showTopScores();

    freeBoard();
    return 0;
}
