// PermCheck

#include <string.h>

void clear_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    // printf("shutdown bit %d, dword_idx %d, internal idx %d, A[dword_idx] %08X \n", idx, dword_idx, internal_idx, A[dword_idx]);
    A[dword_idx] &= ~(1U << internal_idx);
    // printf("shotdownbit bit A[dword_idx] %08X\n", A[dword_idx]);
}

int is_clean_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    if (A[dword_idx] & (1U << internal_idx)) {
        return 0;
    } else {
        return 1;
    }
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int min_value = 1;
    int max_value = N;
    int dword_l = N/32;
    if (N%32 > 0) {
        dword_l++;
    }

    unsigned int * bits = (unsigned int *)malloc(dword_l*4);
    memset(bits, 0xFFU, dword_l*4);

    int i;
    for (i=N+1; i<=dword_l*32; i++) {
        clear_bit(bits, i-min_value);
    }

    for (i=0; i<N; i++) {
        if (0 >= A[i] || A[i] > max_value) {
            return 0;
        } 
        if (is_clean_bit(bits, A[i]-min_value)) {
            return 0;
        }
        clear_bit(bits, A[i]-min_value);
    }

    for(i=0; i<dword_l; i++) {
        if (bits[i] > 0) {
            return 0;
        }
    }
    
    return 1;
}
