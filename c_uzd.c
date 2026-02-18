#include <stdio.h>
#include <stdlib.h>


long long get_number(void) {
    char input[100];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        exit(1);
    }

    if (input[0] == '\n') {
        printf("Empty input\n");
        exit(1);
    }

    int is_negative = 0;
    if (input[0] == '-') {
        is_negative = 1;
    }

    long long num = 0;
    for (int i = is_negative; input[i] != '\n'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid symbol: %c\n", input[i]);
            exit(1);
        }

        long long digit = input[i] - '0';
        num = num * 10 + digit;
    }

    if (is_negative) {
        return -num;
    }

    return num;
}

int main() {
    printf("Input x1: ");
    long long x1 = get_number();
    printf("Input y1: ");
    long long y1 = get_number();
    printf("Input x2: ");
    long long x2 = get_number();
    printf("Input y2: ");
    long long y2 = get_number();

    long long new_x = abs(x1 - x2);
    long long new_y = abs(y1 - y2);

    char board[new_x + 2][new_y + 2] = {0}; 
    long long moves = 1;
    board[0][0] = 1;

    int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};


    while (board[new_x][new_y] == 0) {
        for (int i = 0; i < new_x + 2; i++){
            for (int j = 0; j < new_y + 2; j++) {
                if (board[i][j] == moves) {
                    for (int k = 0; k < 8; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni >= 0 && ni < new_x + 2 && nj >= 0 && nj < new_y + 2 && board[ni][nj] == 0) {
                            board[ni][nj] = moves + 1;
                        }
                    }
                }
            }
        }
        moves++;
    }

    moves--;

    printf("Moves: %lld\n", moves);
    return 0;
}
