#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

// Kolory ANSI
#define RESET "\033[0m"
#define DARK_GRAY "\033[1;30m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"
#define WHITE "\033[1;37m"

char **board;
char **display;
int ROWS, COLS, MINES;

void initializeBoard()
{
    board = malloc(ROWS * sizeof(char *));
    display = malloc(ROWS * sizeof(char *));

    for (int i = 0; i < ROWS; i++)
    {
        board[i] = malloc(COLS * sizeof(char));
        display[i] = malloc(COLS * sizeof(char));
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = '0';
            display[i][j] = '*';
        }
    }
}

void freeBoard()
{
    for (int i = 0; i < ROWS; i++)
    {
        free(board[i]);
        free(display[i]);
    }
    free(board);
    free(display);
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

void printBoard(char **b)
{
    printf("    "); // Dodatkowe odstępy dla numerów kolumn
    for (int j = 0; j < COLS; j++)
    {
        printf("%2d ", j); // Wyrównanie numerów kolumn do dwóch cyfr
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++)
    {
        printf("%2d |", i); // Wyrównanie numerów wierszy do dwóch cyfr
        for (int j = 0; j < COLS; j++)
        {
            char cell = b[i][j];
            switch (cell)
            {
            case '0':
                printf(DARK_GRAY " %c " RESET, cell);
                break;
            case '1':
                printf(BLUE " %c " RESET, cell);
                break;
            case '2':
                printf(GREEN " %c " RESET, cell);
                break;
            case '3':
                printf(YELLOW " %c " RESET, cell);
                break;
            case '4':
                printf(MAGENTA " %c " RESET, cell);
                break;
            case '5':
                printf(CYAN " %c " RESET, cell);
                break;
            case '6':
                printf(RED " %c " RESET, cell);
                break;
            case '7':
                printf(WHITE " %c " RESET, cell);
                break;
            case '8':
                printf(WHITE " %c " RESET, cell);
                break;
            case '*': // Niewidoczne pole
            case 'F': // Flaga
                printf(WHITE " %c " RESET, cell);
                break;
            case 'M': // Mina, może być wyświetlana w grze przegranej
                printf(RED " %c " RESET, cell);
                break;
            default:
                printf(" %c ", cell);
                break;
            }
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
        return -1; // Trafiono minę
    }

    revealedFields++;

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
    if (!display || !board)
    {
        printf("Błąd: Plansza nie została zainicjalizowana.\n");
        return -1; // Kod błędu
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (display[i][j] == '*' && board[i][j] != 'M')
            {
                return 0; // Gra jeszcze się nie skończyła
            }
        }
    }
    return 1; // Wszystkie pola odkryte
}
