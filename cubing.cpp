#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
// #include "encrypt.h"

using CubeType = std::vector<std::vector<char>>;

// メモ
// g++ -std=c++1z cubing.cpp

char InputFileName[] = "input.txt";
char OutputFileName[] = "output.txt";
time_t timer; // 経過時間を表示する為の宣言
struct tm *t_st;

int cubing_key(char *key) {
    std::cout << std::endl << "転置鍵を入力してください" << std::endl;
    char c;
    int idx = 0;
    
    scanf("%s", key);

    while(key[idx] != '\0'){
        idx++;
    }
    idx = idx - idx%3; // keyの長さを3の倍数にする
    return idx;
}

void outputfn(std::string s) { //文字出力関数
    std::ofstream writing_file;
    writing_file.open(OutputFileName, std::ios::out); // ファイル読み込み
    writing_file << s; //ファイル出力
    std::cout << "ファイルへの出力が完了しました" << std::endl;
}

int main(void) {
    char str[46];
    char key[46];
    char c;
    int strlen;
    int keylen;

    FILE *fp;
    fp = fopen(InputFileName, "r");

    strlen = 0;

    while((c = fgetc(fp)) != EOF) {
        str[strlen] = c;
        strlen++;
    }

    printf("%s\n", str);
    printf("\nが入力されました\n");

    keylen = cubing_key(key);
    
    struct Cube cube = { &str[46], &key[46], &strlen, &keylen };
    cube.Cubing_encrypt();

    outputfn(str);

    return 0;
}