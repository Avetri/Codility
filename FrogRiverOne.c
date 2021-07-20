// FrogRiverOne

#include <string.h>

void raise_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    // if (idx==31) printf("touch bit %d, dword_idx %d, internal idx %d, A[dword_idx] %08X \n", idx, dword_idx, internal_idx, A[dword_idx]);
    A[dword_idx] |= 1U << internal_idx;
    // if (idx==31) printf("touched bit A[dword_idx] %08X\n", A[dword_idx]);
}

int is_filled(unsigned int * A, int N) {
    int i = 0;
    while (i < N && A[i] == 0xFFFFFFFFU) {
        i++;
    }
    if (i < N) {
        return 0;
    } else {
        return 1;
    }
}

int solution(int X, int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int min_value = 1;
    int max_value = X;

    int dword_l = max_value/32;
    if (max_value%32 > 0) {
        dword_l++;
    }

    unsigned int * bits = (unsigned int *)malloc(dword_l*4);
    memset(bits, 0, dword_l*4);

    int i;
    for (i=X+1; i<=dword_l*32; i++) {
        raise_bit(bits, i-min_value);
    }

    int res = -1;

    for (i=0; i<N; i++) {
        raise_bit(bits, A[i]-min_value);
        if (1 == is_filled(bits, dword_l)) {
            res = i;
            break;
        }
    }

    free(bits);
    return res;
}
