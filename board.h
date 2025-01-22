#ifndef BOARD_H
#define BOARD_H

extern char **board;
extern char **display;
extern int ROWS, COLS, MINES;

void initializeBoard();
void freeBoard();
void placeMines();
void printBoard(char **b);
int reveal(int row, int col);
void placeFlag(int row, int col);
int checkWin();

#endif
