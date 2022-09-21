#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<Windows.h>


#define BOARD_SIZE_WEDTH    8
#define BOARD_SIZE_HIGHT    8
#define POSSIBLE_MOVES      8
#define INIT_ROW            0
#define INIT_COLUMN         0
#define TOURS               64

const int horizontal[POSSIBLE_MOVES] = { 2,  1, -1, -2, -2, -1, 1, 2 };
const int vertical[POSSIBLE_MOVES] = { -1, -2, -2, -1,  1,  2, 2, 1 };

void initBoard(unsigned int board[][BOARD_SIZE_WEDTH]);
bool isValidMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int moveNumber);
void moveTheKnight(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int moveNumber);
void printBoard(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[]);
unsigned int getPossibleMoves(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int possibleMoves[]);

int main(void)
{
    unsigned int board[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH] = { 0 };
    unsigned int position[3];
    unsigned int possibleMoves[POSSIBLE_MOVES] = { 0 };
    unsigned int totalPossibleMoves = 0;
    unsigned int result[TOURS] = { 0 };
    position[0] = INIT_ROW;
    position[1] = INIT_COLUMN;
    position[2] = 0;

    srand(time(NULL));
    unsigned int counter = 0;
    while (position[2] < TOURS)
    {
        position[0] = INIT_ROW;
        position[1] = INIT_COLUMN;
        position[2] = 0;
        initBoard(board);
        board[position[0]][position[1]] = ++position[2];
        totalPossibleMoves = getPossibleMoves(board, position, possibleMoves);
        while (totalPossibleMoves > 0)
        {
            unsigned int random = rand() % totalPossibleMoves;
            moveTheKnight(board, position, possibleMoves[random]);
            //printBoard(board, position);
            totalPossibleMoves = getPossibleMoves(board, position, possibleMoves);
        }
        result[position[2]-1]++;
        counter++;

        //printBoard(board, position);
        //printf("Total Square Visited = %u\n", position[2]);
        if (position[2] == TOURS)
        {
            printBoard(board, position);
            printf("Total Square Visited = %u\n", position[2]);
            getchar();
        }
    }   
    for (size_t i = 0; i < TOURS; i++)
    {
        printf("%-5u%u\n", i+1, result[i]);
    }
    printf("\nTotal Run = %u\n", counter);
}

unsigned int getPossibleMoves(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int possibleMoves[])
{
    unsigned int counter = 0;
    for (unsigned int i = 0; i < POSSIBLE_MOVES; i++)
    {
        if (isValidMove(board, position, i))
        {
            possibleMoves[counter] = i;
            counter++;
        }
    }
    return counter;
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

bool isValidMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int moveNumber)
{
    unsigned int row = position[0] + vertical[moveNumber];
    unsigned int column = position[1] + horizontal[moveNumber];

    if (row < 0 || row >= BOARD_SIZE_HIGHT ||
        column < 0 || column >= BOARD_SIZE_WEDTH ||
        board[row][column] != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void moveTheKnight(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int moveNumber)
{
    position[0] += vertical[moveNumber];
    position[1] += horizontal[moveNumber];
    board[position[0]][position[1]] = ++position[2];
}

void printBoard(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[])
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
            if (board[i][j] == position[2])
            {
                printf("|%3s ", "&*");
            }
            else if (board[i][j] == 0)
            {
                printf("|%3c ", ' ');
            }
            else
            {
                printf("|%3u ", board[i][j]);
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