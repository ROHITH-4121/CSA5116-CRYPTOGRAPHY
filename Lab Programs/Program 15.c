
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

double freq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

typedef struct {
    int key;
    double score;
    char text[MAX];
} Result;

int main() {
    char cipher[MAX];
    Result results[26], temp;
    int top, i, j, k;

    printf("Enter ciphertext: ");
    fgets(cipher, MAX, stdin);

    cipher[strcspn(cipher, "\n")] = '\0';

    printf("Enter number of top plaintexts (1-26): ");
    scanf("%d", &top);

    if (top < 1 || top > 26) {
        printf("Invalid number. Enter 1 to 26.\n");
        return 1;
    }

    for (k = 0; k < 26; k++) {
        int count[26] = {0};
        int total = 0;

        results[k].key = k;
        results[k].score = 0;

        for (i = 0; cipher[i] != '\0'; i++) {
            if (isalpha((unsigned char)cipher[i])) {
                int c = tolower((unsigned char)cipher[i]) - 'a';
                int p = (c - k + 26) % 26;

                results[k].text[i] = isupper((unsigned char)cipher[i])
                                      ? p + 'A' : p + 'a';

                count[p]++;
                total++;
            } else {
                results[k].text[i] = cipher[i];
            }
        }

        results[k].text[i] = '\0';

        if (total > 0) {
            for (j = 0; j < 26; j++) {
                results[k].score +=
                    count[j] * freq[j] / total;
            }
        }
    }

    for (i = 0; i < 25; i++) {
        for (j = i + 1; j < 26; j++) {
            if (results[j].score > results[i].score) {
                temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            }
        }
    }

    printf("\nTop %d possible plaintexts:\n", top);

    for (i = 0; i < top; i++) {
        printf("%d. Key = %d | Score = %.3f\n",
               i + 1, results[i].key, results[i].score);
        printf("   %s\n", results[i].text);
    }

    return 0;
}
