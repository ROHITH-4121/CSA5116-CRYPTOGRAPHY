
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char message[] =
        "meet me at the usual place at ten rather than eight oclock";
    char plain[200], cipher[200], decrypted[200];
    int key[2][2] = {{9, 4}, {5, 7}};
    int inv[2][2] = {{5, 12}, {15, 25}};
    int i, n = 0, a, b, c1, c2;

    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha((unsigned char)message[i])) {
            plain[n++] = toupper((unsigned char)message[i]);
        }
    }

    if (n % 2 != 0)
        plain[n++] = 'X';

    plain[n] = '\0';

    printf("Plaintext: %s\n", plain);

    for (i = 0; i < n; i += 2) {
        a = plain[i] - 'A';
        b = plain[i + 1] - 'A';

        c1 = (key[0][0] * a + key[0][1] * b) % 26;
        c2 = (key[1][0] * a + key[1][1] * b) % 26;

        cipher[i] = c1 + 'A';
        cipher[i + 1] = c2 + 'A';
    }
    cipher[n] = '\0';

    printf("\nEncrypted ciphertext: %s\n", cipher);

    for (i = 0; i < n; i += 2) {
        a = cipher[i] - 'A';
        b = cipher[i + 1] - 'A';

        c1 = (inv[0][0] * a + inv[0][1] * b) % 26;
        c2 = (inv[1][0] * a + inv[1][1] * b) % 26;

        decrypted[i] = c1 + 'A';
        decrypted[i + 1] = c2 + 'A';
    }
    decrypted[n] = '\0';

    printf("Decrypted plaintext: %s\n", decrypted);

    return 0;
}
