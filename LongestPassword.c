// LongestPassword

int measure(char *S) {
    char * ptr = S;
    int char_cnt = 0;
    int letters_cnt = 0;
    int number_cnt = 0;
    if (ptr[0] == 0) {
        return -1;
    }
    while (ptr[0] == ' ' && ptr[0] != 0) {
        ptr++;
    }
    if (ptr[0] == 0) {
        return -1;
    }
    int failure = 0;
    while (ptr[0] != ' ' && ptr[0] != 0) {
        if ((ptr[0] >= 'a' && ptr[0] <= 'z') || (ptr[0] >= 'A' && ptr[0] <= 'Z')) {
            letters_cnt++;
            char_cnt++;
        } else if (ptr[0] >= '0' && ptr[0] <= '9') {
            number_cnt++;
            char_cnt++;
        } else {
            failure = 1;
        }
        ptr++;
    }
    if (letters_cnt%2 != 0) {
        failure = 1;
    }
    if (number_cnt%2 != 1) {
        failure = 1;
    }
    int deep_length = measure(ptr);
    if (failure == 1) {
        return deep_length;
    }
    if (char_cnt > deep_length) {
        return char_cnt;
    } else {
        return deep_length;
    }
}

int solution(char *S) {
    // write your code in C99 (gcc 6.2.0)
    return measure(S);
}
