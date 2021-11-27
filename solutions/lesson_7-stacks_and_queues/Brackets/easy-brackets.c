/**
 * URL : https://app.codility.com/demo/results/training3DN4AN-QFJ/
 */

#include <string.h>

/**
 * Stack Operations
 */
static char* stack = NULL;
static int head = 0;
void print_stack() {
    printf("[");
    for (int i = 0; i < 100; i++) {
        printf("'%c'%s", stack[i], (i < 100? "," : ""));
    }
    printf("]");
}
void stack_init(int size) {
    stack = malloc (size * sizeof(char));
    memset(stack, 0, size * sizeof(char));
}
void push(char c) { stack[head] = c; head++; }
char pop(void) { char c = stack[head - 1]; head --; return c; }

/**
 * HashTable using switch for brackets
 */
char brackets_hash_table(char key) {
    switch(key) {
        case '(': return ')'; break;
        case '{': return '}'; break;
        case '[': return ']'; break;
    }
    return 0;
}

int solution(char *S) {
    /**
     * Solution: Using Stack to push and pop the brackets, if the poping is not as expected then it's not a properly nested string.
     * Time Complexity:
     *   for loop linear => O(n)
     * Memory Complxity:
     *   Stack can be as long as the string => O(n)
     */
    stack_init((int) strlen(S));    
    for(int i = 0; S[i] != '\0'; i++) { // Iterate over the string
        char current_char = S[i];
        char popped_char = 0;
        switch (current_char) {
            case '(': case '{': case '[': push(current_char); break;
            case ')': case '}': case ']':
                popped_char = pop();
                if (brackets_hash_table(popped_char) != current_char) {
                    /* Not properly nested */
                    return 0;
                }
                break;
            default: break;
        }
    }
    if( head == 0 ) return 1;
    /* At the end of the stack is not empty this means some of the opening brackets are not closed properly */
    else return 0;
}

