// correction.h
#include <string.h>
#include <strings.h>
#include <ctype.h>

#define MAX_WORDS 10001
#define WORD_LEN 64
#define BUFFER_SIZE 1024

char dictionary[MAX_WORDS][WORD_LEN];
int dict_size = 0;

void load_dictionary(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Dictionary open failed");
        exit(EXIT_FAILURE);
    }
    while (fscanf(file, "%s", dictionary[dict_size]) != EOF) {
        dict_size++;
    }
    fclose(file);
}

int levenshtein(const char *s1, const char *s2) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];
    for (int i = 0; i <= len1; i++) dp[i][0] = i;
    for (int j = 0; j <= len2; j++) dp[0][j] = j;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (tolower(s1[i - 1]) == tolower(s2[j - 1])) ? 0 : 1;
            int min = dp[i - 1][j] + 1;
            if (dp[i][j - 1] + 1 < min) min = dp[i][j - 1] + 1;
            if (dp[i - 1][j - 1] + cost < min) min = dp[i - 1][j - 1] + cost;
            dp[i][j] = min;
        }
    }
    return dp[len1][len2];
}

const char *auto_correct(const char *word) {
    for (int i = 0; i < dict_size; i++) {
        if (strcasecmp(word, dictionary[i]) == 0)
            return word;
    }
    int min_dist = 100;
    const char *closest = word;
    for (int i = 0; i < dict_size; i++) {
        int dist = levenshtein(word, dictionary[i]);
        if (dist < min_dist) {
            min_dist = dist;
            closest = dictionary[i];
        }
    }
    return closest;
}

void correct_message(const char *input, char *output) {
    char temp[BUFFER_SIZE];
    strcpy(temp, input);
    output[0] = '\0';

    char *word = strtok(temp, " ");
    while (word) {
        const char *corrected = auto_correct(word);
        strcat(output, corrected);
        strcat(output, " ");
        word = strtok(NULL, " ");
    }
}
