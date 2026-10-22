#include <stdio.h>
#include <string.h>

int main() {
    char text[1000];
    int a, b, i, p, c, inv, found;

    printf("Enter ciphertext: ");
    fgets(text, sizeof(text), stdin);

    for (a = 1; a < 26; a++) {
        int x, y = 26;
        x = a;

        while (y != 0) {
            int r = x % y;
            x = y;
            y = r;
        }

        if (x != 1)
            continue;

        for (b = 0; b < 26; b++) {
            inv = -1;

            for (i = 0; i < 26; i++) {
                if ((a * i) % 26 == 1) {
                    inv = i;
                    break;
                }
            }

            if (inv == -1)
                continue;

            printf("\na = %d, b = %d: ", a, b);

            for (i = 0; text[i] != '\0'; i++) {
                if (text[i] >= 'A' && text[i] <= 'Z') {
                    c = text[i] - 'A';
                    p = (inv * (c - b + 26)) % 26;
                    printf("%c", p + 'A');
                } else if (text[i] >= 'a' && text[i] <= 'z') {
                    c = text[i] - 'a';
                    p = (inv * (c - b + 26)) % 26;
                    printf("%c", p + 'a');
                } else {
                    printf("%c", text[i]);
                }
            }
        }
    }

    return 0;
}