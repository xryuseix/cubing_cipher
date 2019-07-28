#include <iostream>
#include <vector>

struct CubeOP {
    int direction;
    int column;
    int times;
};

struct Cube {
    char cubing[54];

    Cube (const char (&str)[54]) {
        for(int i = 0; i < 54; i++) {
            cubing[i] = str[i];
        }
    }
  
    void rotate(const CubeOP &key) {
        char letter;
        int col = key.column - 1;
        if(key.direction == 1) { // 方向 // 縦方向 
            for(int k = 0; k < key.times*3; k++) { // 回数 

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
        } else if(key.direction == 2){ // 横方向
            for(int k = 0; k < key.times*3; k++) { // 回数 
                letter = cubing[9 + 12*col];
                for(int m = 0; m < 11; m++) {
                    cubing[9 + 12*col + m] = cubing[10 + 12*col + m];
                }
                cubing[20 + 12*col] = letter;
            }
        } else if(key.direction == 3) { // 回転方向
            for(int k = 0; k < key.times*3; k++) { // 回数 
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

template <class T>
bool Equal(const T& a, const T& b) {
    return a == b;
}

template <>
bool Equal(const Cube& a, const Cube& b) {
    return a.equals(b);
}

template <int N>
bool Equal(const char (&a)[N], const char (&b)[N]) {

    if(strncmp(a,b,N) == 0) {
        return 1;
    } else {
        return 0;
    }
}

template <class T>
void assertEqual(const T& a, const T& b) {

    if(Equal(a, b)) {
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
        CubeOP op = {1, 2, 1};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube.cubing, expected.cubing);
    }

    { //横方向テスト
        char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        char ExpectedStr[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'v', 'w', 'x', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        
        Cube cube(str);
        Cube expected(ExpectedStr);

        std::vector<CubeOP> key;
        CubeOP op = {2, 2, 1};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube.cubing, expected.cubing);
    }

    { //回転方向テスト
        char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        char ExpectedStr[54] = {'a', 'b', 'c', 'q', 'C', 'O', 'g', 'h', 'i', 'j', 'f', 'l', 'm', 'n', 'o', 'p', 'Y', 'r', 's', 't', 'u', 'v', 'e', 'x', 'y', 'z', 'A', 'B', 'X', 'D', 'E', 'F', 'G', 'H', 'd', 'J', 'K', 'L', 'M', 'N', 'W', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'k', 'w', 'I', 'Z', '!', '?'};
        
        Cube cube(str);
        Cube expected(ExpectedStr);

        std::vector<CubeOP> key;
        CubeOP op = {3, 2, 1};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube.cubing, expected.cubing);
    }
    return;
}

Cube str2cube(const char (&str)[54]) {

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

        assertEqual(cube.cubing, ExpectedStr);
    }

    {
        char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        char ExpectedStr[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
        char buf[54];
        
        Cube cube(str);
        cube2str(cube, buf);
        
        assertEqual(buf, ExpectedStr);
    }
    
    return;
}

void encrypt(const std::vector<CubeOP>& key, const char (&str)[54], char (&ct)[54]) {
    
    Cube cube = str2cube(str);
    for(int i = 0; i < key.size(); i++) {
        cube.rotate(key[i]);
    }
    cube2str(cube, ct);

    return;
}

void encrypt_test() {

    char str[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
    char ExpectedStr[54] = {'a', 'n', 'c', 'd', 'z', 'f', 'g', 'L', 'i', 'j', 'k', 'l', 'm', 'U', 'o', 'p', 'q', 'r', 's', 'h', 'u', 'v', 'w', 'x', 'y', 'X', 'A', 'B', 'C', 'D', 'E', 'e', 'G', 'H', 'I', 'J', 'K', '!', 'M', 'N', 'O', 'P', 'Q', 'b', 'S', 'T', 'R', 'V', 'W', 'F', 'Y', 'Z', 't', '?'};
    char ct[54];
    
    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    key.push_back(op);
    
    encrypt(key, str, ct);
    assertEqual(ct, ExpectedStr);

    return;
}

void decrypt(std::vector<CubeOP>& key, const char (&str)[54], char (&pt)[54]) {

    Cube cube = str2cube(str);
    for(int i = key.size()-1; i >= 0; i--) {
        key[i].times = 4 - key[i].times;
        cube.rotate(key[i]);
    }
    cube2str(cube, pt);

    return;
}

void decrypt_test() {

    char str[54] = {'a', 'n', 'c', 'd', 'z', 'f', 'g', 'L', 'i', 'j', 'k', 'l', 'm', 'U', 'o', 'p', 'q', 'r', 's', 'h', 'u', 'v', 'w', 'x', 'y', 'X', 'A', 'B', 'C', 'D', 'E', 'e', 'G', 'H', 'I', 'J', 'K', '!', 'M', 'N', 'O', 'P', 'Q', 'b', 'S', 'T', 'R', 'V', 'W', 'F', 'Y', 'Z', 't', '?'};
    char ExpectedStr[54] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?'};
    char pt[54];

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    key.push_back(op);

    decrypt(key, str, pt);
    assertEqual(ExpectedStr,pt);

    return;
}

int main(int ac, char **av) { 
    // unit_test();
    // en_decode_test();
    // encrypt_test();
    // printf("--------\n");
    // decrypt_test();

    cubingmode()


    return 0;
}

/*
cubingmode(){

loop{
encoding()
encrypt()
}
shuffle()

}
 */