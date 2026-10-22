#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char cipher[2000], key[128];
    int i;
    char c;

    for (i = 0; i < 128; i++)
        key[i] = '?';

    printf("Enter ciphertext:\n");
    fgets(cipher, sizeof(cipher), stdin);

    printf("Enter number of mappings: ");
    int n;
    scanf("%d", &n);

    printf("Enter ciphertext-symbol and plaintext-letter pairs:\n");

    for (i = 0; i < n; i++) {
        char from, to;
        scanf(" %c %c", &from, &to);
        key[(unsigned char)from] = to;
    }

    printf("\nDecrypted message:\n");

    for (i = 0; cipher[i] != '\0'; i++) {
        c = cipher[i];

        if (key[(unsigned char)c] != '?')
            putchar(key[(unsigned char)c]);
        else
            putchar(c);
    }

    return 0;
}