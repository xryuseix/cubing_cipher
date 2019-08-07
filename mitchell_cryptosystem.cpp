#include <iostream>

struct CubeOP {
    char dir;
    int times;
};

struct Cube {
    char cubing[54];

    Cube (const char (&str)[54]) {
        for(int i = 0; i < 54; i++) {
            cubing[i] = str[i];
        }
    }
  
    // void rotate(const CubeOP &key) {
    //     char letter;
    //     int col = (key.times - 1)/3; //0は内側，１は外側
    //     int times = (key.times - 1)%3 + 1;
    //     if(key.dir == 0) { // 方向,Row 
    //         for(int k = 0; k < times*3; k++) { // 回数, *３はcubeの面が3*3だから

    //             letter = cubing[0 + col]; // colは転値対象列(0~2)
    //             cubing[0 + col] = cubing[3 + col];
    //             cubing[3 + col] = cubing[6 + col];
    //             cubing[6 + col] = cubing[12 + col];
    //             cubing[12 + col] = cubing[24 + col];
    //             cubing[24 + col] = cubing[36 + col];
    //             cubing[36 + col] = cubing[45 + col];
    //             cubing[45 + col] = cubing[48 + col];
    //             cubing[48 + col] = cubing[51 + col];
    //             cubing[51 + col] = cubing[44 - col];
    //             cubing[44 - col] = cubing[32 - col];
    //             cubing[32 - col] = cubing[20 - col];
    //             cubing[20 - col] = letter;

    //         }
    //     } else if(key.dir == 1) { // Column
    //         for(int k = 0; k < times*3; k++) { // 回数 
    //             letter = cubing[9 + 12*col];
    //             for(int m = 0; m < 11; m++) {
    //                 cubing[9 + 12*col + m] = cubing[10 + 12*col + m];
    //             }
    //             cubing[20 + 12*col] = letter;
    //         }
    //     } else if(key.dir == 2) { // Level
    //         for(int k = 0; k < times*3; k++) { // 回数 
    //             letter = cubing[6 - 3*col];
    //             cubing[6 - 3*col] = cubing[7 - 3*col];
    //             cubing[7 - 3*col] = cubing[8 - 3*col];
    //             cubing[8 - 3*col] = cubing[15 + col];
    //             cubing[15 + col] = cubing[27 + col];
    //             cubing[27 + col] = cubing[39 + col];
    //             cubing[39 + col] = cubing[47 + 3*col];
    //             cubing[47 + 3*col] = cubing[46 + 3*col];
    //             cubing[46 + 3*col] = cubing[45 + 3*col];
    //             cubing[45 + 3*col] = cubing[35 - col];
    //             cubing[35 - col] = cubing[23 - col];
    //             cubing[23 - col] = cubing[11 - col];
    //             cubing[11 - col] = letter;
    //         }
    //     }
    // }

    bool equals (const Cube& a) const {
        bool equal = true;
        for(int i = 0; i < 54; i++) {
            if(cubing[i] != a.cubing[i]) {
                equal = false;
                break;
            }
        }
        return equal;
    }

    void print() const {
        for(int i = 0; i < 54; i++) {
            printf("%c", cubing[i]);
        }
        printf("\n");
    }
};

void shuffle(char (&str)[54]) {
    for(int i = 1; i < 5; i++) {
        int j = rand() % (6 - i) + i;
        for(int k = 0; k < 9; k ++) {
            std::swap(str[i*9 + k], str[j*9 + k]);
        }
    }
}

void encode(const char (&str)[48], char (&encoded_str)[54]) {
    int pos;
    int strpos = 0;
    for(int i = 0; i < 54; i++) {
        encoded_str[i] = '*';
    }
    encoded_str[0] = '1';
    for(int i = 2; i <= 6; i++) { //数字を代入
       encoded_str[(i - 1)*9 + rand()%9] = i + '0'; 
    }
    for(int i = 0; i < 54; i++) {
        if(encoded_str[i] != '*') {
            continue;
        } else {
            encoded_str[i] = str[strpos];
            strpos++;
        }
    }
    shuffle(encoded_str);
}

void encode_test() {
    char str[48] = {'I', 'F', 'M', 'A', 'T', 'H', 'E', 'M', 'A', 'T', 'I', 'C', 'S', 'I', 'S', 'T', 'H', 'E', 'W', 'A', 'Y', 'O', 'F', 'L', 'I', 'F', 'E', 'D', 'O', 'N', 'T', 'F', 'O', 'R', 'G', 'E', 'T', 'T', 'H', 'E', 'T', 'H', 'E', 'O', 'R', 'E', 'M', 'S'};
    char encoded_str[54];
    encode(str, encoded_str);
    for(int i = 0; i < 54; i++) {
        if(i%9 == 0) {
            printf("\n");
        }
        printf("%c ",encoded_str[i]);
    }
    printf("\n");
}

// void rotate_test() {
//     //
// }

int main(int ac, char **av) {

    srand((unsigned) time(NULL));

    printf("\n----encode_test----\n");
    encode_test();

    // printf("\n----rotate_test----\n");
    // rotate_test();
    

    //printf("\n----test----\n");
    //test();
    return 0;
}