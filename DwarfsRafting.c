int char_to_pos(char C) {
    if (C >= 'A' && C <= 'Z') {
        return (int)(C-'A');
    }
    if (C >= 'a' && C <= 'z') {
        return (int)(C-'a');
    }
    return -1;    
}

struct seat {
    int row;
    int label_idx;
    struct seat * next;
};

struct seat * parse_seats(char * seats) {
    if (seats == NULL) {
        return NULL;
    }
    char * ptr = seats;
    while (ptr[0] == ' ') {
        ptr++;
    }
    if (seats[0] == 0) {
        return NULL;
    }
    
    struct seat * my_seat = (struct seat *)malloc(sizeof(struct seat));
    my_seat->row = 0;
    my_seat->label_idx = 0;
    while (ptr[0] != ' ' && ptr[0] != 0) {
        if (ptr[0] >= '0' && ptr[0] <= '9') {
            my_seat->row *= 10;
            my_seat->row += ptr[0]-'0';
        } else {
            my_seat->label_idx = char_to_pos(ptr[0]);
        }
        ptr++;
    }

    my_seat->row--;
    my_seat->next = parse_seats(ptr);
    return my_seat;
}

int solution(int N, char *S, char *T) {
    // write your code in C99 (gcc 6.2.0)
    if (N < 2 || N > 26 || N%2 == 1) {
        return -1;
    }
    int half_leng = N/2;
    int square_half_leng = half_leng*half_leng;
    int left_front_barrels = 0;
    int left_front_dwarfs = 0;
    int left_front_new_dwarfs = 0;
    int left_back_barrels = 0;
    int left_back_dwarfs = 0;
    int left_back_new_dwarfs = 0;
    int right_front_barrels = 0;
    int right_front_dwarfs = 0;
    int right_front_new_dwarfs = 0;
    int right_back_barrels = 0;
    int right_back_dwarfs = 0;
    int right_back_new_dwarfs = 0;

    struct seat * barrels = parse_seats(S);
    struct seat * dwarfs = parse_seats(T);

    // printf("barrels: ");
    while (barrels) {
        // printf("%d:%d ", barrels->row, barrels->label_idx);
        if (barrels->row < half_leng) {
            if (barrels->label_idx < half_leng) {
                left_front_barrels++;
            } else {
                right_front_barrels++;
            }
        } else {
            if (barrels->label_idx < half_leng) {
                left_back_barrels++;
            } else {
                right_back_barrels++;
            }
        }
        barrels = barrels->next;
    }

    // printf("\ndwarfs: ");
    while (dwarfs) {
        // printf("%d:%d ", dwarfs->row, dwarfs->label_idx);
        if (dwarfs->row < half_leng) {
            if (dwarfs->label_idx < half_leng) {
                left_front_dwarfs++;
            } else {
                right_front_dwarfs++;
            }
        } else {
            if (dwarfs->label_idx < half_leng) {
                left_back_dwarfs++;
            } else {
                right_back_dwarfs++;
            }
        }
        dwarfs = dwarfs->next;
    }
    // printf("\n");

    left_front_new_dwarfs = square_half_leng - left_front_barrels - left_front_dwarfs;
    left_back_new_dwarfs = square_half_leng - left_back_barrels - left_back_dwarfs;
    right_front_new_dwarfs = square_half_leng - right_front_barrels - right_front_dwarfs;
    right_back_new_dwarfs = square_half_leng - right_back_barrels - right_back_dwarfs;

    //Lets balance them
    int balanced = 0;
    int left_new_dwarfs = left_front_new_dwarfs + left_back_new_dwarfs;
    int left_dwarfs = left_front_dwarfs + left_back_dwarfs + left_new_dwarfs;
    int right_new_dwarfs = right_front_new_dwarfs + right_back_new_dwarfs;
    int right_dwarfs = right_front_dwarfs + right_back_dwarfs + right_new_dwarfs;
    int front_new_dwarfs = left_front_new_dwarfs + right_front_new_dwarfs;
    int front_dwarfs = left_front_dwarfs + right_front_dwarfs + front_new_dwarfs;
    int back_new_dwarfs = left_back_new_dwarfs + right_back_new_dwarfs;
    int back_dwarfs = left_back_dwarfs + right_back_dwarfs + back_new_dwarfs;
    int all_new_dwarfs = left_front_new_dwarfs + right_front_new_dwarfs + left_back_new_dwarfs + right_back_new_dwarfs;
    int all_dwarfs = left_dwarfs + right_dwarfs;
    if (left_dwarfs == right_dwarfs && front_dwarfs == back_dwarfs) {
        balanced = 1;
    }
    while (balanced == 0 && all_new_dwarfs > 0) {
        // printf("left %d, right %d, front %d, back %d\n", left_dwarfs, right_dwarfs, front_dwarfs, back_dwarfs);
        if (right_dwarfs > left_dwarfs && right_new_dwarfs == 0) {
            return -1;
        }
        if (right_dwarfs < left_dwarfs && left_new_dwarfs == 0) {
            return -1;
        }
        if (front_dwarfs > back_dwarfs && front_new_dwarfs == 0) {
            return -1;
        }
        if (front_dwarfs < back_dwarfs && back_new_dwarfs == 0) {
            return -1;
        }

        if (left_dwarfs > right_dwarfs && front_dwarfs > back_dwarfs) {
            if (left_front_new_dwarfs >0) {
                left_front_new_dwarfs--;      
            } else {
                return -1;
            }   
        } else if (left_dwarfs < right_dwarfs && front_dwarfs > back_dwarfs ) {
            if (right_front_new_dwarfs == 0) {
                return -1;
            }
            right_front_new_dwarfs--;
        } else if (left_dwarfs > right_dwarfs && front_dwarfs < back_dwarfs) {
            if (left_back_new_dwarfs == 0) {
                return -1;
            }
            left_back_new_dwarfs--;            
        } else if (left_dwarfs < right_dwarfs && front_dwarfs < back_dwarfs) {
            if (right_back_new_dwarfs == 0) {
                return -1;                
            }
            right_back_new_dwarfs--;
        } else if (left_dwarfs == right_dwarfs && front_dwarfs != back_dwarfs) {
            if (front_dwarfs > back_dwarfs) {
                if (left_front_new_dwarfs > 0) {
                    left_front_new_dwarfs--;
                }
                if (right_front_new_dwarfs > 0) {
                    right_front_new_dwarfs--;
                }
            } else {
                if(left_back_new_dwarfs > 0) {
                    left_back_new_dwarfs--;
                }
                if(right_back_new_dwarfs > 0) {
                    right_back_new_dwarfs--;
                }
            }
        } else if (left_dwarfs != right_dwarfs && front_dwarfs == back_dwarfs) {
            if (left_dwarfs > right_dwarfs) {
                if (left_front_new_dwarfs > 0) {
                    left_front_new_dwarfs--;
                }
                if (left_back_new_dwarfs > 0) {
                    left_back_new_dwarfs--;
                }
            } else {
                if(right_front_new_dwarfs > 0) {
                    right_front_new_dwarfs--;
                }
                if(right_back_new_dwarfs > 0) {
                    right_back_new_dwarfs--;
                }
            }
        }

        left_new_dwarfs = left_front_new_dwarfs + left_back_new_dwarfs;
        left_dwarfs = left_front_dwarfs + left_back_dwarfs + left_new_dwarfs;
        right_new_dwarfs = right_front_new_dwarfs + right_back_new_dwarfs;
        right_dwarfs = right_front_dwarfs + right_back_dwarfs + right_new_dwarfs;
        front_new_dwarfs = left_front_new_dwarfs + right_front_new_dwarfs;
        front_dwarfs = left_front_dwarfs + right_front_dwarfs + front_new_dwarfs;
        back_new_dwarfs = left_back_new_dwarfs + right_back_new_dwarfs;
        back_dwarfs = left_back_dwarfs + right_back_dwarfs + back_new_dwarfs;
        all_new_dwarfs = left_new_dwarfs + right_new_dwarfs;
        all_dwarfs = left_dwarfs + right_dwarfs;

        if (all_new_dwarfs > 0 && left_dwarfs == right_dwarfs && front_dwarfs == back_dwarfs) {
            // printf("left %d, right %d, front %d, back %d\n", left_dwarfs, right_dwarfs, front_dwarfs, back_dwarfs);
            balanced = 1;
        }
    }; 

    if (balanced == 1) {
        return all_new_dwarfs;
    }

    return -1;
}
