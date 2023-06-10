#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int edit_distance_c(char* word1, char* word2, int max_ed, int check_mat) {
    assert(max_ed >= 0 && "the max_ed should be non-negative");

    if (strcmp(word1, word2) == 0) {
        return 0;
    }

    if (max_ed == 0) {
        return max_ed+1;  // max_ed + 1 for exceed maximum
    }

    int infi = max_ed * 10;
    int m = strlen(word1);
    int n = strlen(word2);
    assert(m <= n && "Put the shorter words first if the length is different");
    int bandwidth = (max_ed-n+m)/ 2 * 2 + n - m + 1; // the is the maximum width of the matrix needed
    //printf("%d\n", bandwidth);
    int n_col = bandwidth + 2; // add two col as boundary col
    int n_row = m + 1;// add one row as boundary col
    int start_col = (n_col + 1 +m-n)/2;
    int end_col = (n_col + 1 +n-m)/2;

    // edit distance
    int cost_indel = 1;
    int cost_sub = 1;

    // Initialisation
    int* dp = (int*)calloc(n_row * n_col, sizeof(int));
    int* w2_idx_rel = (int*)malloc(n_col * sizeof(int));
    int* init_score = (int*)malloc(n_col * sizeof(int));
    int* max_ed_col = (int*)malloc(n_col * sizeof(int));

    for (int i = 0; i < n_col; i++) {
        w2_idx_rel[i] = i - start_col;
        init_score[i] = abs(w2_idx_rel[i]);
        dp[i] = abs(w2_idx_rel[i]);
        max_ed_col[i] = max_ed - init_score[i];
    }

    for (int i = 0; i < n_row; i++) {
        dp[i * n_col] = infi;
        dp[i * n_col + n_col - 1] = infi;
    }
    

    // printf("w2_idx_rel: ");
    // for (int i = 0; i < n_col; i++) {
    //     printf("%d ", w2_idx_rel[i]);
    // }
    // printf("\n");

    // printf("init_score: ");
    // for (int i = 0; i < n_col; i++) {
    //     printf("%d ", init_score[i]);
    // }
    // printf("\n");

    // printf("max_ed_col: ");
    // for (int i = 0; i < n_col; i++) {
    //     printf("%d ", max_ed_col[i]);
    // }
    // printf("\n");

    int match, w_idx;

    for (int r = 1; r < n_row; r++) {
        w_idx = r - 1;

        for (int c = 1; c < n_col - 1; c++) {  // do not update boundary columns
            if (w_idx + c - start_col < 0 || w_idx + c - start_col >= n) {
                match = 0;
            } else {
                match = (word1[w_idx] == word2[w_idx + c - start_col]) ? 0 : cost_sub;
            }

            dp[r * n_col + c] = fmin(
                fmin(dp[(r) * n_col + (c - 1)] + cost_indel, dp[(r - 1) * n_col + c] + match),
                dp[(r - 1) * n_col + (c + 1)] + cost_indel
            );
        }

        int all_greater = 1;

        for (int i = 0; i < n_col; i++) {
            if (dp[r * n_col + i] <= max_ed_col[i]) {
                all_greater = 0;
                break;
            }
        }

        if (all_greater) {
            free(dp);
            free(w2_idx_rel);
            free(init_score);
            free(max_ed_col);
            return max_ed+1;
        }
    }

    if (check_mat) {
        printf("dp:\n");
        for (int i = 0; i < n_row; i++) {
            for (int j = 0; j < n_col; j++) {
                printf("%d ", dp[i * n_col + j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    int result = dp[(n_row-1) * n_col + end_col];
    
    // for (int i = 0; i < n_col; i++) {
    //     if (dp[(n_row-1) * n_col + i] + init_score[i] < result) {
    //         result = dp[(n_row-1) * n_col + i] + init_score[i]; // Update the minimum value
    //     }
    // }

    //int result = fmin(dp[m * n_col + (c - 1)] + cost_indel + match, dp[(r - 1) * n_col + c] + match)       

    free(dp);
    free(w2_idx_rel);
    free(init_score);
    free(max_ed_col);

    return result;
}

int main() {
    // Test inputs
    int max_ed = 16;
    char word1[] = "ABCD1234ABCD1234ABCDABCD";
    char word2[] = "ABCD1234XXXXABCD1234ABCDABCD";

    // Call the edit_distance_c function
    int result = edit_distance_c(word1, word2, max_ed, 1);

    // Print the result
    printf("Edit distance: %d\n", result);

    return 0;
}