#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[1000], key[27];
    int i;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the 26-letter substitution key: ");
    scanf("%26s", key);

    if (strlen(key) != 26) {
        printf("Invalid key! Enter exactly 26 letters.\n");
        return 1;
    }

    for (i = 0; i < 26; i++) {
        key[i] = toupper(key[i]);

        if (key[i] < 'A' || key[i] > 'Z') {
            printf("Invalid key! Use only alphabets.\n");
            return 1;
        }

        for (int j = 0; j < i; j++) {
            if (key[i] == key[j]) {
                printf("Invalid key! Letters must be unique.\n");
                return 1;
            }
        }
    }

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = key[text[i] - 'A'];
        } else if (islower(text[i])) {
            text[i] = tolower(key[text[i] - 'a']);
        }
    }

    printf("Encrypted message: %s", text);

    return 0;
}