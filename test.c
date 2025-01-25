#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "config.h"

int difficulty;
int revealedFields;

void test_easy_game()
{
    printf("=== Test: Gra ===\n");
    ROWS = 9;
    COLS = 9;
    MINES = 10;
    initializeBoard();
    placeMines();

    int initialRevealed = revealedFields;
    reveal(0, 0);
    if (revealedFields > initialRevealed)
    {
        printf("PASSED: polecenie r zadziałało poprawnie.\n");
    }
    else
    {
        printf("FAILED: polecenie r nie odsłoniło żadnej komórki.\n");
    }

    freeBoard();
}

void test_custom_game()
{
    printf("=== Test: Gra własna ===\n");
    ROWS = 5;
    COLS = 5;
    MINES = 3;
    initializeBoard();
    placeMines();

    if (MINES > 0 && board != NULL)
    {
        printf("PASSED: Gra własna zainicjalizowana poprawnie.\n");
    }
    else
    {
        printf("FAILED: Nie udało się zainicjalizować gry własnej.\n");
    }

    freeBoard();
}

void test_moves_from_file()
{
    printf("=== Test: Ruchy z pliku ===\n");
    const char *testFile = "test_moves.txt";
    FILE *file = fopen(testFile, "w");
    if (!file)
    {
        printf("FAILED: Nie udało się stworzyć pliku.\n");
        return;
    }
    fprintf(file, "r 0 0\nr 1 1\nf 2 2\n");
    fclose(file);

    // Dodaj inicjalizację zmiennych globalnych
    ROWS = 9;
    COLS = 9;
    MINES = 10;

    initializeBoard();
    placeMines();

    int result = processMovesFromFile(testFile);
    if (result >= 0)
    {
        printf("PASSED: Ruchy z pliku zostały przeprowadzone poprawnie.\n");
    }
    else
    {
        printf("FAILED: Błąd ruchów z pliku.\n");
    }

    freeBoard();      // Sprzątanie pamięci
    remove(testFile); // Usunięcie pliku testowego
}

int main()
{
    test_easy_game();
    test_custom_game();
    test_moves_from_file();
    return 0;
}
