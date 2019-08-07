#include <iostream>
#include<vector>

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
  
    void rotate(const CubeOP &key) {
        char letter;
        int col = (key.times - 1)/3; //0は内側，１は外側
        int times = (key.times - 1)%3 + 1;
        
        if(key.dir == 'R') { // 方向,Row 
            for(int k = 0; k < times*3; k++) { // 回数, *３はcubeの面が3*3だから
            
                letter = cubing[4 + col*3];
                cubing[4 + col*3] = cubing[3 + col*3];
                cubing[3 + col*3] = cubing[50 + col*3];
                cubing[50 + col*3] = cubing[49 + col*3];
                cubing[49 + col*3] = cubing[48 + col*3];
                cubing[48 + col*3] = cubing[41 + col*3];
                cubing[41 + col*3] = cubing[40 + col*3];
                cubing[40 + col*3] = cubing[39 + col*3];
                cubing[39 + col*3] = cubing[23 + col*3];
                cubing[23 + col*3] = cubing[22 + col*3];
                cubing[22 + col*3] = cubing[21 + col*3];
                cubing[21 + col*3] = cubing[5 + col*3];
                cubing[5 + col*3] = letter;
                
            }
        } else if(key.dir == 'C') { // Column
            for(int k = 0; k < times*3; k++) { // 回数 
                
                letter = cubing[1 + col];
                cubing[1 + col] = cubing[4 + col];
                cubing[4 + col] = cubing[7 + col];
                cubing[7 + col] = cubing[30 - col*3];
                cubing[30 - col*3] = cubing[31 - col*3];
                cubing[31 - col*3] = cubing[32 - col*3];
                cubing[32 - col*3] = cubing[43 - col];
                cubing[43 - col] = cubing[40 - col];
                cubing[40 - col] = cubing[37 - col];
                cubing[37 - col] = cubing[14 + col*3];
                cubing[14 + col*3] = cubing[13 + col*3];
                cubing[13 + col*3] = cubing[12 + col*3];
                cubing[12 + col*3] = letter;

            }
        } else if(key.dir == 'L') { // Level
            for(int k = 0; k < times*3; k++) { // 回数 
                letter = cubing[10 + col];
                cubing[10 + col] = cubing[13 + col];
                cubing[13 + col] = cubing[16 + col];
                cubing[16 + col] = cubing[19 + col];
                cubing[19 + col] = cubing[22 + col];
                cubing[22 + col] = cubing[25 + col];
                cubing[25 + col] = cubing[28 + col];
                cubing[28 + col] = cubing[31 + col];
                cubing[31 + col] = cubing[34 + col];
                cubing[34 + col] = cubing[52 - col];
                cubing[52 - col] = cubing[49 - col];
                cubing[49 - col] = cubing[46 - col];
                cubing[46 - col] = letter;
            }
        }
    }

    bool equals (const Cube& a) const {
        bool equal = true;
        for(int i = 0; i < 54; i++) {
            if(cubing[i] != a.cubing[i]) {
                printf("%c,%c,%d\n",cubing[i],a.cubing[i],i);
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

template <>
bool Equal(const std::vector<CubeOP> (&a), const std::vector<CubeOP> (&b)) {
    bool equal = true;
    for(int i = 0; i < a.size(); i++) {
        if(a[i].dir != b[i].dir || a[i].times != b[i].times) {
            equal = false;
            break;
        }
    }
    return equal;
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
            if(encoded_str[i] == ' ' && rand()%2 == 0) {
                encoded_str[i] = '\0';
            }
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

template<int N>
std::vector<CubeOP> make_key(char (&key)[N]) {

    std::vector<CubeOP> newkey;
    CubeOP op;
    for(int i = 0; i < N; i+=2) {
        CubeOP op = {key[i], key[i+1] - '0'};
        newkey.push_back(op);
    }
    return newkey;
}

void key_test() {
    char str[] = {'R', '4', 'C', '1', 'L', '5'};
    std::vector<CubeOP> key = make_key(str);

    std::vector<CubeOP> Expected;
    {
        CubeOP op = {'R', 4};
        Expected.push_back(op);
    }
    {
        CubeOP op = {'C', 1};
        Expected.push_back(op);
    }
    {
        CubeOP op = {'L', 5};
        Expected.push_back(op);
    }
    assertEqual(key, Expected);
}

void rotate_test() {
    {//Row_test
        char str[54] = {'1', 'I', 'F', 'M', 'A', 'T', 'H', 'E', 'M', 'A', '2', 'T', 'I', 'C', 'S', 'I', 'S', 'T', '4', 'I', 'F', 'E', 'D', 'O', 'N', 'T', 'F', 'T', '6', 'H', 'E', 'O', 'R', 'E', 'M', 'S', 'H', '3', 'E', 'W', 'A', 'Y', 'O', 'F', 'L', 'O', 'R', 'G', 'E', 'T', '5', 'T', 'H', 'E'};
        char Expectedstr[54] = {'1', 'I', 'F', 'M', 'A', 'T', 'T', 'H', 'E', 'A', '2', 'T', 'I', 'C', 'S', 'I', 'S', 'T', '4', 'I', 'F', 'E', 'D', 'O', 'H', 'E', 'M', 'T', '6', 'H', 'E', 'O', 'R', 'E', 'M', 'S', 'H', '3', 'E', 'W', 'A', 'Y', 'N', 'T', 'F', 'O', 'R', 'G', 'E', 'T', '5', 'O', 'F', 'L'};

        Cube cube(str);
        Cube Expectedcube(Expectedstr);

        std::vector<CubeOP> key;
        CubeOP op = {'R', 4};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube,Expectedcube);
    }
    {
        char str[54] = {'1', 'I', 'F', 'M', 'A', 'T', 'H', 'E', 'M', 'A', '2', 'T', 'I', 'C', 'S', 'I', 'S', 'T', '4', 'I', 'F', 'E', 'D', 'O', 'N', 'T', 'F', 'T', '6', 'H', 'E', 'O', 'R', 'E', 'M', 'S', 'H', '3', 'E', 'W', 'A', 'Y', 'O', 'F', 'L', 'O', 'R', 'G', 'E', 'T', '5', 'T', 'H', 'E'};
        char Expectedstr[54] = {'1', 'E', 'F', 'M', 'O', 'T', 'H', 'R', 'M', 'A', '2', 'T', 'E', 'A', 'I', 'I', 'S', 'T', '4', 'I', 'F', 'E', 'D', 'O', 'N', 'T', 'F', 'T', '6', 'H', 'F', 'A', '3', 'E', 'M', 'S', 'H', 'I', 'E', 'W', 'C', 'Y', 'O', 'S', 'L', 'O', 'R', 'G', 'E', 'T', '5', 'T', 'H', 'E'};

        Cube cube(str);
        Cube Expectedcube(Expectedstr);

        std::vector<CubeOP> key;
        CubeOP op = {'C', 1};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube,Expectedcube);
    }
    {
        char str[54] = {'1', 'I', 'F', 'M', 'A', 'T', 'H', 'E', 'M', 'A', '2', 'T', 'I', 'C', 'S', 'I', 'S', 'T', '4', 'I', 'F', 'E', 'D', 'O', 'N', 'T', 'F', 'T', '6', 'H', 'E', 'O', 'R', 'E', 'M', 'S', 'H', '3', 'E', 'W', 'A', 'Y', 'O', 'F', 'L', 'O', 'R', 'G', 'E', 'T', '5', 'T', 'H', 'E'};
        char Expectedstr[54] = {'1', 'I', 'F', 'M', 'A', 'T', 'H', 'E', 'M', 'A', '2', 'H', 'I', 'C', 'R', 'I', 'S', 'S', '4', 'I', 'T', 'E', 'D', 'E', 'N', 'T', 'O', 'T', '6', 'T', 'E', 'O', 'S', 'E', 'M', 'T', 'H', '3', 'E', 'W', 'A', 'Y', 'O', 'F', 'L', 'F', 'R', 'G', 'O', 'T', '5', 'F', 'H', 'E'};

        Cube cube(str);
        Cube Expectedcube(Expectedstr);

        std::vector<CubeOP> key;
        CubeOP op = {'L', 5};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube,Expectedcube);
    }
    
}

int main(int ac, char **av) {

    srand((unsigned) time(NULL));

    printf("\n----encode_test----\n");
    encode_test();

    printf("\n----key_test----\n");
    key_test();

    printf("\n----rotate_test----\n");
    rotate_test();

    return 0;
}