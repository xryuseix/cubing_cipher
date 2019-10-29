#include <iostream>
#include <cstdlib>
#include "Newcubing.cpp"
void keylen_encrypt(const std::vector<CubeOP>& key, std::vector<char> (&str), std::vector<char> (&ct)) {

    std::vector<char> pt;
    for(int i = 0; i < str.size(); i++) {
        pt.push_back(str[i]);
    }
    if(pt.size()%45 != 0) {
        pt.push_back('\0');
    }
    while(pt.size()%45 != 0) { //パディング処理
        int chartype = rand()%62;
        pt.push_back(base62_table[chartype]);
    }

    char plainblock[45];
    char encoded_block[54];
    char cipherblock[54];
    std::vector<char> tmp;

    for(int j = 0; j < 45; j++) { //平文から平文ブロック作成
        plainblock[j] = pt[j];
    }
    
    encoding(plainblock, encoded_block, 0);
    encrypt(key, encoded_block, cipherblock);
    for(int i = 0; i < 45; i++) {
        ct[i] = cipherblock[i];
    }



    return;
}

int main(void) {
    srand((unsigned)time(NULL));
    // 推奨すべき鍵の長さ測定
    std::vector<char> pt{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r'};
    for(int keylen = 3; keylen <= 300; keylen += 3) {
        //鍵の生成
        std::vector<CubeOP> key;
        CubeOP op = {1, 2, 1};
        for(int i = 0; i < keylen/3; i++) {
            op.direction = 1 + rand()%3;
            op.column = 1 + rand()%3;
            op.times = 1 + rand()%3;
            key.push_back(op);
        }
        int transnum[100];//転置回数
        for(int i = 0; i < 100; i++) { //100回試行する
            //転置
            std::vector<char> ct(pt.size());
            keylen_encrypt(key, pt, ct);
            //比較
            int same = 0;
            for(int j = 0; j < pt.size(); j++) {
                if(pt[j] == ct[j]) {
                    same++;
                }
            }
            // printf("-------\n");
            // for(int j=0;j<ct.size();j++){
            //     printf("%c",ct[j]);
            // }
            // printf("\n----------\n");
            transnum[i] = same;
        }
        int sum = 0;
        for(int i = 0; i < 100; i++) {
            sum += transnum[i];
        }
        double ave = sum / 100.0 / 45.0 * 100;
        //一致率
        // printf("keylen:%4d, ave:%4f\n", keylen, ave);
        printf("%d,%f\n", keylen, ave);
    }
}