#include <iostream>
#include <vector>

struct CubeOP {
    int direction;
    int column;
    int times;
};

struct Cube {
    std::vector<char> cubing;

    Cube (int slength, char* str, int klength, CubeOP* key) {
        for(int i = 0; i < slength; i++) {
            cubing.push_back(str[i]);
        }
        for(int i = slength; i < 54; i++) {
            cubing.push_back('*');
        }
    }
  
    void rotate() {
        
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
    CubeOP key[100];
    CubeOP op = {1,2,3};
    key[0] = op;

    Cube cube(5, str, 1, key);
    cube.rotate();
    cube.print();
    return 0;
}