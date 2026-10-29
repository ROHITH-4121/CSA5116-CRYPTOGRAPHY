
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void findPosition(char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char text[200], a, b;
    int i, n = 0, r1, c1, r2, c2;

    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i])) {
            char ch = toupper((unsigned char)message[i]);
            if (ch == 'J')
                ch = 'I';
            text[n++] = ch;
        }
    }

    text[n] = '\0';

    printf("Plaintext: %s\n", message);
    printf("Encrypted text: ");

    for (i = 0; i < n; i += 2) {
        a = text[i];

        if (i + 1 < n)
            b = text[i + 1];
        else
            b = 'X';

        if (a == b) {
            b = 'X';
            i--;
        }

        findPosition(a, &r1, &c1);
        findPosition(b, &r2, &c2);

        if (r1 == r2) {
            printf("%c%c",
                matrix[r1][(c1 + 1) % 5],
                matrix[r2][(c2 + 1) % 5]);
        } else if (c1 == c2) {
            printf("%c%c",
                matrix[(r1 + 1) % 5][c1],
                matrix[(r2 + 1) % 5][c2]);
        } else {
            printf("%c%c",
                matrix[r1][c2],
                matrix[r2][c1]);
        }
    }

    printf("\n");
    return 0;
}
