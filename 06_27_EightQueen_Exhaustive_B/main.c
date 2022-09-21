#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<Windows.h>

#define BOARD_SIZE_WEDTH    8
#define BOARD_SIZE_HIGHT    8
#define NUMBER_OF_QWEENS    8
#define NUMBER_OF_TEST      100000

void initElimination(unsigned int elimination[][BOARD_SIZE_WEDTH]);
void initBoard(unsigned int board[][BOARD_SIZE_WEDTH]);
void printBoard(unsigned int board[][BOARD_SIZE_WEDTH]);
void printElimination(unsigned int elimination[][BOARD_SIZE_WEDTH]);
bool isValidMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[]);
void PutQween(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int elimination[][BOARD_SIZE_WEDTH], unsigned int position[]);
bool possibleMoves(unsigned int elimination[][BOARD_SIZE_WEDTH]);

int main(void)
{
    unsigned int board[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH] = { 0 };
    unsigned int elimination[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH] = { 0 };
    unsigned int frequncey[NUMBER_OF_QWEENS + 1] = { 0 };
    unsigned int position[2];
    unsigned int numberOfSuccessQueens = 0;

    
    for (size_t a1 = 0; a1 < NUMBER_OF_QWEENS; a1++)
    {
        position[0] = 0;
        position[1] = a1;
        if (isValidMove(board, position))
        {
            board[0][a1] = 1;
            for (size_t a2 = 0; a2 < NUMBER_OF_QWEENS; a2++)
            {
                position[0] = 1;
                position[1] = a2;
                if (isValidMove(board, position))
                {
                    board[1][a2] = 1;
                    for (size_t a3 = 0; a3 < NUMBER_OF_QWEENS; a3++)
                    {
                        position[0] = 2;
                        position[1] = a3;
                        if (isValidMove(board, position))
                        {
                            board[2][a3] = 1;
                            for (size_t a4 = 0; a4 < NUMBER_OF_QWEENS; a4++)
                            {
                                position[0] = 3;
                                position[1] = a4;
                                if (isValidMove(board, position))
                                {
                                    board[3][a4] = 1;
                                    for (size_t a5 = 0; a5 < NUMBER_OF_QWEENS; a5++)
                                    {
                                        position[0] = 4;
                                        position[1] = a5;
                                        if (isValidMove(board, position))
                                        {
                                            board[4][a5] = 1;
                                            for (size_t a6 = 0; a6 < NUMBER_OF_QWEENS; a6++)
                                            {
                                                position[0] = 5;
                                                position[1] = a6;
                                                if (isValidMove(board, position))
                                                {
                                                    board[5][a6] = 1;
                                                    for (size_t a7 = 0; a7 < NUMBER_OF_QWEENS; a7++)
                                                    {
                                                        position[0] = 6;
                                                        position[1] = a7;
                                                        if (isValidMove(board, position))
                                                        {
                                                            board[6][a7] = 1;
                                                            for (size_t a8 = 0; a8 < NUMBER_OF_QWEENS; a8++)
                                                            {
                                                                position[0] = 7;
                                                                position[1] = a8;
                                                                if (isValidMove(board, position))
                                                                {
                                                                    board[7][a8] = 1;

                                                                    printBoard(board);
                                                                    numberOfSuccessQueens++;
                                                                }
                                                                board[7][a8] = 0;
                                                            }
                                                        }
                                                        board[6][a7] = 0;
                                                    }
                                                }
                                                board[5][a6] = 0;
                                            }
                                        }
                                        board[4][a5] = 0;
                                    }
                                }
                                board[3][a4] = 0;
                            }
                        }
                        board[2][a3] = 0;
                    }
                }
                board[1][a2] = 0;
            }
        }
        board[0][a1] = 0;
    }

    printf("Total number of success = %u\n", numberOfSuccessQueens);
}

bool possibleMoves(unsigned int elimination[][BOARD_SIZE_WEDTH])
{
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            if (elimination[i][j] == 1)
            {
                return true;
            }
        }
    }
    return false;
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

    }
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


void initElimination(unsigned int elimination[][BOARD_SIZE_WEDTH])
{
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            elimination[i][j] = 1;
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
        printf("%s", "|---");
    }
    puts("|");
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            if (board[i][j] == 1)
            {
                printf("|%2s ", "Q");
            }
            else
            {
                printf("|%2c ", ' ');
            }
        }
        puts("|");
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            printf("%s", "|---");
        }
        puts("|");
    }
}

void printElimination(unsigned int elimination[][BOARD_SIZE_WEDTH])
{
    //system("cls");
    for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
    {
        printf("%s", "|---");
    }
    puts("|");
    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            printf("|%2u ", elimination[i][j]);
        }
        puts("|");
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            printf("%s", "|---");
        }
        puts("|");
    }
}