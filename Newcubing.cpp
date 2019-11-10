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

void en_masking1(const char (&plain)[45], char (&masked)[45], std::vector<int> (&iv)) {

    for(int i = 0; i < 45; i++) {
        iv.push_back(rand()%tablesize);
        int dis = static_cast<int>(std::distance(std::begin(printable_table), std::find(std::begin(printable_table), std::end(printable_table), plain[i])));
        int idx = (iv[iv.size() - 1] + dis)%tablesize;
        masked[i] = printable_table[idx];
    }
}

void en_masking2(const char (&plain)[54], char (&masked)[54], std::vector<int> (&iv)) {

    for(int i = 0; i < 45; i++) {
        masked[i] = plain[i];
    }
    for(int i = 45; i < 52; i++) {
        iv.push_back(rand()%tablesize);
        int dis = static_cast<int>(std::distance(std::begin(printable_table), std::find(std::begin(printable_table), std::end(printable_table), plain[i])));
        int idx = (iv[iv.size() - 1] + dis)%tablesize;
        masked[i] = printable_table[idx];
    }
    masked[52] = plain[52];
    masked[53] = plain[53];
}

void de_masking1(std::vector<char> (&plain), char (&masked)[45], std::vector<int> (&iv), const int nowblock) {

    for(int i = 0; i < 45; i++) {
        int dis = static_cast<int>(std::distance(std::begin(printable_table), std::find(std::begin(printable_table), std::end(printable_table), plain[i])));
        int idx = (tablesize + dis - iv[nowblock*45 + i])%tablesize;
        masked[i] = printable_table[idx];
    }
}

void de_masking2(const char (&plain)[54], char (&masked)[54], std::vector<int> (&iv), const int nowblock) {

    for(int i = 0; i < 45; i++) {
        masked[i] = plain[i];
    }
    for(int i = 45; i < 52; i++) {
        int dis = static_cast<int>(std::distance(std::begin(printable_table), std::find(std::begin(printable_table), std::end(printable_table), plain[i])));
        int idx = (tablesize + dis - iv[nowblock*7 + i - 45])%tablesize;
        masked[i] = printable_table[idx];
    }
    masked[52] = plain[52];
    masked[53] = plain[53];

}

void shuffle(std::vector<std::vector<char>> (&str)) {

    for(int i = str.size() - 1; i > 0; i--) {
        int j = rand() % i;
        for(int k = 0; k < 68; k++) {
            std::swap(str[i][k], str[j][k]);
        }
    }
}

void cubingmode_en(const std::vector<CubeOP>& key, std::vector<char> (&str), std::vector<char> (&ct), std::vector<int> (&iv1), std::vector<int> (&iv2)) {

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
        char masked_block1[45];
        char masked_block2[54];
        std::vector<char> tmp;

        for(int j = 0; j < 45; j++) { //平文から平文ブロック作成
            plainblock[j] = pt[i*45 + j];
        }
        en_masking1(plainblock, masked_block1, iv1);
        
        encoding(masked_block1, encoded_block, i);
        
        en_masking2(encoded_block, masked_block2, iv2);
        
        encrypt(key, masked_block2, cipherblock);
        
        for(int j = 0; j < 54; j ++) { //char-vector変換
            tmp.push_back(cipherblock[j]);
        }

        for(int j = 0; j < 7; j++) { //ivはint型だが暗号文はchar型なので，型変換
            if(iv2[7*i + j] < 10) {
                tmp.push_back('0');
                tmp.push_back(iv2[7*i + j] + '0');
            } else {
                tmp.push_back(iv2[7*i + j]/10 + '0');
                tmp.push_back(iv2[7*i + j]%10 + '0');
            }
        }
        ShuffleText.push_back(tmp);
    }

    shuffle(ShuffleText);

    for(int i = 0; i < ShuffleText.size(); i++) {
        for(int j = 0; j < 54 + 14; j ++) {
            ct.push_back(ShuffleText[i][j]);
        }
    }
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

void decoding(std::vector<std::vector<char>> (&BeforeShuffleText), std::vector<char> (&pt), std::vector<int> (&iv)) {

    char tmp[45];
    sort(BeforeShuffleText.begin(), BeforeShuffleText.end(), sortcomp);

    for(int i = 0; i < BeforeShuffleText.size(); i++) {
        de_masking1(BeforeShuffleText[i], tmp, iv, i);
        for(int j = 0; j < 45; j++) {
            pt.push_back(tmp[j]);
        }
    }
    //パディング削除
    pt.erase(pt.begin() + static_cast<int>(std::distance(std::begin(pt), std::find(std::begin(pt), std::end(pt), '\0'))), pt.end());
}

