#include <vector>

using CubeType = std::vector<std::vector<char>>;

CubeType string_to_cubing(char, int);
char cubing_to_string(CubeType);
CubeType cubing_en(CubeType, char);
CubeType shuffle(CubeType);
CubeType sequential(CubeType);
CubeType hash(CubeType);
CubeType randnum(CubeType);

struct Cube {
    char *str;
    char *key;
    int *strlen;
    int *keylen;
    CubeType cubing;

    void Cubing_encrypt() {
        cubing = string_to_cubing(str, strlen);
        cubing = hash(cubing);
        cubing = sequential(cubing);
        cubing = randnum(cubing);
        cubing = cubing_en(cubing, *key);
        cubing = shuffle(cubing);
        *str = cubing_to_string(cubing);
    }
};

CubeType string_to_cubing(char *str, int *strlen) {
    CubeType cubing(*strlen/46 + 1, std::vector<char>(54));

    for(int i = 0; i < *strlen/46 + 1; i++) { // 平文をcubing配列に格納
        for(int j = 0; j < 45; j++) {
            cubing[i][j] = str[i*45 + j];
        }
    }

    for(int i = 44; i >= *strlen % 46; i--) {
        cubing[cubing.size() - 1][i] = '*'; // 末尾に＊をつける
    }
    return cubing;
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
            cubing[i][52]=rand()%26 + 'a';
        }
        
        if(rand() % 10 == 0) {
            cubing[i][53] = rand() % 26 + 'A';
        } else {
            cubing[i][53] = rand() % 26 + 'a';
        }
    }
	return cubing;
}

CubeType cubing_en(CubeType cubing, char key, int strlen, int keylen) {
    /*
    //Visualizer
    //配列の中の数字がどのように格納されているのか見てわかるように表示する
    //デバッグ用
    std::cout << "平文" << std::endl;
    for(int i = 0; i <= cubing.size()/45; i++) {
        for(j = 0; j < 54; j++) {
            if(j == 0 || j == 3 || j == 6 || j == 45 || j == 48 || j == 51) {
                std::cout << "   " ;
            }
            std::cout << cubing[i][j];
            if(j == 2 || j == 5 || j == 8 || j == 20 || j == 32 || j == 44 || j == 47 || j == 50 || j == 53) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;;
    }
    */
/* 
    for(int n = 0; n < keylen; n++) { // keyはkey.len回文字を変えて暗号化する
        for(int j = 0; j < cubing.size(); j++) { // 行数回ループ
            for(int i = 0; i < keylen; i = i + 3) { // 転置
                int num = 2 + key[i + 2] - '3'; // 型変換('1'->0,'2'->1)
                char letter;
                
                if(key[i] == '1') { // 方向 // 縦方向 
                    for(int k = 0; k < 3 - ('3' - key[i + 2]); k++) { // 回数 
                        letter=cubing[j][0 + num]; // numは転値対象列(0~2)
                        
                        // ここの変則的な数字は配列にしてもいい
                        // が、ネストが増える上にプログラムの意味がわからなくなりそうなので残す
                        
                        cubing[j][0 + num] = cubing[j][3 + num];
                        cubing[j][3 + num] = cubing[j][6 + num];
                        cubing[j][6 + num] = cubing[j][12 + num];
                        cubing[j][12 + num] = cubing[j][24 + num];
                        cubing[j][24 + num] = cubing[j][36 + num];
                        cubing[j][36 + num] = cubing[j][45 + num];
                        cubing[j][45 + num] = cubing[j][48 + num];
                        cubing[j][48 + num] = cubing[j][51 + num];
                        cubing[j][51 + num] = cubing[j][44 - num];
                        cubing[j][44 - num] = cubing[j][32 - num];
                        cubing[j][32 - num] = cubing[j][20 - num];
                        cubing[j][20 - num] = letter;
                    }
                } else if(key[i] == '2'){ // 横方向
                    for(int k = 0; k < 3 - ('3' - key[i + 2]); k++) {
                        letter = cubing[j][9 + 12*num];
                        for(int m = 0; m < 11; m++) {
                          cubing[j][9 + 12*num + m] = cubing[j][10 + 12*num + m];
                        }
                        cubing[j][20 + 12*num] = letter;
                    }
                } else if(key[i] == '3') { // 回転方向
                    for(int k = 0; k < 3 - ('3' - key[i + 2]); k++) {
                        letter = cubing[j][6 - 3*num];
                        cubing[j][6 - 3*num] = cubing[j][7 - 3*num];
                        cubing[j][7 - 3*num] = cubing[j][8 - 3*num];
                        cubing[j][8 - 3*num] = cubing[j][15 + num];
                        cubing[j][15 + num] = cubing[j][27 + num];
                        cubing[j][27 + num] = cubing[j][39 + num];
                        cubing[j][39 + num] = cubing[j][47 + 3*num];
                        cubing[j][47 + 3*num] = cubing[j][46 + 3*num];
                        cubing[j][46 + 3*num] = cubing[j][45 + 3*num];
                        cubing[j][45 + 3*num] = cubing[j][35 - num];
                        cubing[j][35 - num] = cubing[j][23 - num];
                        cubing[j][23 - num] = cubing[j][11 - num];
                        cubing[j][11 - num] = letter;
                    }
                }
            }
        }
        key = key.substr(1) + key[0]; // 鍵を１文字ずらす
    }
*/
    /*
    //Visualizer    
    std::cout << "暗号文" << std::endl;
    for(j = 0; j < cubing.size(); j++) {
        for(int k = 0; k < 54; k++) {
            if(k == 0 || k == 3 || k == 6 || k == 45 || k == 48 || k == 51) {
                std::cout << "   ";
            }
            std::cout << cubing[j][k];
            if(k == 2 || k == 5 || k == 8 || k == 20 || k == 32 || k == 44 || k == 47 || k == 50 || k == 53) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    */
    return cubing;
}

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

char cubing_to_string(CubeType cubing) {
    char s[46] = "";
    for(int i = 0; i < cubing.size(); i++) { // 出力用 
        for(int j = 0; j < 54; j++) {
            //s += cubing[i][j];
        }
    }
    return *s;
}