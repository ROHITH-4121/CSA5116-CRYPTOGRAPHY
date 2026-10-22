#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char key[100], text[1000], matrix[5][5];
    int used[26] = {0};
    int i, j, r, c, k = 0;

    used['J' - 'A'] = 1;

    printf("Enter keyword: ");
    scanf("%99s", key);

    printf("Enter plaintext: ");
    scanf("%999s", text);

    for (i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            matrix[k / 5][k % 5] = 'A' + i;
            k++;
        }
    }

    printf("\nPlayfair Matrix:\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    char plain[1000];
    int n = 0;

    for (i = 0; text[i] != '\0'; i++) {
        char ch = toupper(text[i]);
        if (ch >= 'A' && ch <= 'Z') {
            if (ch == 'J')
                ch = 'I';
            plain[n++] = ch;
        }
    }
    plain[n] = '\0';

    char prepared[2000];
    int p = 0;

    for (i = 0; i < n; i++) {
        prepared[p++] = plain[i];

        if (i + 1 < n && plain[i] == plain[i + 1])
            prepared[p++] = 'X';
    }

    if (p % 2 != 0)
        prepared[p++] = 'X';

    prepared[p] = '\0';

    printf("\nEncrypted text: ");

    for (i = 0; i < p; i += 2) {
        int r1 = 0, c1 = 0, r2 = 0, c2 = 0;

        for (r = 0; r < 5; r++) {
            for (c = 0; c < 5; c++) {
                if (matrix[r][c] == prepared[i]) {
                    r1 = r;
                    c1 = c;
                }
                if (matrix[r][c] == prepared[i + 1]) {
                    r2 = r;
                    c2 = c;
                }
            }
        }

        if (r1 == r2) {
            printf("%c%c", matrix[r1][(c1 + 1) % 5],
                           matrix[r2][(c2 + 1) % 5]);
        } else if (c1 == c2) {
            printf("%c%c", matrix[(r1 + 1) % 5][c1],
                           matrix[(r2 + 1) % 5][c2]);
        } else {
            printf("%c%c", matrix[r1][c2], matrix[r2][c1]);
        }
    }

    printf("\n");
    return 0;
}