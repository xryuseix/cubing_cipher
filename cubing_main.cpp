#include <vector>

struct Cube {
    std::vector<char> cubing;

    Cube (int length, char* str) {
        for(int i = 0; i < length; i++) {
            cubing.push_back(str[i]);
        }
        for(int i = length; i < 54; i++) {
            cubing.push_back('*');
        }
    }
  
    void shuffle() {
        //
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
    Cube cube(5, str);
    cube.shuffle();
    cube.print();
    return 0;
}