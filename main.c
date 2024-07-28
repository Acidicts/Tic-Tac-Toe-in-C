#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';
char winner = ' ';
char response;

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner();

int main(void) {
    response = 'Y';

    do {
        resetBoard();
        winner = ' ';

        while (winner == ' ' && checkFreeSpaces() > 0) {
            printBoard();

            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }

        printBoard();
        printWinner();
        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response);  // Note the space before %c to consume any leftover newline character
        response = toupper(response);

    } while (response == 'Y');

    return 0;
}

void resetBoard() {
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkFreeSpaces() {
    int freeSpaces = 9;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }

    return freeSpaces;
}

void playerMove() {
    int x, y;

    do {
        printf("Enter row #1-3: ");
        scanf("%d", &x);
        x--;
        printf("Enter column #1-3: ");
        scanf("%d", &y);
        y--;

        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') {
            printf("Invalid Move!\n");
        } else {
            board[x][y] = PLAYER;
            break;
        }
    } while (1);
}

void computerMove() {
    srand(time(0));
    int x, y;

    if (checkFreeSpaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }
    return ' ';
}

void printWinner() {
    if (winner == PLAYER) {
        printf("You Win!");
    } else if (winner == COMPUTER) {
        printf("You Lose!");
    } else {
        printf("It's a tie!");
    }
}