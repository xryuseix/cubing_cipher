#include <iostream>
#include <vector>

struct CubeOP {
    int direction;
    int column;
    int times;
};

struct Cube {
    char cubing[54];

    Cube (char (&str)[54]) {
        for(int i = 0; i < 54; i++) {
            cubing[i] = str[i];
        }
    }
  
    void rotate(std::vector<CubeOP> &key) {
        for(int i = 0; i < key.size(); i = i + 3) { // 転置
            char letter;
            int col = key[i].column - 1;
            if(key[i].direction == 1) { // 方向 // 縦方向 
                for(int k = 0; k < key[i].times; k++) { // 回数 

                    letter = cubing[0 + col]; // colは転値対象列(0~2)
                    cubing[0 + col] = cubing[3 + col];
                    cubing[3 + col] = cubing[6 + col];
                    cubing[6 + col] = cubing[12 + col];
                    cubing[12 + col] = cubing[24 + col];
                    cubing[24 + col] = cubing[36 + col];
                    cubing[36 + col] = cubing[45 + col];
                    cubing[45 + col] = cubing[48 + col];
                    cubing[48 + col] = cubing[51 + col];
                    cubing[51 + col] = cubing[44 - col];
                    cubing[44 - col] = cubing[32 - col];
                    cubing[32 - col] = cubing[20 - col];
                    cubing[20 - col] = letter;

                }
            } else if(key[i].direction == 2){ // 横方向
                for(int k = 0; k < key[i].times; k++) { // 回数 
                    letter = cubing[9 + 12*col];
                    for(int m = 0; m < 11; m++) {
                        cubing[9 + 12*col + m] = cubing[10 + 12*col + m];
                    }
                    cubing[20 + 12*col] = letter;
                }
            } else if(key[i].direction == 3) { // 回転方向
                for(int k = 0; k < key[i].times; k++) { // 回数 
                    letter = cubing[6 - 3*col];
                    cubing[6 - 3*col] = cubing[7 - 3*col];
                    cubing[7 - 3*col] = cubing[8 - 3*col];
                    cubing[8 - 3*col] = cubing[15 + col];
                    cubing[15 + col] = cubing[27 + col];
                    cubing[27 + col] = cubing[39 + col];
                    cubing[39 + col] = cubing[47 + 3*col];
                    cubing[47 + 3*col] = cubing[46 + 3*col];
                    cubing[46 + 3*col] = cubing[45 + 3*col];
                    cubing[45 + 3*col] = cubing[35 - col];
                    cubing[35 - col] = cubing[23 - col];
                    cubing[23 - col] = cubing[11 - col];
                    cubing[11 - col] = letter;
                }
            }
        }
    }

    bool equals(Cube a){
        bool equal = true;
        for(int i = 0; i < 54; i++) {
            if(cubing[i] != a.cubing[i]) {
                equal = false;
            }
        }
        return equal;
    }
  
    void print() {
        for(int i = 0; i < 54; i++) {
            printf("%c", cubing[i]);
        }
        printf("\n");
    }
};

void cube_assert(Cube a, Cube b){
    if(a.equals(b)) {
        printf("AC\n");
    } else {
        printf("WA\n");
    }
    return;
}

void unit_test() {

    { //縦方向テスト
    char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
    char ExpectedStr[54] = {'a', 'n', 'c', 'd', 'z', 'f', 'g', 'L', 'i', 'j', 'k', 'l', 'm', 'U', 'o', 'p', 'q', 'r', 's', 'h', 'u', 'v', 'w', 'x', 'y', 'X', 'A', 'B', 'C', 'D', 'E', 'e', 'G', 'H', 'I', 'J', 'K', '!', 'M', 'N', 'O', 'P', 'Q', 'b', 'S', 'T', 'R', 'V', 'W', 'F', 'Y', 'Z', 't', '?'};
    
    Cube cube(str);
    Cube expected(ExpectedStr);

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 3};
    key.push_back(op);

    cube.rotate(key);
    cube_assert(cube, expected);
    }

    { //横方向テスト
    char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
    char ExpectedStr[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'v', 'w', 'x', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
    
    Cube cube(str);
    Cube expected(ExpectedStr);

    std::vector<CubeOP> key;
    CubeOP op = {2, 2, 3};
    key.push_back(op);

    cube.rotate(key);
    cube_assert(cube, expected);
    }

    { //回転方向テスト
    char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
    char ExpectedStr[54] = {'a', 'b', 'c', 'q', 'C', 'O', 'g', 'h', 'i', 'j', 'f', 'l', 'm', 'n', 'o', 'p', 'Y', 'r', 's', 't', 'u', 'v', 'e', 'x', 'y', 'z', 'A', 'B', 'X', 'D', 'E', 'F', 'G', 'H', 'd', 'J', 'K', 'L', 'M', 'N', 'W', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'k', 'w', 'I', 'Z', '!', '?'};
    
    Cube cube(str);
    Cube expected(ExpectedStr);

    std::vector<CubeOP> key;
    CubeOP op = {3, 2, 3};
    key.push_back(op);

    cube.rotate(key);
    cube_assert(cube, expected);
    }
    return;
}

Cube str2cube(char (&str)[54]) {
    Cube cube (str);
    return std::move(cube);
}

void cube2str(Cube cube, char (&str)[54]) {
    for(int i = 0; i < 54; i++) {
        str[i] = cube.cubing[i];
    }
    return;
}

void en_decode_test() {
    {
        char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        char ExpectedStr[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        
        Cube cube = str2cube(str);

        if(strncmp(cube.cubing, ExpectedStr, 54) == 0) { //f(x) == y
            printf("encode: AC\n");
        } else {
            printf("encode: WA\n");
        }
    }

    {
        char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        char ExpectedStr[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        char buf[54];
        
        Cube cube(str);
        cube2str(cube, buf);
        
        if(strncmp(buf, ExpectedStr, 54) == 0) { //f(y) == x
            printf("decode: AC\n");
        } else {
            printf("decode: WA\n");
        }
    }
    
    return;
}

int main(int ac, char **av) { 
    unit_test();
    en_decode_test();
    // cube.print();
    return 0;
}