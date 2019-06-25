#include <iostream>
#include <vector>

struct Cube {
    std::vector<char> cubing;
    std::vector<char> key;

    Cube (int slength, char* str, int klength, char* pkey) {
        for(int i = 0; i < slength; i++) {
            cubing.push_back(str[i]);
        }
        for(int i = slength; i < 54; i++) {
            cubing.push_back('*');
        }
        for(int i = 0; i < klength; i++) {
            key.push_back(pkey[i]);
        }
        for(int i = 0; i < klength%3; i++) {
            key.pop_back();
        }
    }
  
    void shuffle() {
        for(int n = 0; n < key.size(); n++) { // keyはkey.len回文字を変えて暗号化する
            for(int i = 0; i < key.size(); i = i + 3) { // 転置
                int num = 2 + key[i + 2] - '3'; // 型変換('1'->0,'2'->1)
                char letter;
                
                if(key[i] == '1') { // 方向 // 縦方向 
                    for(int k = 0; k < 3 - ('3' - key[i + 2]); k++) { // 回数 
                        letter=cubing[0 + num]; // numは転値対象列(0~2)
                        
                        // ここの変則的な数字は配列にしてもいい
                        // が、ネストが増える上にプログラムの意味がわからなくなりそうなので残す
                        
                        cubing[0 + num] = cubing[3 + num];
                        cubing[3 + num] = cubing[6 + num];
                        cubing[6 + num] = cubing[12 + num];
                        cubing[12 + num] = cubing[24 + num];
                        cubing[24 + num] = cubing[36 + num];
                        cubing[36 + num] = cubing[45 + num];
                        cubing[45 + num] = cubing[48 + num];
                        cubing[48 + num] = cubing[51 + num];
                        cubing[51 + num] = cubing[44 - num];
                        cubing[44 - num] = cubing[32 - num];
                        cubing[32 - num] = cubing[20 - num];
                        cubing[20 - num] = letter;
                    }
                } else if(key[i] == '2'){ // 横方向
                    for(int k = 0; k < 3 - ('3' - key[i + 2]); k++) {
                        letter = cubing[9 + 12*num];
                        for(int m = 0; m < 11; m++) {
                          cubing[9 + 12*num + m] = cubing[10 + 12*num + m];
                        }
                        cubing[20 + 12*num] = letter;
                    }
                } else if(key[i] == '3') { // 回転方向
                    for(int k = 0; k < 3 - ('3' - key[i + 2]); k++) {
                        letter = cubing[6 - 3*num];
                        cubing[6 - 3*num] = cubing[7 - 3*num];
                        cubing[7 - 3*num] = cubing[8 - 3*num];
                        cubing[8 - 3*num] = cubing[15 + num];
                        cubing[15 + num] = cubing[27 + num];
                        cubing[27 + num] = cubing[39 + num];
                        cubing[39 + num] = cubing[47 + 3*num];
                        cubing[47 + 3*num] = cubing[46 + 3*num];
                        cubing[46 + 3*num] = cubing[45 + 3*num];
                        cubing[45 + 3*num] = cubing[35 - num];
                        cubing[35 - num] = cubing[23 - num];
                        cubing[23 - num] = cubing[11 - num];
                        cubing[11 - num] = letter;
                    }
                }
            }
        }
        //鍵を１文字ずらす
        key.push_back(key[0]);
        for(int i = 0; i < key.size()-1; i++) {
            key[i] = key[i + 1];
        }
        key.pop_back();
    }
  
    void print() {
        for(int i = 0; i < cubing.size(); i++) {
            printf("%c",cubing[i]);
        }
        printf("\n");
    }
};

int main(int ac, char **av) {
    char str[45] = {'a','b','c','d','e'};
    char pkey[100] = {'1','1','2'}; 
    Cube cube(5, str, 3, pkey);
    cube.shuffle();
    cube.print();
    return 0;
}