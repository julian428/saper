#ifndef BOARD_H
#define BOARD_H

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

extern char **board;
extern char **display;
extern int ROWS, COLS, MINES;
extern int difficulty; // Poziom trudności: 1 - Łatwy, 2 - Średni, 3 - Trudny, 0 - Własny
extern int revealedFields;

void initializeBoard();
void freeBoard();
void placeMines();
void clearConsole();
void printBoard(char **b);
int reveal(int row, int col);
void placeFlag(int row, int col);
int checkWin();

#endif
