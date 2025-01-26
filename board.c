#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "board.h"

int consoleWidth = 80;  // Domyślna szerokość
int consoleHeight = 24; // Domyślna wysokość

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

void getConsoleSize()
{
    struct winsize w;
    // pokazuje error ale działa
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
    {
        consoleWidth = w.ws_col;
        consoleHeight = w.ws_row;
    }
}

void clearConsole()
{
    printf("\033[H\033[J"); // ANSI: \033[H - kursor do góry, \033[J - czyści ekran
}

void printBoard(char **b)
{
    getConsoleSize(); // Pobranie rozmiaru konsoli

    // Obliczanie odstępów dla centrowania
    int paddingTop = (consoleHeight - ROWS - 3) / 2; // -3 na nagłówki
    int paddingLeft = (consoleWidth - (COLS * 3)) / 2;

    clearConsole();

    // Wyświetlanie pustych wierszy na górze (centrowanie w pionie)
    for (int i = 0; i < paddingTop; i++)
    {
        printf("\n");
    }

    printf("%*s", paddingLeft, ""); // Centrowanie numerów kolumn
    printf("    ");                 // Odstęp na numery wierszy
    for (int j = 0; j < COLS; j++)
    {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++)
    {
        printf("%*s", paddingLeft, ""); // Odstęp dla centrowania planszy
        printf("%2d |", i);             // Numer wiersza
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
            case '8':
                printf(WHITE " %c " RESET, cell);
                break;
            case '*': // Niewidoczne pole
            case 'F': // Flaga
                printf(WHITE " %c " RESET, cell);
                break;
            case 'M': // Mina
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
