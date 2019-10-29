#include <iostream>
#include <cstdlib>
#include "Newcubing.cpp"
int main(void) {
    srand((unsigned)time(NULL));
    // 推奨すべき鍵の長さ測定
    for(int keylen = 3; keylen <= 300; keylen += 3) {
        int transnum[100] = {0};//転置回数
        for(int i = 0; i < 100; i++) { //100回試行する
            //ここの処理書いて~~
        }
        int sum = 0;
        for(int i = 0; i < 100; i++) {
            sum += transnum[i];
        }
        double ave = sum / 45.0;
        printf("keylen:%4d, ave:%4f\n", keylen, ave);
    }
}