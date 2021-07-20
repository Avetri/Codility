// DisappearingPairs

#include <string.h>

char * solution(char *S) {

    char * ptr = S;
    char * cursor = ptr+1;

    int l = strlen(S);

    while (cursor < S+l+1) {
        // printf ("S \"%s\", ptr \"%s\", cursor \"%s\" \n", S, ptr, cursor);
        if (ptr > S && ptr[-1] == ptr[0]) {
            ptr[-1] = 0;
            ptr[0]  = 0;
            ptr--;
            continue;
        }
        if (ptr[0] != 0 && ptr[0] == cursor[0]) {
            ptr[0] = 0;
            cursor[0] = 0;
            cursor++;
            continue;
        }
        if (ptr[0] != 0 && ptr[0] != cursor[0]) {
            ptr[1] = cursor[0];
            cursor++;
            ptr++;
            continue;
        }
        if (ptr[0] == 0) {
            ptr[0] = cursor[0];
            cursor++;
            continue;
        } 
    }
    ptr[1] = 0;

    return S;
}
