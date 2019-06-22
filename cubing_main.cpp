#include <vector>

struct Cube {
    std::vector<std::vector<char>> cubing;
    Cube () {
      // write here
    }
  
    void shuffle() {
        for(int i = cubing.size() - 1; i > 0; i--) {
            int j = rand() % i;
            for(int k = 0; k < 54; k++) {
                char c = cubing[i][k];
                cubing[i][k] = cubing[j][k];
                cubing[j][k] = c;
            }    
        }
    }
  
    void print() {
        for(int i = 0; i < cubing.size(); i++){
            for(int j = 0; j < cubing[i].size(); j++){
                printf("%c",cubing[i][j]);
            }
        }
        printf("\n");
    }
};

int main(int ac, char **av) {
    Cube cube;
    cube.shuffle();
    cube.print();
    return 0;
}