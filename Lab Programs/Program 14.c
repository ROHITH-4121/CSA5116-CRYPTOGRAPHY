
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plain1[] = "send more money";
    char plain2[] = "cash not needed";
    char cipher[100];
    int key1[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key2[100];
    int i, j = 0;

    printf("One-Time Pad Vigenere Cipher\n\n");

    printf("Plaintext: %s\n", plain1);
    printf("Ciphertext: ");

    for (i = 0; plain1[i] != '\0'; i++) {
        if (plain1[i] == ' ') {
            cipher[i] = ' ';
            printf(" ");
        } else {
            int p = tolower(plain1[i]) - 'a';
            int c = (p + key1[j]) % 26;
            cipher[i] = c + 'a';
            printf("%c", cipher[i]);
            j++;
        }
    }
    cipher[i] = '\0';

    printf("\n\nTarget plaintext: %s\n", plain2);
    printf("New key stream: ");

    j = 0;
    for (i = 0; plain2[i] != '\0'; i++) {
        if (plain2[i] == ' ') {
            printf(" ");
        } else {
            int c = tolower(cipher[i]) - 'a';
            int p = tolower(plain2[i]) - 'a';
            key2[j] = (c - p + 26) % 26;
            printf("%d ", key2[j]);
            j++;
        }
    }

    printf("\n");
    return 0;
}
