#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<Windows.h>

#define BOARD_SIZE_WEDTH    8
#define BOARD_SIZE_HIGHT    8
#define NUMBER_OF_QWEENS    8


void initElimination(unsigned int elimination[][BOARD_SIZE_WEDTH]);
void reInitElimination(unsigned int elimination[][BOARD_SIZE_WEDTH]);
void initBoard(unsigned int board[][BOARD_SIZE_WEDTH]);
void printBoard(unsigned int board[][BOARD_SIZE_WEDTH]);
void printElimination(unsigned int elimination[][BOARD_SIZE_WEDTH]);
bool isValidMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[]);
void PutQween(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int elimination[][BOARD_SIZE_WEDTH], unsigned int position[]);

int main(void)
{
    unsigned int board[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH] = { 0 };
    unsigned int elimination[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH] = { 0 };
    unsigned int position[2];

    initElimination(elimination);
    printBoard(board);
    puts("");
    printElimination(elimination);

    position[0] = 4;
    position[1] = 0;
    PutQween(board, elimination, position);
    for (unsigned int k = 0; k < NUMBER_OF_QWEENS; k++)
    {
        unsigned int smallest = 100;
        for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
        {
            for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
            {
                if (elimination[i][j] != 0 && elimination[i][j] < smallest)
                {
                    smallest = elimination[i][j];
                    position[0] = i;
                    position[1] = j;
                }
            }
        }

        PutQween(board, elimination, position);
        printBoard(board);
        puts("");
        printElimination(elimination);
        Sleep(500);
    }
    

    printBoard(board);
    puts("");
    printElimination(elimination);
}

bool isValidMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[])
{
    
    for (unsigned int i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        if (board[i][position[1]] == 1 || board[position[0]][i] == 1)
            return false;
        
    }
    //check for diagonals
    for (unsigned int k = 1; k < BOARD_SIZE_HIGHT; k++)
    {
        if (position[0] + k < BOARD_SIZE_HIGHT && position[1] + k < BOARD_SIZE_WEDTH && board[position[0] + k][position[1] + k] == 1)
            return false;
        if ((int)(position[0] - k) >= 0 && (int)(position[1] - k) >= 0 && board[(int)(position[0] - k)][(int)(position[1] - k)] == 1)
            return false;
        if (position[0] + k < BOARD_SIZE_HIGHT && (int)(position[1] - k) >= 0 && board[position[0] + k][(int)(position[1] - k)] == 1)
            return false;
        if ((int)(position[0] - k) >= 0 && position[1] + k < BOARD_SIZE_WEDTH && board[(int)(position[0] - k)][position[1] + k] == 1)
            return false;
    }

    return true;
}

void PutQween(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int elimination[][BOARD_SIZE_WEDTH], unsigned int position[])
{
    if (isValidMove(board, position))
    {
        board[position[0]][position[1]] = 1;

        //Reassign elimination
        elimination[position[0]][position[1]] = 0;

        for (unsigned int i = 0; i < BOARD_SIZE_HIGHT; i++)
        {
            elimination[i][position[1]] = 0;
            elimination[position[0]][i] = 0;
        }
        for (unsigned int k = 1; k < BOARD_SIZE_HIGHT; k++)
        {
            if (position[0] + k < BOARD_SIZE_HIGHT && position[1] + k < BOARD_SIZE_WEDTH)
                elimination[position[0] + k][position[1] + k] = 0;
            if ((int)(position[0] - k) >= 0 && (int)(position[1] - k) >= 0)
                elimination[(int)(position[0] - k)][(int)(position[1] - k)] = 0;
            if (position[0] + k < BOARD_SIZE_HIGHT && (int)(position[1] - k) >= 0)
                elimination[position[0] + k][(int)(position[1] - k)] = 0;
            if ((int)(position[0] - k) >= 0 && position[1] + k < BOARD_SIZE_WEDTH)
                elimination[(int)(position[0] - k)][position[1] + k] = 0;
        }
        reInitElimination(elimination);
        
    }
}

void reInitElimination(unsigned int elimination[][BOARD_SIZE_WEDTH])
{
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            if (elimination[i][j] != 0)
            {
                unsigned int totalElimination = 0;
                for (unsigned int k = 0; k < BOARD_SIZE_HIGHT; k++)
                {
                    if (elimination[k][j] != 0)
                        totalElimination++;
                    if(elimination[i][k] != 0)
                        totalElimination++;
                }
                for (unsigned int k = 1; k < BOARD_SIZE_HIGHT; k++)
                {
                    if (i + k < BOARD_SIZE_HIGHT && j + k < BOARD_SIZE_WEDTH && elimination[i + k][j + k] != 0)
                        totalElimination++;
                    if ((int)(i - k) >= 0 && (int)(j - k) >= 0 && elimination[(i - k)][j - k] != 0)
                        totalElimination++;
                    if (i + k < BOARD_SIZE_HIGHT && (int)(j - k) >= 0 && elimination[i + k][j - k] != 0)
                        totalElimination++;
                    if ((int)(i - k) >= 0 && j + k < BOARD_SIZE_WEDTH && elimination[i - k][j + k] != 0)
                        totalElimination++;
                }
                elimination[i][j] = totalElimination - 1;
            }
        }
    }
}

void initElimination(unsigned int elimination[][BOARD_SIZE_WEDTH])
{
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            unsigned int totalElimination = BOARD_SIZE_HIGHT + BOARD_SIZE_WEDTH - 1;
            for (unsigned int k = 1; k < BOARD_SIZE_HIGHT; k++)
            {
                if (i + k < BOARD_SIZE_HIGHT && j + k < BOARD_SIZE_WEDTH)
                    totalElimination++;
                if ((int)(i - k) >= 0 && (int)(j - k) >= 0)
                    totalElimination++;
                if (i + k < BOARD_SIZE_HIGHT && (int)(j - k) >= 0)
                    totalElimination++;
                if ((int)(i - k) >= 0 && j + k < BOARD_SIZE_WEDTH)
                    totalElimination++;
            }
            elimination[i][j] = totalElimination;
        }
    }
}

void initBoard(unsigned int board[][BOARD_SIZE_WEDTH])
{
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            board[i][j] = 0;
        }
    }
}

void printBoard(unsigned int board[][BOARD_SIZE_WEDTH])
{
    system("cls");
    for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
    {
        printf("%s", "|----");
    }
    puts("|");
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            if (board[i][j] == 1)
            {
                printf("|%3s ", "#Q");
            }
            else
            {
                printf("|%3c ", ' ');
            }
        }
        puts("|");
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            printf("%s", "|----");
        }
        puts("|");
    }
}

void printElimination(unsigned int elimination[][BOARD_SIZE_WEDTH])
{
    //system("cls");
    for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
    {
        printf("%s", "|----");
    }
    puts("|");
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            printf("|%3u ", elimination[i][j]);
        }
        puts("|");
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            printf("%s", "|----");
        }
        puts("|");
    }
}