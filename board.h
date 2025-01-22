#ifndef BOARD_H
#define BOARD_H

extern char **board;
extern char **display;
extern int ROWS, COLS, MINES;
extern int difficulty;     // Poziom trudności: 1 - Łatwy, 2 - Średni, 3 - Trudny, 0 - Własny
extern int revealedFields; // Licznik odsłoniętych pól

void initializeBoard();
void freeBoard();
void placeMines();
void printBoard(char **b);
int reveal(int row, int col);
void placeFlag(int row, int col);
int checkWin();

#endif
