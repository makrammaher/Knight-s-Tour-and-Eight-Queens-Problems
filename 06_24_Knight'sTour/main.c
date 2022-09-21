#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<Windows.h>


#define BOARD_SIZE_WEDTH    8
#define BOARD_SIZE_HIGHT    8
#define POSSIBLE_MOVES      8
#define currentRow position[0]
#define currentColumn position[1]
#define squareVisited position[2]


void initAccessibilty(unsigned int accessibility[][BOARD_SIZE_WEDTH], unsigned int board[][BOARD_SIZE_WEDTH]);
void initBoard(unsigned int board[][BOARD_SIZE_WEDTH]);
bool isValidMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int moveNumber);
void moveTheKnight(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int accessibility[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int moveNumber);
void printBoard(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[]);
void printAccessibilty(unsigned int accessibility[][BOARD_SIZE_WEDTH]);
unsigned int possibleMoves(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int accessibility[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int possibleMoveAccessiblilty[][2]);
unsigned int bestPossibleMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int accessibility[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int answer[], unsigned int depth);
void reduceAccessibilty(unsigned int board[][BOARD_SIZE_WEDTH], int accessibility[][BOARD_SIZE_WEDTH], unsigned int position[]);

const int horizontal[POSSIBLE_MOVES] = { 2,  1, -1, -2, -2, -1, 1, 2 };
const int vertical[POSSIBLE_MOVES] = { -1, -2, -2, -1,  1,  2, 2, 1 };

int main(void)
{
    unsigned int accessibility[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH] = { 0 };
    unsigned int board[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH] = { 0 };
    unsigned int possibleMoveAccessiblilty[POSSIBLE_MOVES][2] = { 0 };
    unsigned int position[3];

    //Current Position

    for (unsigned int i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (unsigned int j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            //init
            initBoard(board);
            squareVisited = 0;
            currentRow = i;
            currentColumn = j;
            initAccessibilty(accessibility,board);
            board[currentRow][currentColumn] = ++squareVisited;
            reduceAccessibilty(board, accessibility, position);


            if (i == 1 && j == 10)
            {
                j = 10;
            }

            size_t possiblesMoves = possibleMoves(board, accessibility, position, possibleMoveAccessiblilty);
            

            while (possiblesMoves != 0)
            {

                unsigned int answer[2] = { 0 };
                bestPossibleMove(board, accessibility, position, answer,2);
                /*unsigned int bestMove;
                unsigned int bestAccessibilty = 9;
                for (size_t i = 0; i < possiblesMoves; i++)
                {
                    if (possibleMoveAccessiblilty[i][1] < bestAccessibilty)
                    {
                        bestAccessibilty = possibleMoveAccessiblilty[i][1];
                        bestMove = possibleMoveAccessiblilty[i][0];
                    }
                }*/

                moveTheKnight(board, accessibility, position, answer[0]);
                possiblesMoves = possibleMoves(board, accessibility, position, possibleMoveAccessiblilty);

                printBoard(board, position);
                Sleep(100);
                //puts("");
                //printAccessibilty();
                //printf("Total Square Visited = %u\n", squareVisited);
                //getchar();

            }
            printBoard(board, position);
            //puts("");
            //printAccessibilty();
            printf("Total Square Visited = %u\n", squareVisited);
            getchar();
        }
    }

}


void initAccessibilty(unsigned int accessibility[][BOARD_SIZE_WEDTH], unsigned int board[][BOARD_SIZE_WEDTH])
{

    for (size_t i = 0; i < BOARD_SIZE_HIGHT; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            accessibility[i][j] = 0;
            for (unsigned int k = 0; k < POSSIBLE_MOVES; k++)
            {

                unsigned int row = i + vertical[k];
                unsigned int column = j + horizontal[k];
                if (!(row < 0 || row >= BOARD_SIZE_HIGHT ||
                    column < 0 || column >= BOARD_SIZE_WEDTH ||
                    board[row][column] != 0))
                {
                    accessibility[i][j]++;

                }
            }
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

bool isValidMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int moveNumber)
{
    unsigned int row = currentRow + vertical[moveNumber];
    unsigned int column = currentColumn + horizontal[moveNumber];

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

void moveTheKnight(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int accessibility[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int moveNumber)
{
    currentRow += vertical[moveNumber];
    currentColumn += horizontal[moveNumber];
    board[currentRow][currentColumn] = ++squareVisited;
    reduceAccessibilty(board, accessibility, position);
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
            if (board[i][j] == squareVisited)
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

void printAccessibilty(unsigned int accessibility[][BOARD_SIZE_WEDTH])
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
            printf("|%3d ", accessibility[i][j]);
        }
        puts("|");
        for (size_t j = 0; j < BOARD_SIZE_WEDTH; j++)
        {
            printf("%s", "|----");
        }
        puts("|");
    }
}

unsigned int possibleMoves(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int accessibility[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int possibleMoveAccessiblilty[][2])
{
    unsigned int totalPossibleMoves = 0;
    for (unsigned int i = 0; i < POSSIBLE_MOVES; i++)
    {
        if (isValidMove(board, position,i))
        {
            unsigned int row = currentRow + vertical[i];
            unsigned int column = currentColumn + horizontal[i];
            possibleMoveAccessiblilty[totalPossibleMoves][0] = i;
            possibleMoveAccessiblilty[totalPossibleMoves][1] = accessibility[row][column];
            totalPossibleMoves++;
        }
    }
    return totalPossibleMoves;
}


unsigned int bestPossibleMove(unsigned int board[][BOARD_SIZE_WEDTH], unsigned int accessibility[][BOARD_SIZE_WEDTH], unsigned int position[], unsigned int answer[], unsigned int depth)
{
    unsigned int totalPossibleMoves = 0;
    unsigned int possibleMoveAccessiblilty[POSSIBLE_MOVES][2] = { 0 };

    for (unsigned int i = 0; i < POSSIBLE_MOVES; i++)
    {
        if (isValidMove(board, position, i))
        {
            unsigned int row = currentRow + vertical[i];
            unsigned int column = currentColumn + horizontal[i];
            possibleMoveAccessiblilty[totalPossibleMoves][0] = i;
            possibleMoveAccessiblilty[totalPossibleMoves][1] = accessibility[row][column];
            totalPossibleMoves++;
        }
    }

    //sort by accessibilty if total possible moves > 1
    if (totalPossibleMoves > 1)
    {
        for (unsigned int pass = 1; pass < totalPossibleMoves; pass++)
        {
            for (size_t i = 0; i < totalPossibleMoves - 1; i++)
            {
                if (possibleMoveAccessiblilty[i][1] > possibleMoveAccessiblilty[i + 1][1])
                {
                    unsigned int holdMove, holdAccessibility;
                    holdMove = possibleMoveAccessiblilty[i][0];
                    holdAccessibility = possibleMoveAccessiblilty[i][1];

                    possibleMoveAccessiblilty[i][0] = possibleMoveAccessiblilty[i + 1][0];
                    possibleMoveAccessiblilty[i][1] = possibleMoveAccessiblilty[i + 1][1];

                    possibleMoveAccessiblilty[i + 1][0] = holdMove;
                    possibleMoveAccessiblilty[i + 1][1] = holdAccessibility;
                }
            }
        }
        
        //assume the best is the first one
        size_t bestIndex = 0;
        if (possibleMoveAccessiblilty[1][1] == possibleMoveAccessiblilty[bestIndex][1])
        {   
            for (unsigned int i = 1; i < totalPossibleMoves; i++)
            {
                if (possibleMoveAccessiblilty[i][1] == possibleMoveAccessiblilty[bestIndex][1])
                {
                    unsigned int fakeBoard[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH];
                    unsigned int fakeAccessibilty[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH];
                    unsigned int fakeBoard2[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH];
                    unsigned int fakeAccessibilty2[BOARD_SIZE_HIGHT][BOARD_SIZE_WEDTH];
                    unsigned int fakeposition[3];
                    fakeposition[0] = position[0];
                    fakeposition[1] = position[1];
                    fakeposition[2] = position[2];
                    unsigned int fakeposition2[3];
                    fakeposition2[0] = position[0];
                    fakeposition2[1] = position[1];
                    fakeposition2[2] = position[2];
                    for (size_t a = 0; a < BOARD_SIZE_HIGHT; a++)
                    {
                        for (size_t b = 0; b < BOARD_SIZE_WEDTH; b++)
                        {
                            fakeBoard[a][b] = board[a][b];
                            fakeAccessibilty[a][b] = accessibility[a][b];
                            fakeBoard2[a][b] = board[a][b];
                            fakeAccessibilty2[a][b] = accessibility[a][b];
                        }
                    }
                    
                    unsigned int dep = 1;
                    unsigned int answer[2] = { 0 };
                    unsigned int answer2[2] = { 0 };
                    moveTheKnight(fakeBoard, fakeAccessibilty, fakeposition, possibleMoveAccessiblilty[bestIndex][0]);
                    moveTheKnight(fakeBoard2, fakeAccessibilty2, fakeposition2, possibleMoveAccessiblilty[i][0]);
                    while (answer[1] == answer2[1] && depth > dep)
                    {
                        dep++;
                        unsigned int pMoves = bestPossibleMove(fakeBoard, fakeAccessibilty, fakeposition, answer, depth-1);
                        unsigned int pMoves2 = bestPossibleMove(fakeBoard2, fakeAccessibilty2, fakeposition2, answer2, depth-1);
                        moveTheKnight(fakeBoard, fakeAccessibilty, fakeposition, answer[0]);
                        moveTheKnight(fakeBoard2, fakeAccessibilty2, fakeposition2, answer2[0]);
                    }
                    if (answer2[1] < answer[1])
                    {
                        bestIndex = i;
                    }

                }
                else
                {
                    break;
                }
                
            }
            answer[0] = possibleMoveAccessiblilty[bestIndex][0];
            answer[1] = possibleMoveAccessiblilty[bestIndex][1];
            return totalPossibleMoves;
        }
        else
        {
            answer[0] = possibleMoveAccessiblilty[0][0];
            answer[1] = possibleMoveAccessiblilty[0][1];
            return totalPossibleMoves;
        }
    }
    else if(totalPossibleMoves == 1)
    {
        answer[0] = possibleMoveAccessiblilty[0][0];
        answer[1] = possibleMoveAccessiblilty[0][1];
        return totalPossibleMoves;
    }
    else
    {
        return totalPossibleMoves;
    }
}



void reduceAccessibilty(unsigned int board[][BOARD_SIZE_WEDTH], int accessibility[][BOARD_SIZE_WEDTH], unsigned int position[])
{
    accessibility[currentRow][currentColumn] = 0;
    for (unsigned int i = 0; i < POSSIBLE_MOVES; i++)
    {
        if (isValidMove(board, position,i))
        {
            //reduce
            unsigned int row = currentRow + vertical[i];
            unsigned int column = currentColumn + horizontal[i];
            if(accessibility[row][column] > 0)
                accessibility[row][column]--;
        }
    }
}
