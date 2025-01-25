#ifndef CONFIG_H
#define CONFIG_H

#define EASY_ROWS 9
#define EASY_COLS 9
#define EASY_MINES 10

#define MEDIUM_ROWS 16
#define MEDIUM_COLS 16
#define MEDIUM_MINES 40

#define HARD_ROWS 16
#define HARD_COLS 30
#define HARD_MINES 99

extern int ROWS, COLS, MINES;

void saveScore(const char *name, int score);
void showTopScores();
void chooseDifficulty();

#endif
