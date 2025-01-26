#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "config.h"

int difficulty;
int revealedFields;

void test_easy_game()
{
    printf(YELLOW "=== Test: Gra ===\n" RESET);
    ROWS = 9;
    COLS = 9;
    MINES = 10;
    initializeBoard();
    placeMines();

    int initialRevealed = revealedFields;
    reveal(0, 0);
    if (revealedFields > initialRevealed)
    {
        printf(GREEN "PASSED: polecenie r zadziałało poprawnie.\n" RESET);
    }
    else
    {
        printf(RED "FAILED: polecenie r nie odsłoniło żadnej komórki.\n" RESET);
    }

    freeBoard();
}

void test_custom_game()
{
    printf(CYAN "\n=== Test: Gra własna ===\n" RESET);
    ROWS = 5;
    COLS = 5;
    MINES = 3;
    initializeBoard();
    placeMines();

    if (MINES > 0 && board != NULL)
    {
        printf(GREEN "PASSED: Gra własna zainicjalizowana poprawnie.\n" RESET);
    }
    else
    {
        printf(RED "FAILED: Nie udało się zainicjalizować gry własnej.\n" RESET);
    }

    freeBoard();
}

void test_moves_from_file()
{
    printf(MAGENTA "\n=== Test: Ruchy z pliku ===\n" RESET);
    const char *testFile = "test_moves.txt";
    FILE *file = fopen(testFile, "w");
    if (!file)
    {
        printf(RED "FAILED: Nie udało się stworzyć pliku.\n" RESET);
        return;
    }
    fprintf(file, "r 0 0\nr 1 1\nf 2 2\n");
    fclose(file);

    ROWS = 9;
    COLS = 9;
    MINES = 10;

    initializeBoard();
    placeMines();

    int result = processMovesFromFile(testFile);
    if (result >= 0)
    {
        printf(GREEN "PASSED: Ruchy z pliku zostały przeprowadzone poprawnie.\n" RESET);
    }
    else
    {
        printf(RED "FAILED: Błąd ruchów z pliku.\n" RESET);
    }

    freeBoard();
    remove(testFile);
}

int main()
{
    test_easy_game();
    test_custom_game();
    test_moves_from_file();
    return 0;
}
