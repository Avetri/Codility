// FirstUnique [!!! non successfull !!!]

#include <string.h>

void clear_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    // printf("shutdown bit %d, dword_idx %d, internal idx %d, A[dword_idx] %08X \n", idx, dword_idx, internal_idx, A[dword_idx]);
    A[dword_idx] &= ~(1U << internal_idx);
    // printf("shotdownbit bit A[dword_idx] %08X\n", A[dword_idx]);
}
/*
int is_clean_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    if (A[dword_idx] & (1U << internal_idx)) {
        return 0;
    } else {
        return 1;
    }
}
*/

void raise_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    // if (idx==31) printf("touch bit %d, dword_idx %d, internal idx %d, A[dword_idx] %08X \n", idx, dword_idx, internal_idx, A[dword_idx]);
    A[dword_idx] |= (1U << internal_idx);
    // if (idx==31) printf("touched bit A[dword_idx] %08X\n", A[dword_idx]);
}

int is_raised_bit(unsigned int * A, int idx) {
    int dword_idx = idx / 32;
    int internal_idx = idx % 32;
    if (A[dword_idx] & (1U << internal_idx)) {
        return 1;
    } else {
        return 0;
    }
}

int find_n_clear_the_first_once(unsigned int * A, int start, int length) {
    int dword_l = length/32;
    if (length%32 > 0) {
        dword_l++;
    }
    int i=start/32;
    while (i<dword_l && A[i]==0){
        i++;
    }
    int res = -1;
    if (i<dword_l) {
        int internal_idx = 0;
        unsigned int brick = A[i];
        while (internal_idx < 32 && !(brick&1U)) {
            internal_idx++;
            brick >>= 1;
        }
        res = i*32 + internal_idx;
        clear_bit(A, res);        
    }
    return res;
}

int find_idx(int * A, int N, int victim) {
    int i = 0;
    while (i<N && A[i]!=victim) {
        i++;
    }
    return i;
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    //int min_value = 0;
    int max_value = 1000000000;
    int dword_l = max_value/32;
    if (max_value%32 > 0) {
        dword_l++;
    }
    unsigned int * once = (unsigned int *)malloc(dword_l*4);
    memset(once, 0, dword_l*4);
    unsigned int * non_once = (unsigned int *)malloc(dword_l*4);
    memset(non_once, 0, dword_l*4);
    int i;
    for (i=0; i<N; i++) {
        if (is_raised_bit(non_once, A[i])) {
            continue;
        } else if (is_raised_bit(once, A[i])) {
            clear_bit(once, A[i]);
            raise_bit(non_once, A[i]);
        } else {
            raise_bit(once, A[i]);
        }
    }
    free(non_once);
    
    int first_once = -1;
    int first_once_idx = N;
    int new_first_once;
    int new_first_once_idx = N;
    while (-1 != (new_first_once = find_n_clear_the_first_once(once, first_once+1, max_value))) {
        new_first_once_idx = find_idx(A, N, new_first_once);
        if (new_first_once_idx < first_once_idx) {
            first_once_idx = new_first_once_idx;
            first_once = new_first_once;
        }
    }

    free(once);
    return first_once;
}
