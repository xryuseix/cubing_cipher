#include <vector>

using CubeType = std::vector<std::vector<char>>;

struct Cube {
    CubeType cubing;
    Cube () {
      // write here
    }
  
    void encryupt() {
        cubing = hash(cubing);
        cubing = sequential(cubing);
        cubing = randnum(cubing);
        cubing = cubing_en(cubing, key);
        cubing = shuffle(cubing);
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
    cube.encryupt();
    cube.print();
    return 0;
}