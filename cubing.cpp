#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

using CubeType = std::vector<std::vector<char>>;

void outputfn(std::string);
std::string inputfn();
std::string cubing_key();
CubeType cubing_en(CubeType, std::string);
CubeType string_to_cubing(std::string);
std::string cubing_to_string(CubeType);
CubeType shuffle(CubeType);
CubeType sequential(CubeType);
CubeType hash(CubeType);
CubeType randnum(CubeType);

// メモ
// g++ -std=c++1z cuning.cpp

std::string InputFileName="input.txt";
std::string OutputFileName="output.txt";
time_t timer; // 経過時間を表示する為の宣言
struct tm *t_st;

struct Cube {
    std::string plain;
    std::string cipher;
    std::string key;
    CubeType cubing;

    void Input() {
        plain = inputfn();
    }
    void Output() {
        outputfn(cipher);
    }
    void Cubing_key() {
        key = cubing_key();
    }
    void String_to_Cubing() {
        cubing = string_to_cubing(plain);
    }
    void Cubing_to_String() {
        cipher = cubing_to_string(cubing);
    }
    void Cubing_encrypt() {
        cubing = cubing_en(cubing, key);
    }
    void Shuffle() {
        cubing = shuffle(cubing);
    }
    void Hash() {
        cubing = hash(cubing);
    }
    void Sequential() {
        cubing = sequential(cubing);
    }
    void Randnum() {
        cubing = randnum(cubing);
    }
};

int main(void) {
    Cube cube;

    cube.Input();
    cube.Cubing_key();
    cube.String_to_Cubing();
    cube.Hash();
    cube.Sequential();
    cube.Randnum();
    cube.Cubing_encrypt();
    cube.Shuffle();
    cube.Cubing_to_String();
    cube.Output();

    return 0;
}

std::string inputfn() { // 文字入力関数
    std::string s = "", buf;
    std::ifstream reading_file(InputFileName);

    while (!reading_file.eof()) {
        getline(reading_file, buf);
        s += buf + "\n";
    }

    s = s.substr(0, s.length() - 1);
    std::cout << s << std::endl;
    std::cout << std::endl << "が入力されました" << std::endl;
    return s;
}

void outputfn(std::string s) { //文字出力関数
    std::ofstream writing_file;
    writing_file.open(OutputFileName, std::ios::out); // ファイル読み込み
    writing_file << s; //ファイル出力
    std::cout << "ファイルへの出力が完了しました" << std::endl;
}

std::string cubing_key() {
    std::cout << std::endl << "転置鍵を入力してください" << std::endl;
    std::string key;
    std::cin >> key;
    key = key.substr(0, key.length() - key.length() % 3); // keyの長さを3の倍数にする
    return key;
}

CubeType string_to_cubing(std::string s) {
    CubeType cubing(s.length()/46 + 1, std::vector<char>(54));

    for(int i = 0; i < s.length()/46 + 1; i++) { // 平文をcubing配列に格納
        for(int j = 0; j < 45; j++) {
            cubing[i][j] = s[i*45 + j];
        }
    }

    for(int i = 44; i >= s.length() % 46; i--) {
        cubing[cubing.size() - 1][i] = '*'; // 末尾に＊をつける
    }
    return cubing;
}

CubeType cubing_en(CubeType cubing, std::string key) {
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

    for(int n = 0; n < key.length(); n++) { // keyはkey.len回文字を変えて暗号化する
        for(int j = 0; j < cubing.size(); j++) { // 行数回ループ
            for(int i = 0; i < key.length(); i = i + 3) { // 転置
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

std::string cubing_to_string(CubeType cubing) {
    std::string s = "";
    for(int i = 0; i < cubing.size(); i++) { // 出力用 
        for(int j = 0; j < 54; j++) {
            s += cubing[i][j];
        }
    }
    return s;
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