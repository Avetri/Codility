// TapeEquilibrium

#include <limits.h>

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int * left_sum  = (int *)malloc(sizeof(int)*N);
    int * right_sum = (int *)malloc(sizeof(int)*N);
    int i;
    left_sum[0] = A[0];
    for (i=1; i<N-1; i++) {
        left_sum[i] = left_sum[i-1] + A[i];
    } 
    right_sum[N-1] = A[N-1];
    for (i=N-1-1; i>0; i--) {
        right_sum[i] = right_sum[i+1] + A[i];
    }

    int min = 2000;
    for (i=0; i<N-1; i++) {
        int new_diff = abs(left_sum[i] - right_sum[i+1]);
        if (min > new_diff) {
            min = new_diff;
        }
    }

    free(left_sum);
    free(right_sum);

    return min;
}
