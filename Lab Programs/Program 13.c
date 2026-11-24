
#include <stdio.h>

int main() {
    int key[2][2] = {{3, 3}, {2, 5}};
    int plain[2][2] = {{1, 0}, {0, 1}};
    int cipher[2][2];

    printf("Chosen Plaintext Attack on Hill Cipher\n\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cipher[i][j] = 0;

            for (int k = 0; k < 2; k++) {
                cipher[i][j] += key[i][k] * plain[k][j];
            }

            cipher[i][j] %= 26;
        }
    }

    printf("Plaintext Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d ", plain[i][j]);
        printf("\n");
    }

    printf("\nCiphertext Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d ", cipher[i][j]);
        printf("\n");
    }

    printf("\nRecovered Key Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d ", cipher[i][j]);
        printf("\n");
    }

    return 0;
}
