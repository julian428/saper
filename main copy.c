#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *generateGameMatrix(int size, int bombs, float fix)
{
    char *matrix = (char *)calloc(size, sizeof(char));

    // wypełniam macierz bombami
    for (int i = 0, bombCounter = bombs; i < size && bombCounter > 0; i++)
    {
        if (((double)rand() / RAND_MAX) > (fix * (double)bombs / size))
            continue;
        matrix[i] = 1;
        bombCounter--;
    }

    return matrix;
}

void drawBoard(char *gameMatrix, int x, int y)
{
    for (int i = 0; i < x * y; i++)
    {
        if (i % x == 0)
            printf("\n");
        if ((int)gameMatrix[i] < 2)
            printf("#");
        printf("%c", gameMatrix[i]);
    }
    printf("\n");
}
int makeMove(char *gameMatrix, int x, int y)
{
    char move[5];
    fgets(move, 4, stdin);
    int xPos = (int)atoi((char)move[2]);
    int yPos = (int)atoi((char)move[4]);

    int linearPosition = (yPos)*x + xPos;
    printf("%d, %d, %d\n", linearPosition, xPos, yPos);

    gameMatrix[linearPosition] = gameMatrix[linearPosition] * 68 + 20;
}

int main()
{
    srand(time(NULL));
    int x = 8, y = 8;
    char *gameMatrix = generateGameMatrix(x * y, 20, 1.5);
    while (1)
    {
        drawBoard(gameMatrix, x, y);
        makeMove(gameMatrix, x, y);
    }
}