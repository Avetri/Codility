// StrSymmetryPoint

#include <string.h>

int solution(char *S) {
    // write your code in C99 (gcc 6.2.0)
    if (S == NULL) {
        return -1;
    }
    int len = strlen(S);
    if (len%2 == 0) {
        return -1;
    }
    if (len == 1) {
        return 0;
    }
    int left_idx = 0;
    int right_idx = len-1;
    while (left_idx < right_idx && S[left_idx] == S[right_idx]) {
        left_idx++;
        right_idx--;
    }
    if (left_idx < right_idx) {
        return -1;
    }
    return left_idx;
}
