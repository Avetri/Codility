// ArrayInversionCount [!!! non successfull !!!]

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int res = 0;
    int i, j;
    for (i=0; i<N-1; i++) {
        for (j=i+1; j<N; j++) {
            if (A[i] > A[j]) {
                res++;
            }
        }
        if (res > 1000000000) {
            return -1;
        }
    }
    return res;
}
