#include <iostream>
#include <vector> //後でけす
#include <chrono>
// ここで暗号化プログラムを読みこむ
#include "Newcubing.cpp"

int main(){

    const int N = 10;
    // double sec[N];
    std::vector<double> sec(N);
    for(int calcnum = 0; calcnum < N; calcnum++) { //測定はN回行う

        double lastsec = 0.0;
        int times = 0;
        double msec = 0.0;

        while(1){
            std::clock_t c_start = std::clock();      // 計測スタート時刻を保存
            /* ここに暗号化処理 */
            times++;
            usecubing_en();
            usecubing_de(); // 呼び出す関数

            std::clock_t c_end = std::clock();       // 計測終了時刻を保存
            auto dur = c_end - c_start;        // 要した時間を計算
            msec += 1000.0 * dur / CLOCKS_PER_SEC; // 要した時間をミリ秒（1/1000秒）に変換して表示

            if(msec > 3000) { // 3秒で終了
                break;
            }
            lastsec = static_cast<int> (msec)/1000.0; // lastsecは秒単位
        }
        // 要した時間をミリ秒（1/1000秒）に変換して表示
        std::cout << lastsec << " sec " << times - 1 << " times\n";
        // std::cout << calcnum << " " << N << " " << times << std::endl;
        sec[calcnum] = times;
    }

    double timesum = 0;
    for(int i = 0; i < N; i++) {
        //平均算出
        timesum += sec[i];
    }
    std::cout << timesum/N << std::endl;

    // ↓読みにくいので今はコメントアウト
    // std::cout << "Doing cubing cubingmode for 3s on N size blocks: " << times << "cubing cubingmode's in " << lastsec << "s\n";
    /*
    こうゆうのが出したい
    Doing aes-128 cbc for 3s on 16 size blocks: 22208501 aes-128 cbc's in 2.81s
    */
    return 0;
}