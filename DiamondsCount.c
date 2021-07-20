// DiamondsCount

#include <string.h>

int solution(int X[], int Y[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int x_sym[N][N];
    memset(x_sym, 0, N*N*sizeof(int));
    int y_sym[N][N];
    memset(y_sym, 0, N*N*sizeof(int));
    int i, j;
    for (i=0; i<N-1; i++) {
        for (j=i+1; j<N; j++) {
            if (Y[i] == Y[j] && X[i] != X[j] && abs(X[i]-X[j])%2 == 0) {
                x_sym[(X[i]+X[j])/2][Y[i]]++;
                // printf("X sym.: %d:%d\n", (X[i]+X[j])/2, Y[i]);
            }
            if (X[i] == X[j] && Y[i] != Y[j] && abs(Y[i]-Y[j])%2 == 0) {
                y_sym[X[i]][(Y[i]+Y[j])/2]++;
                // printf("Y sym.: %d:%d\n", X[i], (Y[i]+Y[j])/2);
            }
        }
    }
    int res = 0;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            res += x_sym[i][j]*y_sym[i][j];
        }
    }

    return res; 
}
