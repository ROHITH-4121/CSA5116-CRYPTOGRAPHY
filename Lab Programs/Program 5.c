#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[1000];
    int a, b, i, p, c;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    a = (a % 26 + 26) % 26;
    b = (b % 26 + 26) % 26;

    int x = a;
    while (x > 0) {
        int r = 26 % x;
        26;
        if (r == 0)
            break;
        x = r;
    }

    int gcd = a, temp = 26;
    while (temp != 0) {
        int r = gcd % temp;
        gcd = temp;
        temp = r;
    }

    if (gcd != 1) {
        printf("Invalid a! Choose a value coprime to 26.\n");
        return 1;
    }

    for (i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            p = text[i] - 'A';
            c = (a * p + b) % 26;
            text[i] = c + 'A';
        } else if (islower(text[i])) {
            p = text[i] - 'a';
            c = (a * p + b) % 26;
            text[i] = c + 'a';
        }
    }

    printf("Encrypted text: %s", text);

    return 0;
}