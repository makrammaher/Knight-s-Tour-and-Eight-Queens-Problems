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
    unsigned int counter = 0;
    srand(time(NULL));

    while(counter < NUMBER_OF_TEST)
    {
        counter++;
        numberOfSuccessQueens = 0;
        initBoard(board);
        initElimination(elimination);
        while (possibleMoves(elimination))
        {
            position[0] = rand() % BOARD_SIZE_HIGHT;
            position[1] = rand() % BOARD_SIZE_WEDTH;

            if (isValidMove(board, position))
            {
                PutQween(board, elimination, position);
                numberOfSuccessQueens++;
            }
        }
        frequncey[numberOfSuccessQueens]++;
        
        
        if (numberOfSuccessQueens >= 8)
        {
            printBoard(board);
            puts("");
            printElimination(elimination);
            printf("\nTotal Success Queens = %u\n\n", numberOfSuccessQueens);
            //getchar();
            //Sleep(500);
        }
        //Sleep(1000);
    }
    for (unsigned int i = 1; i < NUMBER_OF_QWEENS + 1; i++)
    {
        printf("frequncy[%u] = %3u\n", i, frequncey[i]);
    }
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