// PermMissingElem

#include <errno.h>
#include <string.h>

void shutdown_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    // printf("shutdown bit %d, dword_idx %d, internal idx %d, A[dword_idx] %08X \n", idx, dword_idx, internal_idx, A[dword_idx]);
    A[dword_idx] &= ~(1U << internal_idx);
    // printf("shotdownbit bit A[dword_idx] %08X\n", A[dword_idx]);
}

int find_absent(unsigned int * A, int length, int min_value) {
    int dword_idx = 0;
    while ((dword_idx < length) && (A[dword_idx] == 0)) {
        dword_idx++;
    }
    if (dword_idx >= length) {
        return -1;
    }
    int internal_idx = 0;
    while ((internal_idx < 32) && (A[dword_idx] != 1)) {
        A[dword_idx] >>= 1;
        internal_idx++;
    }
    return dword_idx * 32 + internal_idx + min_value; 
}

int solution(int A[], int N) {
    int min_value = 1;
    int max_value = N+1;
    int dword_len = max_value/32;
    if (max_value%32 > 0) {
        dword_len++;
    }

    unsigned int * bits = (unsigned int *)malloc(dword_len*4);
    memset(bits, 0xFFU, dword_len*4);
    int i;
    for (i=max_value+1; i<=dword_len*32; i++) {
        shutdown_bit(bits, i-min_value);        
    }
    for (i=0; i<N; i++) {
        shutdown_bit(bits, A[i]-min_value);
    }

    int absent = find_absent(bits, max_value, min_value);
    free(bits);
    return absent;
}
