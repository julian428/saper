#include "saper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tablice globalne
char board[ROWS][COLS];
char display[ROWS][COLS];

void initializeBoard()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = '0';
            display[i][j] = '*';
        }
    }
}

void placeMines()
{
    srand(time(NULL));
    int placedMines = 0;

    while (placedMines < MINES)
    {
        int row = rand() % ROWS;
        int col = rand() % COLS;

        if (board[row][col] != 'M')
        {
            board[row][col] = 'M';
            placedMines++;

            // Update numbers around the mine
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int newRow = row + i;
                    int newCol = col + j;

                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && board[newRow][newCol] != 'M')
                    {
                        board[newRow][newCol]++;
                    }
                }
            }
        }
    }
}

void printBoard(char b[ROWS][COLS])
{
    printf("  ");
    for (int j = 0; j < COLS; j++)
    {
        printf(" %d", j);
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++)
    {
        printf("%d ", i);
        for (int j = 0; j < COLS; j++)
        {
            printf(" %c", b[i][j]);
        }
        printf("\n");
    }
}

int reveal(int row, int col)
{
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || display[row][col] != '*')
    {
        return 0;
    }

    display[row][col] = board[row][col];

    if (board[row][col] == 'M')
    {
        return -1; // Hit a mine
    }

    if (board[row][col] == '0')
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                reveal(row + i, col + j);
            }
        }
    }

    return 0;
}

void placeFlag(int row, int col)
{
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
    {
        printf("Nieprawidłowe współrzędne.\n");
        return;
    }

    if (display[row][col] == '*')
    {
        display[row][col] = 'F';
    }
    else if (display[row][col] == 'F')
    {
        display[row][col] = '*';
    }
    else
    {
        printf("Nie można postawić flagi na odkrytym polu.\n");
    }
}

int checkWin()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (display[i][j] == '*' && board[i][j] != 'M')
            {
                return 0;
            }
        }
    }
    return 1;
}
