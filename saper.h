#ifndef SAPER_H
#define SAPER_H

#define ROWS 9
#define COLS 9
#define MINES 10

// Deklaracje globalnych zmiennych
extern char board[ROWS][COLS];
extern char display[ROWS][COLS];

// Deklaracje funkcji
void initializeBoard();
void placeMines();
void printBoard(char b[ROWS][COLS]);
int reveal(int row, int col);
void placeFlag(int row, int col);
int checkWin();

#endif
