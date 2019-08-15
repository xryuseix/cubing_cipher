#include <iostream>
#include <vector>
#include <cmath>

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

const static char base62_table[62] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const static char printable_table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~', ' ', '\n', '\0', '\t'};
const static unsigned int tablesize = sizeof(printable_table)/sizeof(char);

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
        int beforetimes = key[i].times;
        key[i].times = 4 - key[i].times;
        cube.rotate(key[i]);
        key[i].times = beforetimes;
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

void encoding(const char (&plainblock)[45], char (&encoded_block)[54], const int blocknum) {

    for(int i = 0; i < 45; i++) {
        encoded_block[i] = plainblock[i];
    }
    for(int i = 0; i < 5; i++) {
        int sum = 0;
        for(int j = 0; j < 9; j++) {
            sum += plainblock[i*9 + j];
        }
        encoded_block[45 + i] = (char)(sum%26 + 'a');
    }
    encoded_block[50] = base62_table[blocknum/62];
    encoded_block[51] = base62_table[blocknum%62];
    
    int chartype1 = rand()%62;
    int chartype2 = rand()%62;

    encoded_block[52] = base62_table[chartype1];
    encoded_block[53] = base62_table[chartype2];

    return;
}

void encoding_test() {

    const char plainblock[45] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S'};
    char encoded_block[54];

    encoding(plainblock, encoded_block, 0);

    char BeforeRandBlock[52];
    for(int i = 0; i < 52; i ++) {//後ろのrand以外をコピー
        BeforeRandBlock[i] = encoded_block[i];
    }
    char Expectedblock_1[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'z', 'c', 'z', 'g', 'j', 'A', 'A'};
    assertEqual(BeforeRandBlock, Expectedblock_1);
}

void en_masking(const char (&plain)[54], char (&masked)[54], std::vector<int> (&iv)) {
    for(int i = 0; i < 54; i++) {
        iv.push_back(rand()%tablesize);
        int idx = (iv[i] + static_cast<int>(std::distance(std::begin(printable_table), std::find(std::begin(printable_table), std::end(printable_table), plain[i]))))%tablesize;
        masked[i] = printable_table[idx];
    }
}

void de_masking(const char (&plain)[54], char (&masked)[54], std::vector<int> (&iv)) {
    for(int i = 0; i < 54; i++) {
        int tablepos = static_cast<int>(std::distance(std::begin(printable_table), std::find(std::begin(printable_table), std::end(printable_table), plain[i])));
        int idx = (tablesize + tablepos - (int)iv[i])%tablesize;
        masked[i] = printable_table[idx];
    }
}

void shuffle(std::vector<std::vector<char>> (&str)) {

    for(int i = str.size() - 1; i > 0; i--) {
        int j = rand() % i;
        for(int k = 0; k < 54; k++) {
            char c = str[i][k];
            str[i][k] = str[j][k];
            str[j][k] = c;
        }
    }
}

void cubingmode_en(const std::vector<CubeOP>& key, std::vector<char> (&str), std::vector<char> (&ct), std::vector<int> (&iv)) {

    std::vector<std::vector<char>> ShuffleText;
    std::vector<char> pt;
    for(int i = 0; i < str.size(); i++) {
        pt.push_back(str[i]);
    }
    if(pt.size()%45 != 0) {
        pt.push_back('\0');
    }
    while(pt.size()%45 != 0) { //パディング処理
        int chartype = rand()%62;
        pt.push_back(base62_table[chartype]);
    }

    int blocknum = pt.size()/45;

    for(int i = 0; i < blocknum; i++) {

        char plainblock[45];
        char encoded_block[54];
        char cipherblock[54];
        char masked_block[54];
        std::vector<char> tmp;

        for(int j = 0; j < 45; j++) { //平文から平文ブロック作成
            plainblock[j] = pt[i*45 + j];
        }
        encoding(plainblock, encoded_block, i);
        en_masking(encoded_block, masked_block, iv);
        
        encrypt(key, masked_block, cipherblock);

        for(int j = 0; j < 54; j ++) { //char-vector変換
            tmp.push_back(cipherblock[j]);
            iv.push_back(masked_block[i]);
        }
        ShuffleText.push_back(tmp);
    }

    shuffle(ShuffleText);

    for(int i = 0; i < ShuffleText.size(); i++) {
        for(int j = 0; j < 54; j ++) {
            ct.push_back(ShuffleText[i][j]);
        }
    }
    // for(int i = 0; i < iv.size(); i++) {
    //     std::cout<<iv[i]<<" ";
    // }

    return;
}

