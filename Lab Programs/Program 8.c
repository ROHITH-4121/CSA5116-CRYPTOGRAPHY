
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char plain[100], cipher[27] = "";
    char key[] = "CIPHER";
    int used[26] = {0};
    int i, j = 0;

    for (i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (!used[ch - 'A']) {
            cipher[j++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (i = 0; i < 26; i++) {
        if (!used[i]) {
            cipher[j++] = 'A' + i;
        }
    }
    cipher[26] = '\0';

    printf("Plain alphabet : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    printf("Cipher alphabet: %s\n", cipher);

    printf("Enter plaintext: ");
    fgets(plain, sizeof(plain), stdin);

    printf("Encrypted text: ");
    for (i = 0; plain[i] != '\0'; i++) {
        char ch = toupper(plain[i]);

        if (ch >= 'A' && ch <= 'Z') {
            printf("%c", cipher[ch - 'A']);
        } else {
            printf("%c", plain[i]);
        }
    }

    printf("\n");
    return 0;
}
