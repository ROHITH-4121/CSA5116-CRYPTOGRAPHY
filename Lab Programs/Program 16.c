
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define MAX 2000
#define TOP 10
#define RESTARTS 30
#define ITERATIONS 3000

const double english[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

const char *common[] = {
    "th","he","in","er","an","re","on","at","en","nd",
    "ti","es","or","te","of","ed","is","it","al","ar",
    "st","to","nt","ng","se","ha","as","ou","io","le",
    "ve","co","me","de","hi","ri","ro","ic","ne","ea",
    "ra","ce","li","ch","ll","be","ma","si","om","ur",
    "the","and","ing","ion","tio","ent","for","her",
    "tha","nth","int","ere","ter","est","ers","ati",
    "hat","ate","all","eth","hes","ver","his","oft",
    "ith","fth","sth","oth","res","ont","rea","not",
    NULL
};

typedef struct {
    char text[MAX];
    char key[26];
    double score;
} Candidate;

Candidate best[TOP];
int found = 0;

void shuffle(char key[]) {
    for (int i = 25; i > 0; i--) {
        int j = rand() % (i + 1);
        char t = key[i];
        key[i] = key[j];
        key[j] = t;
    }
}

void decrypt(const char cipher[], char plain[], const char key[]) {
    for (int i = 0; cipher[i]; i++) {
        if (isalpha((unsigned char)cipher[i])) {
            int c = tolower((unsigned char)cipher[i]) - 'a';
            char p = key[c];

            plain[i] = isupper((unsigned char)cipher[i])
                       ? toupper((unsigned char)p) : p;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[strlen(cipher)] = '\0';
}

double scoreText(const char text[]) {
    double score = 0.0;

    for (int i = 0; text[i]; i++) {
        if (isalpha((unsigned char)text[i])) {
            int c = tolower((unsigned char)text[i]) - 'a';
            score += log(english[c] / 100.0);
        }
    }

    for (int i = 0; text[i] && text[i + 1]; i++) {
        if (isalpha((unsigned char)text[i]) &&
            isalpha((unsigned char)text[i + 1])) {
            char pair[3] = {
                tolower((unsigned char)text[i]),
                tolower((unsigned char)text[i + 1]), '\0'
            };

            for (int j = 0; common[j]; j++) {
                if (strlen(common[j]) == 2 &&
                    strcmp(pair, common[j]) == 0) {
                    score += 1.5;
                    break;
                }
            }
        }
    }

    for (int i = 0; text[i]; i++) {
        if (!isalpha((unsigned char)text[i]))
            continue;

        char tri[4] = {0};
        int n = 0;

        for (int j = i; text[j] && n < 3; j++) {
            if (!isalpha((unsigned char)text[j]))
                break;
            tri[n++] = tolower((unsigned char)text[j]);
        }

        if (n == 3) {
            for (int j = 0; common[j]; j++) {
                if (strlen(common[j]) == 3 &&
                    strcmp(tri, common[j]) == 0) {
                    score += 4.0;
                    break;
                }
            }
        }
    }

    return score;
}

int duplicate(const char text[]) {
    for (int i = 0; i < found; i++)
        if (strcmp(best[i].text, text) == 0)
            return 1;
    return 0;
}

void saveCandidate(const char text[], const char key[],
                   double score) {
    if (duplicate(text))
        return;

    if (found == TOP && score <= best[found - 1].score)
        return;

    int pos = found;

    if (pos >= TOP)
        pos = TOP - 1;
    else
        found++;

    while (pos > 0 && best[pos - 1].score < score) {
        best[pos] = best[pos - 1];
        pos--;
    }

    strcpy(best[pos].text, text);
    strcpy(best[pos].key, key);
    best[pos].score = score;
}

int main(void) {
    char cipher[MAX], plain[MAX];
    char key[26], current[MAX];
    char currentKey[26], trialKey[26];
    int top;

    printf("Enter ciphertext:\n");
    if (!fgets(cipher, sizeof(cipher), stdin))
        return 1;

    cipher[strcspn(cipher, "\n")] = '\0';

    printf("How many possible plaintexts (1-10)? ");
    if (scanf("%d", &top) != 1 || top < 1 || top > TOP) {
        printf("Enter a number from 1 to 10.\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < 26; i++)
        key[i] = 'a' + i;

    for (int r = 0; r < RESTARTS; r++) {
        shuffle(key);
        strcpy(currentKey, key);
        decrypt(cipher, current, currentKey);

        double currentScore = scoreText(current);

        for (int step = 0; step < ITERATIONS; step++) {
            strcpy(trialKey, currentKey);

            int a = rand() % 26;
            int b = rand() % 26;

            char t = trialKey[a];
            trialKey[a] = trialKey[b];
            trialKey[b] = t;

            decrypt(cipher, plain, trialKey);
            double trialScore = scoreText(plain);

            double temperature =
                5.0 * (1.0 - (double)step / ITERATIONS) + 0.05;

            double difference = trialScore - currentScore;

            if (difference > 0 ||
                ((double)rand() / RAND_MAX) <
                exp(difference / temperature)) {
                strcpy(currentKey, trialKey);
                strcpy(current, plain);
                currentScore = trialScore;
            }

            saveCandidate(current, currentKey, currentScore);
        }
    }

    printf("\nTop %d possible plaintexts:\n\n", top);

    for (int i = 0; i < top && i < found; i++) {
        printf("%d. Score: %.2f\n", i + 1, best[i].score);
        printf("   Plaintext: %s\n", best[i].text);
        printf("   Key: %s\n\n", best[i].key);
    }

    printf("Attack completed.\n");
    return 0;
}
