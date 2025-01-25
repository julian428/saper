#include <stdio.h>
#include <string.h>
#include "board.h"
#include "config.h"

int difficulty;
int revealedFields;

int main(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "-f") == 0)
    {
        // Tryb wczytywania ruchów z pliku
        chooseDifficulty();
        initializeBoard();
        placeMines();

        const char *filename = argv[2];
        return processMovesFromFile(filename);
    }

    // Tryb standardowy
    chooseDifficulty();
    initializeBoard();
    placeMines();

    printf("Witamy w grze Saper!\n");

    while (1)
    {
        printBoard(display);
        char action;
        int x, y;
        printf("Podaj akcję (r - odkryj, f - flaga) oraz kolumnę (x) i wiersz (y) (np. r 1 0): ");
        scanf(" %c %d %d", &action, &x, &y);

        if (action == 'r')
        {
            int result = reveal(y, x); // Zmieniamy kolejność argumentów (y, x)

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
            placeFlag(y, x); // Zmieniamy kolejność argumentów (y, x)
        }
        else
        {
            printf("Nieprawidłowa akcja. Użyj 'r' lub 'f'.\n");
        }
    }

    // Wyświetl wynik i zapisz do pliku
    int score = revealedFields * difficulty;
    printf("\nTwój wynik: %d (odsłonięte pola: %d * mnożnik: %d)\n", score, revealedFields, difficulty);

    char playerName[50];
    printf("Podaj swoje imię: ");
    scanf("%s", playerName);
    saveScore(playerName, score);

    // Wyświetl top 5 wyników
    showTopScores();

    freeBoard();
    return 0;
}