void cubingmode_de(std::vector<CubeOP>& key, const std::vector<char> (&str), std::vector<char> (&pt)) {

    std::vector<char> ct;
    std::vector<int> iv1, tmpiv2, iv2;

    for(int i = 0; i < (str.size()/158 + 1)*68; i++) { //暗号文68/158がct+iv2,残りがiv1
        if(i%68 < 54) {
            ct.push_back(str[i]);
        } else {
            tmpiv2.push_back(str[i] - '0');
        }
    }

    for(int i = str.size()/158*68; i < str.size(); i += 2) {
        iv1.push_back((str[i] - '0')*10 + (str[i + 1] - '0'));
    }

    for(int i = 0; i < tmpiv2.size()-1; i += 2) {
        iv2.push_back(tmpiv2[i]*10 + tmpiv2[i + 1]);
    }

    if(ct.size()%54 != 0 || iv2.size()%7 != 0) {
        printf("decryption error\n");
        return;
    }

    int blocknum = ct.size()/54;
    std::vector<std::vector<char>> BeforeShuffleText;
    for(int i = 0; i < blocknum; i++) {

        char cipherblock[54];
        char decrypted_block[54];
        char masked[54];
        std::vector<char> tmp;

        for(int j = 0; j < 54; j++) { //暗号文から暗号文ブロック作成
            cipherblock[j] = ct[i*54 + j];
        }
        decrypt(key, cipherblock, decrypted_block);
        
        de_masking2(decrypted_block, masked, iv2, i);

        for(int j = 0; j < 54; j++) {
            tmp.push_back(masked[j]);
        }
        BeforeShuffleText.push_back(tmp);

    }

    decoding(BeforeShuffleText, pt, iv1);
    return;
}

void encode_decode_test() {
    char str[45] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S'};
    char chencoded[54], chdecoded[45];
    std::vector<char> vcdecoded, vcencoded;
    std::vector<std::vector<char>> todecode;
    std::vector<int> iv(45,0);

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    key.push_back(op);

    encoding(str, chencoded, 0);
    for(int i = 0; i < 54; i++) {
        vcencoded.push_back(chencoded[i]);
    }
    todecode.push_back(vcencoded);
    
    decoding(todecode, vcdecoded, iv);
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

    std::vector<int> iv1,iv2;

    cubingmode_en(key, str, ct, iv1, iv2);

    for(int i=0;i<iv1.size();i++){
        if(iv1[i] < 10) {
            ct.push_back('0');
        } else {
            ct.push_back(iv1[i]/10 + '0');
        }
        ct.push_back(iv1[i]%10 + '0');
    }
    cubingmode_de(key, ct, pt);

    assertEqual(str, pt);
}

void usecubing_en() {

    char InputFileName[] = "./io/input.txt";
    char KeyFileName[] = "./io/key.txt";
    char OutputFileName[] = "./io/cipher.txt";
    std::vector<char> pt;
    std::vector<char> ct;

    { //plain input
        FILE *fp;
        fp = fopen(InputFileName, "r");

        char c;
        while((c = fgetc(fp)) != EOF) {
            pt.push_back(c);
        }
        fclose(fp);
    }
    std::vector<CubeOP> key;
    { //key input
        FILE *fp;
        fp = fopen(KeyFileName, "r");

        char c;
        int num = 0;
        int tmpkey[3];
        while((c = fgetc(fp)) != EOF) {
            tmpkey[num] = c - '0';
            num++;
            if(num%3 == 0) {
                num = 0;
                CubeOP op = {tmpkey[0], tmpkey[1], tmpkey[2]};
                key.push_back(op);
            }
        }
        fclose(fp);
    }

    bool plaintext = 0;
    bool printkey = 0;
    bool printct = 0;
    bool printiv = 0;
    bool generatekey = 0;

    if(generatekey) {
        int keysize = 30;
        CubeOP op = {1, 2, 1};
        for(int i = 0; i < keysize; i++) {
            op.direction = 1 + rand()%3;
            op.column = 1 + rand()%3;
            op.times = 1 + rand()%3;
            key.push_back(op);
        }
    }

    if(plaintext) {
        printf("pt: ");
        for(int i = 0; i < pt.size(); i++) {
            printf("%c", pt[i]);
        }
        printf("\n\n");
    }

    if(printkey) {
        printf("key: ");
        for(int i = 0; i < key.size(); i++) {
            printf("%d%d%d", key[i].direction, key[i].column, key[i].times);
        }
        printf("\n");
    }
    std::vector<int> iv1, iv2;
    for(int i = 0; i < pt.size()/(62*62) + 1; i++) {
        std::vector<int> diviv1, diviv2;
        std::vector<char> divpt;
        std::vector<char> divct;
        // 平文の分割処理
        for(int j = (62*62)*i; j < pt.size() && j < (62*62)*i + (62*62); j++) {
            divpt.push_back(pt[j]);
        }
        cubingmode_en(key, divpt, divct, diviv1, diviv2);

        if(printct) {
            printf("\nct: ");
            for(int i = 0; i < ct.size(); i++) {
                if(ct[i] == '\0'){
                    printf("$");
                    continue;
                } else if(ct[i] == '\t') {
                    printf(" ");
                    continue;
                }
                printf("%c", ct[i]);
            }
            printf("(EOF)\n");
        }

        if(printiv) {
            printf("\niv1: ");
            for(int i = 0; i < iv1.size(); i++) {
                printf("%02d ", iv1[i]);
            }
            printf("(EOF)\n");
            printf("\niv2: ");
            for(int i = 0; i < iv2.size(); i++) {
                printf("%02d ", iv2[i]);
            }
            printf("(EOF)\n");
        }
        // 結合処理
        for(int j = 0; j < divct.size(); j++) {
            ct.push_back(divct[j]);
        }
        for(int j = 0; j < diviv1.size(); j++) {
            iv1.push_back(diviv1[j]);
        }
        for(int j = 0; j < diviv2.size(); j++) {
            iv2.push_back(diviv2[j]);
        }
    }
    { //key output
        FILE *fp;
        fp = fopen(KeyFileName, "w");

        for(int i = 0; i < key.size(); i++) {
            fprintf(fp, "%d%d%d", key[i].direction, key[i].column, key[i].times);
        }
        fclose(fp);
    }
    { //cipher & iv output
        FILE *fp;
        fp = fopen(OutputFileName, "w");

        for(int i = 0; i < ct.size(); i++) {
            fprintf(fp, "%c", ct[i]);
        }
        for(int i = 0; i < iv1.size(); i++) {
            fprintf(fp, "%02d", iv1[i]);
        }
        fclose(fp);
    }
}

