#include <stdio.h>
#include "board.h"
#include "config.h"

int main()
{
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

    freeBoard();
    return 0;
}
