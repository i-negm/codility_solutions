/**
 * URL : https://app.codility.com/demo/results/training9VPQ3K-JF6/
 */

#include <string.h>

#define SOLUTION_BRANCHING_BETWEEN_INC_MAX_INSTRUCTIONS 0
#define SOLUTION_BY_SETTING_NEW_PENDING_OFFSET_FOR_MAX_TO_UPDATE_LATER 1

void print_arr(int A[], int N) {
    printf("[");
    for (int i = 0; i < N; i++) {
        printf("%d%s", A[i], (i == N-1? "" :","));
    }
    printf("]\n");
}

struct Results solution(int N, int A[], int M) {
    struct Results result;

    int* counters = malloc (N * sizeof(int));
    memset (counters, 0, N * sizeof(int));

#if SOLUTION_BY_SETTING_NEW_PENDING_OFFSET_FOR_MAX_TO_UPDATE_LATER
    /**
     * Solution: Max instruction , will reset the offset for all the counters
     *
     * Time complexity:
     *   for loop for commands + for loop for updating the remaining = n+n = 2n => O(n)
     * Memory complexity:
     *   for increasing size of input the memory allocation is linear => O(n)
     */
     int current_max = 0;
    int start_line = 0;

    for (int i = 0; i < M; i++) {
        int command = A[i];
        if (command > N) {
            start_line = current_max;
        } else {
            if (start_line <= counters[command - 1]) {
                counters[command - 1]++;
            } else {
                counters[command - 1] = start_line + 1;
            }
            if (counters[command - 1] > current_max) {
                current_max = counters[command - 1];
            }
        }
    }

    for (int j = 0; j < N; j++) {
        if(counters[j] < start_line) {
            counters[j] = start_line;
        }
    }

#endif /*SOLUTION_BY_SETTING_NEW_PENDING_OFFSET_FOR_MAX_TO_UPDATE_LATER*/

#if SOLUTION_BRANCHING_BETWEEN_INC_MAX_INSTRUCTIONS
    /**
     * Solution: Branching between increment and max instructions.
     *   max_so_far = 0
     *   counters[N] = {0}
     *   for (i in A)
     *     if (command[i] == N+1 ) // Max increase
     *       max_counters(max_so_far)
     *     else
     *       increase(command[i])
     *       if (counters[command[i] - 1] > max_so_far)
     *         max_so_far = counters[command[i] - 1]
     *   return { C = counters, L = N}
     * Time complexity:
     *   for each command * for each element  = n*n => O(n^2)
     * Memory complexity:
     *   for increasing size of input the memory allocation is linear => O(n)
     */
    int max_so_far = 0;
    for (int i = 0; i < M; i++) { /* For each command */
        if (A[i] == N+1) { /* Max instruction */
            for(int j = 0; j < N; j++)
                counters[j] = max_so_far;
        } else { /* Increment instructions */
            counters [A[i] - 1]++;
            if (counters[A[i] - 1] > max_so_far) {
                max_so_far = counters[A[i] - 1];
            }
        }
    }
#endif /*SOLUTION_BRANCHING_BETWEEN_INC_MAX_INSTRUCTIONS*/
    result.C = counters;
    result.L = N;
    return result;
}