void cubingmode_en_test() {

    std::vector<char> str{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!'};
    std::vector<char> ct;

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    key.push_back(op);

    // cubingmode_en(key, str, ct, mask);
    
    return;
}

int sequencenum(char f, char s) {

    int left,right;
    left = static_cast<int>(std::distance(std::begin(base62_table), std::find(std::begin(base62_table), std::end(base62_table), f)));
    right = static_cast<int>(std::distance(std::begin(base62_table), std::find(std::begin(base62_table), std::end(base62_table), s)));
    return left*62 + right;
}

bool sortcomp(const std::vector<char>& l, const std::vector<char>& r) {
    int leftnum = sequencenum(l[50], l[51]);
    int rightnum = sequencenum(r[50], r[51]);

    return leftnum < rightnum;
}

void decoding(std::vector<std::vector<char>> (&BeforeShuffleText), std::vector<char> (&pt)) {

    sort(BeforeShuffleText.begin(), BeforeShuffleText.end(), sortcomp);
    for(int i = 0; i < BeforeShuffleText.size(); i++) {
        for(int j = 0; j < 45; j++) {
            if(BeforeShuffleText[i][j] == '\0') {
                return;
            }
            pt.push_back(BeforeShuffleText[i][j]);
        }
    }
}

void cubingmode_de(std::vector<CubeOP>& key, const std::vector<char> (&str), std::vector<char> (&pt), std::vector<int> (&iv)) {

    if(str.size()%54 != 0) {
        printf("decryption error\n");
        return;
    }
    int blocknum = str.size()/54;
    std::vector<std::vector<char>> BeforeShuffleText; 

    for(int i = 0; i < blocknum; i++) {

        char cipherblock[54];
        char decrypted_block[54];
        char plainblock[45];
        char masked[54];
        std::vector<char> tmp;

        for(int j = 0; j < 54; j++) { //暗号文から暗号文ブロック作成
            cipherblock[j] = str[i*54 + j];
        }
        decrypt(key, cipherblock, decrypted_block);
        de_masking(decrypted_block, masked, iv);
        for(int j = 0; j < 54; j++) {
            tmp.push_back(masked[j]);
        }
        BeforeShuffleText.push_back(tmp);
        
    }

    decoding(BeforeShuffleText, pt);
    return;
}

void encode_decode_test() {
    char str[45] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S'};
    char chencoded[54], chdecoded[45];
    std::vector<char> vcdecoded, vcencoded;
    std::vector<std::vector<char>> todecode;

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    key.push_back(op);

    encoding(str, chencoded, 0);
    for(int i = 0; i < 54; i++) {
        vcencoded.push_back(chencoded[i]);
    }
    todecode.push_back(vcencoded);
    decoding(todecode, vcdecoded);
    for(int i = 0; i < 45; i++) {
        chdecoded[i] = vcencoded[i];
    }
    assertEqual(str, chdecoded);
}

void cubingmode_ende_test() {
    std::vector<char> str{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!', '?', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '!'};
    std::vector<char> ct;
    std::vector<char> pt;

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    key.push_back(op);

    // cubingmode_en(key, str, ct);
    // cubingmode_de(key, ct, pt);
    assertEqual(str, pt);
}

void usecubing(){

    char InputFileName[] = "input.txt";
    std::vector<char> str;
    std::vector<char> ct;

    FILE *fp;
    fp = fopen(InputFileName, "r");

    char c;
    while((c = fgetc(fp)) != EOF) {
        str.push_back(c);
    }

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    for(int i = 0; i < 200; i++) {
        op.column = 1 + rand()%3;
        op.direction = 1 + rand()%3;
        op.times = 1 + rand()%3;
        key.push_back(op);
    }
    
    bool printkey = 1;
    bool printct = 1;
    bool printpt = 1;
    bool printiv = 1;

    if(printkey) {
        printf("key: ");
        for(int i = 0; i < key.size(); i++) {
            printf("%d%d%d", key[i].direction, key[i].column, key[i].times);
        }
        printf("\n");
    }
    
    std::vector<int> iv;

    cubingmode_en(key, str, ct, iv);

    if(printct) {
        printf("\nct: ");
        for(int i = 0; i < ct.size(); i++) {
            if(ct[i]=='\0'){
                printf("$");
                continue;
            }
            printf("%c", ct[i]);
        }
        printf("(EOF)\n");
    }

    if(printiv) {
        printf("\niv: ");
        for(int i = 0; i < iv.size(); i++) {
            printf("%d,", iv[i]);
        }
        printf("(EOF)\n");
    }

    printf("\n----------------------------------\n");
    std::vector<char> pt;
    // for(int i=0;i<iv.size();i++){
    //     std::cout<<iv[i]<<" ";
    // }
    
    cubingmode_de(key, ct, pt, iv);
    
    if(printpt){
        printf("\npt: ");
        for(int i = 0; i < pt.size(); i++) {
            printf("%c", pt[i]);
        }
        printf("(EOF)\n");
    }
}

int main(int ac, char **av) {

    srand((unsigned) time(NULL));
/*
    printf("\n----unit_test----\n");
    unit_test();

    printf("\n----en_decode_test(Cube)----\n");
    en_decode_test();

    printf("\n----encrypt_test----\n");
    encrypt_test();

    printf("\n----decrypt_test----\n");
    decrypt_test();

    printf("\n----encoding_test----\n");
    encoding_test();

    printf("\n----cubingmode_ende_test----\n");
    cubingmode_ende_test();

    printf("\n----encode_decode_test(cubingmode)----\n");
    encode_decode_test();*/

    usecubing();


    return 0;
}
