#include "saper.h"
#include <stdio.h>

int main()
{
    initializeBoard();
    placeMines();

    printf("Witamy w grze Saper!\n");

    while (1)
    {
        printBoard(display);
        char action;
        int row, col;
        printf("Podaj akcję (o - odkryj, f - flaga) oraz wiersz i kolumnę (np. o 0 1): ");
        scanf(" %c %d %d", &action, &row, &col);

        if (action == 'o')
        {
            int result = reveal(row, col);

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
            placeFlag(row, col);
        }
        else
        {
            printf("Nieprawidłowa akcja. Użyj 'o' lub 'f'.\n");
        }
    }

    return 0;
}
