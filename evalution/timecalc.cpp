#include <iostream>
#include <vector>
#include <chrono>
#include "Newcubing.cpp"

std::vector<char> pt;
std::vector<char> ct;
std::vector<CubeOP> key;

void file_input() {
    char InputFileName[] = "./io/input.txt";
    char KeyFileName[] = "./io/key.txt";

    { //plain input
        FILE *fp;
        fp = fopen(InputFileName, "r");

        char c;
        while((c = fgetc(fp)) != EOF) {
            pt.push_back(c);
        }
        fclose(fp);
    }
    int keysize=30;

    { //key input
        FILE *fp;
        fp = fopen(KeyFileName, "w");

        for(int i = 0; i < key.size(); i++) {
            fprintf(fp, "%d%d%d", key[i].direction, key[i].column, key[i].times);
        }
        fclose(fp);
    }
}

int main(){

    std::vector<int> iv1, iv2; //暗号化用配列
    double msec = 0.0; // 計測時間
    file_input(); // 入力時間は計測しない

    std::clock_t c_start = std::clock();      // 計測スタート時刻を保存

    /* ここに暗号化処理 */
    cubingmode_en(key, pt, ct, iv1, iv2);

    std::clock_t c_end = std::clock();       // 計測終了時刻を保存
    
    msec = (c_end - c_start) / (double)CLOCKS_PER_SEC; // 要した時間をミリ秒（1/1000秒）に変換して表示

    // 要した時間をミリ秒（1/1000秒）に変換して表示
    std::cout << msec << " sec " << pt.size() << " Bytes\n";

    return 0;
}