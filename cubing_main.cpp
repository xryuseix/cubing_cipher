#include <iostream>

struct CubeOP {
    int direction;
    int column;
    int times;
};

struct Cube {
    char cubing[54];

    Cube (char* str, int slength) {
        for(int i = 0; i < slength; i++) {
            cubing[i]=str[i];
        }
        for(int i = slength; i < 54; i++) {
            cubing[i]='*';
        }
    }
  
    void rotate(CubeOP* key, int klength) {
        for(int i = 0; i < klength; i = i + 3) { // 転置
            char letter;
            int col = key[i].column - 1;
            if(key[i].direction == 1) { // 方向 // 縦方向 
                for(int k = 0; k < key[i].times; k++) { // 回数 

                    letter=cubing[0 + col]; // colは転値対象列(0~2)
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
  
    void print() {
        for(int i = 0; i < 54; i++) {
            printf("%c",cubing[i]);
        }
        printf("\n");
    }
};

bool isEqual(Cube a, Cube b){
    return true;
}

int main(int ac, char **av) {
    char str[45] = {'a','b','c','d','e'};
    CubeOP key[100];
    CubeOP op = {1,2,3};
    key[0] = op;
    //std::vector<Key> key = genKey();

    Cube cube(str, 5);
    //encode(cube, str);
    cube.rotate(key, 1);
    //decode(cube, res);
    cube.print();
    return 0;
}