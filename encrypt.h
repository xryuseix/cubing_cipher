#include <vector>
#include <string>

using CubeType = std::vector<std::vector<char>>;

CubeType string_to_cubing(std::string);
std::string cubing_to_string(CubeType);
CubeType cubing_en(CubeType, std::string);
CubeType shuffle(CubeType);
CubeType sequential(CubeType);
CubeType hash(CubeType);
CubeType randnum(CubeType);

struct Cube {
    std::string *str;
    std::string *key;
    CubeType cubing;

    void Cubing_encrypt() {
        cubing = string_to_cubing(*str);
        cubing = hash(cubing);
        cubing = sequential(cubing);
        cubing = randnum(cubing);
        cubing = cubing_en(cubing, *key);
        cubing = shuffle(cubing);
        *str = cubing_to_string(cubing);
    }
};

// Fisher–Yates
CubeType shuffle(CubeType ary) {

    for(int i = ary.size() - 1; i > 0; i--) {
        int j = rand() % i;
        for(int k = 0; k < 54; k++) {
            char c = ary[i][k];
            ary[i][k] = ary[j][k];
            ary[j][k] = c;
        }    
    }
    return ary;
}

std::vector<std::vector<char> > hash(CubeType cubing){
    for(int j = 0; j < cubing.size(); j++) { //ハッシュ計算
        for(int i = 0; i < 5; i++) { //5面 
            int sum = 0;
            for(int k = 0; k < 9; k++) { //9文字 
                sum += cubing[j][i*9 + k];
            }
            sum = sum%26 + 97;
            cubing[j][45 + i] = sum; //ハッシュ代入
        }
    }
    return cubing;
}

std::vector<std::vector<char> > sequential(CubeType cubing) {
    for(int i = 0; i < cubing.size(); i++) { //シーケンス番号
        if(i < 26*52) {
            cubing[i][50] = 'A' + (i/26);
        } else {
            cubing[i][50] = 'a' + (i/26);
        }

        if(i < 25) {
            cubing[i][51] = 'A' + (i%26);
        } else {
            cubing[i][51] = 'a' + (i%26);
        }
    }
    return cubing;
}

std::vector<std::vector<char> > randnum(CubeType cubing){
    for(int i = 0; i < cubing.size(); i++) { // 乱数文字付与
        if(rand() % 10 == 0) {
            cubing[i][52] = rand() % 26 + 'A'; // 小文字or大文字の乱数
        } else {
            cubing[i][52]=rand()%26+'a';
        }
        
        if(rand() % 10 == 0) {
            cubing[i][53] = rand() % 26 + 'A';
        } else {
            cubing[i][53] = rand() % 26 + 'a';
        }
    }
	return cubing;
}