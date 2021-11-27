#include <stdbool.h>
#include <string.h>

int solution(int X, int A[], int N) {
    /**
     * Solution: Counter and a mark table
     * 
     * Pseudo Code:
     *   maker_table[X] = {false} // Initialize with all false
     *   counter = X
     *   for (i in A) {
     *     if (marker_table[A[i]] == false) {
     *       counter--
     *       matker_table[A[i]] = true
     *       if (counter == 0) {
     *          earliest_time_frog_jump = i
     *          break
     *       }
     *     }
     *   }
     *   return earliest_time_frog_jump
     *
     * Time Complexity:
     *   one for loop ~ linear = n => O(n0)
     * Memory Complexity:
     *   new array allocation ~ linear with inputs = n => O(n)
     */
    bool* marker_table = malloc ((X + 1) * sizeof(bool));
    memset (marker_table, 0, (X + 1) * sizeof(bool));
    int earliest_frog_jump_time = -1;

    for (int i = 0; i < N; i++) {
        if (marker_table[A[i]] == false) {
            marker_table[A[i]] = true;
            X--; /* Counter is used to avoid iterating over all the array */
            if (X == 0) {
                return i;
            }
        }
    }

    free(marker_table);
    return earliest_frog_jump_time;
}

