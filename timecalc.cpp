#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h> // usleep関数を入れている間だけ
// ここで暗号化プログラムを読みこむ

int main(){
    double lastsec = 0.0;
    int times;

    // ここで鍵・平文を読み込む

    auto start = std::chrono::system_clock::now();      // 計測スタート時刻を保存
    while(1){

        /* ここに暗号化処理 */
        usleep(50*1000);// 暗号化処理の代わり
        times++;


        auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
        auto dur = end - start;        // 要した時間を計算
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count(); // 要した時間をミリ秒（1/1000秒）に変換して表示

        if(msec > 3000) { // 3秒で終了
            break;
        }
        lastsec = static_cast<int> (msec)/1000.0; // lastsecは秒単位
    }
    // 要した時間をミリ秒（1/1000秒）に変換して表示
    std::cout << lastsec << " sec " << times - 1 << " times\n";

    // ↓読みにくいので今はコメントアウト
    // std::cout << "Doing cubing cubingmode for 3s on N size blocks: " << times << "cubing cubingmode's in " << lastsec << "s\n";
    /*
    こうゆうのが出したい
    Doing aes-128 cbc for 3s on 16 size blocks: 22208501 aes-128 cbc's in 2.81s
    */
    return 0;
}