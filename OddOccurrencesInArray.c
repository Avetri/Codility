// OddOccurrencesInArray

#include <strings.h>
#include <errno.h>
#include <string.h>

#define MIN_VALUE 1
#define MAX_VALUE 1000000000

void turn_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    //printf("turn bit %d, dword_idx %d, internal idx %d, A[dword_idx] %d \n", idx, dword_idx, internal_idx, A[dword_idx]);
    A[dword_idx] ^= 1U << internal_idx;
    //printf("turnde bit A[dword_idx] %d\n", A[dword_idx]);
}

int find_odd(unsigned int * A, int length) {
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
    return dword_idx * 32 + internal_idx + MIN_VALUE; 
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int dword_len = (MAX_VALUE - MIN_VALUE + 1)/32;
    if ((MAX_VALUE - MIN_VALUE + 1) % 32 > 0) {
        dword_len += 1;
    }
    unsigned int * bits = (unsigned int *)malloc(dword_len * 4);
    if (bits == NULL) {
        printf("Can't allocate memory: %s!", strerror(errno));
        return -1;
    }
    bzero(bits, dword_len * 4);
    int i;
    for (i=0; i<N; i++) {
        turn_bit(bits, A[i]-MIN_VALUE);
    }
    int odd_one = find_odd(bits, dword_len);
    free(bits);
    return odd_one;
}