void usecubing_de(){
    char InputFileName[] = "./io/cipher.txt";
    char KeyFileName[] = "./io/key.txt";
    char OutputFileName[] = "./io/plain.txt";
    std::vector<char> ct;
    { //cipher input
        FILE *fp;
        fp = fopen(InputFileName, "r");

        char c;
        while((c = fgetc(fp)) != EOF) {
            ct.push_back(c);
        }
        fclose(fp);
    }

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    { //key input
        FILE *fp;
        fp = fopen(KeyFileName, "r");

        char c;
        int oppos = 0;
        while((c = fgetc(fp)) != EOF) {
            if(oppos%3 == 0) {
                op.direction = c - '0';
            } else if(oppos%3 == 1) {
                op.column = c - '0';
            } else {
                op.times = c - '0';
                key.push_back(op);
            }
            oppos = (oppos + 1)%3;
        }
        fclose(fp);
    }

    bool printkey = 0;
    bool printct = 0;
    bool printpt = 0;

    if(printct) {
        printf("\nct: ");
        for(int i = 0; i < ct.size(); i++) {
            if(ct[i] == '\0'){
                printf("$");
                continue;
            } else if(ct[i] == '\t') {
                printf(" ");
                continue;
            }
            printf("%c", ct[i]);
        }
        printf("(EOF)\n");
    }

    if(printkey) {
        printf("key: ");
        for(int i = 0; i < key.size(); i++) {
            printf("%d%d%d", key[i].direction, key[i].column, key[i].times);
        }
        printf("\n");
    }
    std::vector<int> iv1, iv2;
    std::vector<char> pt;
    for(int i = 0; i < pt.size()/(108*62*62) + 1; i++) {
        std::vector<int> diviv1, diviv2;
        std::vector<char> divpt;
        std::vector<char> divct;

        for(int j = (62*62*108)*i; j < ct.size() && j < (62*62*108)*i + (62*62*108); j++) {
            divct.push_back(ct[j]);
        }
        cubingmode_de(key, ct, pt);
        if(printpt){
            printf("\npt: ");
            for(int i = 0; i < pt.size(); i++) {
                printf("%c", pt[i]);
            }
            printf("(EOF)\n");
        }
        // 結合処理
        for(int j = 0; j < divpt.size(); j++) {
            pt.push_back(divpt[j]);
        }
    }

    { //plain output
        FILE *fp;
        fp = fopen(OutputFileName, "w");

        for(int i = 0; i < pt.size(); i++) {
            fprintf(fp, "%c", pt[i]);
        }
        fclose(fp);
    }
}

int main(int ac, char **av) {

    srand((unsigned) time(NULL));

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
    encode_decode_test();

    usecubing_en();

    usecubing_de();


    return 0;
}
