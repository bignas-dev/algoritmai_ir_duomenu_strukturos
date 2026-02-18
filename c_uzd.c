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

    long long dx = llabs(x1 - x2);
    long long dy = llabs(y1 - y2);

    if (dx < dy) {
        long long temp = dx;
        dx = dy;
        dy = temp;
    }

    long long m;

    if (dx == 1 && dy == 0) {
        m = 3;
    } else if (dx == 2 && dy == 2) {
        m = 4;
    } else {
        long long lower1 = (dx + 1) / 2;
        long long lower2 = (dx + dy + 2) / 3;
        m = (lower1 > lower2) ? lower1 : lower2;

        if ((m % 2) != ((dx + dy) % 2)) {
            m++;
        }
    }
    printf("Moves: %lld\n", m);
    return 0;
}
