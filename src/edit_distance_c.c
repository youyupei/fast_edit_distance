#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int edit_distance_c(char* word1, char* word2, int max_ed, int check_mat) {
    // This function is used to calculate the edit distance between two words
    // word1: the first word, which should be the shorter word
    // word2: the second word
    // max_ed: the maximum edit distance allowed
    // check_mat: whether to print the matrix
    assert(max_ed >= 0 && "the max_ed should be non-negative");

    if (strcmp(word1, word2) == 0) {
        return 0;
    }

    // stop if max ed allowed is 0 but word1 != word2
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
    int n_row = m + 1;// add one row as boundary row
    int start_col = (n_col + 1 +m-n)/2 -1 ;
    int end_col = (n_col + 1 +n-m)/2-1;

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
     

    free(dp);
    free(w2_idx_rel);
    free(init_score);
    free(max_ed_col);

    return result;
}

struct sub_edit_rst {
    int ed;
    int long_word_idx;
};

struct sub_edit_rst sub_edit_distance_c(char* word1, char* word2, int max_ed, int check_mat) {
    // This function is used to calculate the edit distance between two words
    // by allowing subsequence match after editing the shorter words.
    // word1: the first word, which should be the shorter word
    // word2: the second word
    // max_ed: the maximum edit distance allowed
    // check_mat: whether to print the matrix
    
    

    assert(max_ed >= 0 && "the max_ed should be non-negative");

    struct sub_edit_rst rst;
    rst.ed = max_ed+1;
    rst.long_word_idx = -1;
    int infi = max_ed * 10;
    int n1 = strlen(word1);
    int n2 = strlen(word2);
    assert(n1 <= n2 && "Put the shorter words first if the length is different");

    
    // Set the dimension of the matrix
    int bandwidth = n2 - n1 + 2* max_ed + 1; // the is the maximum width of the matrix needed
    int n_col = bandwidth + 2; // add two col as boundary col
    int n_row = n1 + 1;// add one row as boundary row
    int start_col[] = {max_ed + 1, n_col-1}; //0-based index, i.e. left inclusive, right exclusive
    int end_col[] = {1, n_col - max_ed - 1}; //0-based index, i.e. left inclusive, right exclusive

    // edit distance cost
    int cost_indel = 1;
    int cost_sub = 1;

    // Initialisation
    int* dp = (int*)calloc(n_row * n_col, sizeof(int));
    int* w2_idx_rel = (int*)malloc(n_col * sizeof(int));
    //int* max_ed_col = (int*)malloc(n_col * sizeof(int));

        // Initialise the first row
    for (int i = 0; i < n_col; i++) {
        w2_idx_rel[i] = i - start_col[0];
        if (i >= start_col[0] && i < start_col[1]) {
            dp[i] = 0; // no penalty for starting at these cols
        } else {
            dp[i] = -w2_idx_rel[i];
        }
        //max_ed_col[i] = max_ed - dp[i];
    }
        // Initialise the first and last cols
    for (int i = 0; i < n_row; i++) {
        dp[i * n_col] = infi;
        dp[i * n_col + n_col - 1] = infi;
    }
    
    // Start Dynamic programming
    int match, w_idx;
    for (int r = 1; r < n_row; r++) {
        w_idx = r - 1;

        for (int c = 1; c < n_col - 1; c++) {  // do not update boundary columns
            if (w_idx + c - start_col[0] < 0 || w_idx + c - start_col[0] >= n2) {
                match = 0;
            } else {
                match = (word1[w_idx] == word2[w_idx + c - start_col[0]]) ? 0 : cost_sub;
            }

            dp[r * n_col + c] = fmin(
                fmin(dp[(r) * n_col + (c - 1)] + cost_indel, dp[(r - 1) * n_col + c] + match),
                dp[(r - 1) * n_col + (c + 1)] + cost_indel
            );
        }

        int all_greater = 1;
        // Check if all the values in the last row and target cols are greater than max_ed
        for (int i = end_col[0]; i < end_col[1]; i++) {
            if (dp[r * n_col + i] <= max_ed) {
                all_greater = 0;
                break;
            }
        }

        if (all_greater) {
            free(dp);
            free(w2_idx_rel);
            //free(max_ed_col);
            return rst;
        }
    }

    // Print the matrix if required
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

    // Find the minimum value in the last row between the target cols
    int min = infi;
    int minColumn = end_col[0];

    for (int j = end_col[0]; j < end_col[1]; j++) {
        if (dp[(n_row-1) * n_col + j] < min) {
            min = dp[(n_row-1) * n_col + j];
            minColumn = j;
        }
    }


    free(dp);
    free(w2_idx_rel);
    //free(init_score);
    //free(max_ed_col);
    rst.ed = min;
    rst.long_word_idx = minColumn-start_col[0] + n1 - 1;
    return rst;
}

int main() {
    // Test inputs
    int max_ed = 1;
    char word1[] = "ABCDABCD";
    char word2[] = "eeABCDACee";
    printf("max_ed: %d\n", max_ed);

    // Call the edit_distance_c function
    int result_ed = edit_distance_c(word1, word2, max_ed, 1);
    struct sub_edit_rst result_sub = sub_edit_distance_c(word1, word2, max_ed, 1);

    // Print the result
    printf("Edit distance: %d\n", result_ed);
    printf("Sub edit distance: %d, Long word end idx: %d\n", result_sub.ed, result_sub.long_word_idx);

    return 0;
}