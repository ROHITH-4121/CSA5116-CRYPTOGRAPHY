
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(char key[]) {
    int used[26] = {0};
    int i, j, k = 0;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i] != '\0'; i++) {
        ch = toupper(key[i]);

        if (ch < 'A' || ch > 'Z')
            continue;

        if (ch == 'J')
            ch = 'I';

        if (!used[ch - 'A']) {
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
}

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

void decrypt(char text[]) {
    int i, r1, c1, r2, c2;
    char a, b;

    for (i = 0; text[i] != '\0'; i++) {
        if (!isalpha((unsigned char)text[i]))
            continue;

        text[i] = toupper((unsigned char)text[i]);

        if (text[i] == 'J')
            text[i] = 'I';
    }

    for (i = 0; text[i] != '\0'; i += 2) {
        if (!isalpha((unsigned char)text[i]))
            continue;

        if (!isalpha((unsigned char)text[i + 1]))
            break;

        a = text[i];
        b = text[i + 1];

        findPosition(a, &r1, &c1);
        findPosition(b, &r2, &c2);

        if (r1 == r2) {
            a = matrix[r1][(c1 + 4) % 5];
            b = matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            a = matrix[(r1 + 4) % 5][c1];
            b = matrix[(r2 + 4) % 5][c2];
        } else {
            a = matrix[r1][c2];
            b = matrix[r2][c1];
        }

        printf("%c%c", a, b);
    }

    printf("\n");
}

int main() {
    char key[100];
    char cipher[] =
        "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFI"
        "WTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEY"
        "CUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";

    printf("Enter Playfair keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    generateMatrix(key);

    printf("\nPlayfair Key Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    printf("\nDecrypted message:\n");
    decrypt(cipher);

    return 0;
}
