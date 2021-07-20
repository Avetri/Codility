// TreeHeight

int depth(struct tree * T, int prev_depth) {
    if (T == NULL) {
        return prev_depth;
    }
    int left_depth = depth(T->l, prev_depth+1);
    int right_depth = depth(T->r, prev_depth+1);
    if (left_depth > right_depth) {
        return left_depth;
    } else {
        return right_depth;
    }
}

int solution(struct tree * T) {
    // write your code in C99 (gcc 6.2.0)
    return depth(T, -1);
}
