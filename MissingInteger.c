// MissingInteger

#include <string.h>

void shutdown_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    // printf("shutdown bit %d, dword_idx %d, internal idx %d, A[dword_idx] %08X \n", idx, dword_idx, internal_idx, A[dword_idx]);
    A[dword_idx] &= ~(1U << internal_idx);
    // printf("shotdownbit bit A[dword_idx] %08X\n", A[dword_idx]);
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int min_value = 1;
    int max_value = 1000000;
    int dword_l = max_value/32;
    if (dword_l%32 > 0) {
        dword_l++;
    }
    unsigned int * bits = (unsigned int *)malloc(dword_l*4);
    memset(bits, 0xFFU, dword_l*4);
    int i;
    for (i=0; i<N; i++) {
        if (A[i] >= min_value && A[i] <= max_value) {
            shutdown_bit(bits, A[i]-min_value);
        }        
    }
    i=0;
    while (i < dword_l && bits[i] == 0) {
        i++;
    }
    if (i >= dword_l) {
        return -1;
    }
    int internal_idx = 0;
    while (internal_idx < 32 && !(bits[i]&1U)) {
        bits[i] >>= 1;
        internal_idx++;
    }
    return i*32 + internal_idx + min_value;
}
