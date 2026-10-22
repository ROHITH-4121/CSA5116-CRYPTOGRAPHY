#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[1000], key[1000];
    int i, j = 0, k;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    scanf("%999s", key);

    int len = strlen(key);

    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            k = toupper(key[j % len]) - 'A';

            if (isupper(text[i]))
                text[i] = (text[i] - 'A' + k) % 26 + 'A';
            else
                text[i] = (text[i] - 'a' + k) % 26 + 'a';

            j++;
        }
    }

    printf("Encrypted text: %s", text);

    return 0;
}