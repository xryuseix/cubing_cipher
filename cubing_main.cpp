#include <vector>

using CubeType = std::vector<std::vector<char>>;

struct Cube {
    CubeType cube;
    Cube () {
      // write here
    }
  
    void shuffle() {
      // write here
    }
  
    void print() {
        for(int i = 0; i < cube.size(); i++){
            for(int j = 0; j < cube[i].size(); j++){
                printf("%c",cube[i][j]);
            }
        }
    }
};

int main(int ac, char **av) {
    Cube cube;
    cube.shuffle();
    cube.print();
    return 0;
}