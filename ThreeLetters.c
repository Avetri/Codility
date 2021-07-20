// ThreeLetters

char * solution(int A, int B) {
    // write your code in C99 (gcc 6.2.0)
    char * str = (char *)malloc(A+B+1);
    str[A+B] = 0;
    int a_pit = 0;
    int b_pit = 0;
    int a_dcnt = A;
    int b_dcnt = B;
    while (a_dcnt > 0 || b_dcnt > 0) {
        if (a_dcnt > 0 && (a_dcnt > b_dcnt || b_pit >= 2) && a_pit < 2) {
            str[a_dcnt + b_dcnt -1] = 'a';
            a_dcnt--;
            a_pit++;
            b_pit=0;
        } else if (b_dcnt > 0 && b_pit < 2) {
            str[a_dcnt + b_dcnt -1] = 'b';
            b_dcnt--;
            b_pit++;
            a_pit=0;
        } else {
            return NULL;
        }
    }

    return str;
}
