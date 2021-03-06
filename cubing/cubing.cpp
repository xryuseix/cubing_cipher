#include <cmath>
#include <iostream>
#include <vector>

struct CubeOP {
    int direction;
    int column;
    int times;
};

struct Cube {
    char cubing[54];

    Cube(const char (&str)[54]) {
        for (int i = 0; i < 54; i++) {
            cubing[i] = str[i];
        }
    }

    void rotate(const CubeOP& key) {
        char letter;
        const int col = key.column - 1;
        if (key.direction == 1) {                      // 方向 // 縦方向
            for (int k = 0; k < key.times * 3; k++) {  // 回数
                letter = cubing[0 + col];  // colは転値対象列(0~2)
                cubing[0 + col] = cubing[3 + col];
                cubing[3 + col] = cubing[6 + col];
                cubing[6 + col] = cubing[12 + col];
                cubing[12 + col] = cubing[24 + col];
                cubing[24 + col] = cubing[36 + col];
                cubing[36 + col] = cubing[45 + col];
                cubing[45 + col] = cubing[48 + col];
                cubing[48 + col] = cubing[51 + col];
                cubing[51 + col] = cubing[44 - col];
                cubing[44 - col] = cubing[32 - col];
                cubing[32 - col] = cubing[20 - col];
                cubing[20 - col] = letter;
            }
        } else if (key.direction == 2) {               // 横方向
            for (int k = 0; k < key.times * 3; k++) {  // 回数
                letter = cubing[9 + 12 * col];
                for (int m = 0; m < 11; m++) {
                    cubing[9 + 12 * col + m] = cubing[10 + 12 * col + m];
                }
                cubing[20 + 12 * col] = letter;
            }
        } else if (key.direction == 3) {               // 回転方向
            for (int k = 0; k < key.times * 3; k++) {  // 回数
                letter = cubing[6 - 3 * col];
                cubing[6 - 3 * col] = cubing[7 - 3 * col];
                cubing[7 - 3 * col] = cubing[8 - 3 * col];
                cubing[8 - 3 * col] = cubing[15 + col];
                cubing[15 + col] = cubing[27 + col];
                cubing[27 + col] = cubing[39 + col];
                cubing[39 + col] = cubing[47 + 3 * col];
                cubing[47 + 3 * col] = cubing[46 + 3 * col];
                cubing[46 + 3 * col] = cubing[45 + 3 * col];
                cubing[45 + 3 * col] = cubing[35 - col];
                cubing[35 - col] = cubing[23 - col];
                cubing[23 - col] = cubing[11 - col];
                cubing[11 - col] = letter;
            }
        }
    }

    bool equals(const Cube& a) const {
        bool equal = true;
        for (int i = 0; i < 54; i++) {
            if (cubing[i] != a.cubing[i]) {
                equal = false;
                break;
            }
        }
        return equal;
    }

    void print() const {
        for (int i = 0; i < 54; i++) {
            printf("%c", cubing[i]);
        }
        printf("\n");
    }
};

const std::string base62_table =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
const static char printable_table[] = {
    '0', '1',  '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',  'c',  'd',
    'e', 'f',  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',  'q',  'r',
    's', 't',  'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',  'E',  'F',
    'G', 'H',  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',  'S',  'T',
    'U', 'V',  'W', 'X', 'Y', 'Z', '!', '"', '#', '$', '%', '&',  '\'', '(',
    ')', '*',  '+', ',', '-', '.', '/', ':', ';', '<', '=', '>',  '?',  '@',
    '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~', ' ', '\n', '\0', '\t'};
const static unsigned int tablesize = sizeof(printable_table) / sizeof(char);

template <class T>
bool Equal(const T& a, const T& b) {
    return a == b;
}

template <>
bool Equal(const Cube& a, const Cube& b) {
    return a.equals(b);
}

template <int N>
bool Equal(const char (&a)[N], const char (&b)[N]) {
    if (strncmp(a, b, N) == 0) {
        return 1;
    } else {
        return 0;
    }
}

template <class T>
void assertEqual(const T& a, const T& b) {
    if (Equal(a, b)) {
        printf("AC\n");
    } else {
        printf("WA\n");
    }
    return;
}

void unit_test() {
    {  //縦方向テスト
        char str[54];
        {
            const std::string _str =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
            _str.copy(str, 54);
        }
        char expected_str[54];
        {
            const std::string _expected_str =
                "ancdzfgLijklmUopqrshuvwxyXABCDEeGHIJK!MNOPQbSTRVWFYZt?";
            _expected_str.copy(expected_str, 54);
        }

        Cube cube(str);
        const Cube expected(expected_str);

        std::vector<CubeOP> key;
        const CubeOP op = {1, 2, 1};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube.cubing, expected.cubing);
    }

    {  //横方向テスト
        char str[54];
        {
            const std::string _str =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
            _str.copy(str, 54);
        }
        char expected_str[54];
        {
            const std::string _expected_str =
                "abcdefghijklmnopqrstuyzABCDEFGvwxHIJKLMNOPQRSTUVWXYZ!?";
            _expected_str.copy(expected_str, 54);
        }
        Cube cube(str);
        const Cube expected(expected_str);

        std::vector<CubeOP> key;
        const CubeOP op = {2, 2, 1};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube.cubing, expected.cubing);
    }

    {  //回転方向テスト
        char str[54];
        {
            const std::string _str =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
            _str.copy(str, 54);
        }
        char expected_str[54];
        {
            const std::string _expected_str =
                "abcqCOghijflmnopYrstuvexyzABXDEFGHdJKLMNWPQRSTUVkwIZ!?";
            _expected_str.copy(expected_str, 54);
        }
        Cube cube(str);
        const Cube expected(expected_str);

        std::vector<CubeOP> key;
        const CubeOP op = {3, 2, 1};
        key.push_back(op);

        cube.rotate(key[0]);
        assertEqual(cube.cubing, expected.cubing);
    }
    return;
}

Cube str2cube(const char (&str)[54]) {
    Cube cube(str);
    return std::move(cube);
}

void cube2str(Cube cube, char (&str)[54]) {
    for (int i = 0; i < 54; i++) {
        str[i] = cube.cubing[i];
    }
    return;
}

void en_decode_test() {
    {
        char str[54];
        {
            const std::string _str =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
            _str.copy(str, 54);
        }
        char expected_str[54];
        {
            const std::string _expected_str =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
            _expected_str.copy(expected_str, 54);
        }
        Cube cube = str2cube(str);

        assertEqual(cube.cubing, expected_str);
    }
    {
        char str[54];
        {
            const std::string _str =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
            _str.copy(str, 54);
        }
        char expected_str[54];
        {
            const std::string _expected_str =
                "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
            _expected_str.copy(expected_str, 54);
        }
        char buf[54];

        Cube cube(str);
        cube2str(cube, buf);

        assertEqual(buf, expected_str);
    }
}

void encrypt(const std::vector<CubeOP>& key, const char (&str)[54],
             char (&ct)[54]) {
    Cube cube = str2cube(str);
    for (auto k : key) {
        cube.rotate(k);
    }
    cube2str(cube, ct);
}

void encrypt_test() {
    char str[54];
    {
        const std::string _str =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
        _str.copy(str, 54);
    }
    char expected_str[54];
    {
        const std::string _expected_str =
            "ancdzfgLijklmUopqrshuvwxyXABCDEeGHIJK!MNOPQbSTRVWFYZt?";
        _expected_str.copy(expected_str, 54);
    }
    char ct[54];

    std::vector<CubeOP> key;
    const CubeOP op = {1, 2, 1};
    key.push_back(op);

    encrypt(key, str, ct);
    assertEqual(ct, expected_str);
}

void decrypt(std::vector<CubeOP>& key, const char (&str)[54], char (&pt)[54]) {
    Cube cube = str2cube(str);
    for (int i = key.size() - 1; i >= 0; i--) {
        int beforetimes = key[i].times;
        key[i].times = 4 - key[i].times;
        cube.rotate(key[i]);
        key[i].times = beforetimes;
    }
    cube2str(cube, pt);
}

void decrypt_test() {
    char str[54];
    {
        const std::string _str =
            "ancdzfgLijklmUopqrshuvwxyXABCDEeGHIJK!MNOPQbSTRVWFYZt?";
        _str.copy(str, 54);
    }
    char expected_str[54];
    {
        const std::string _expected_str =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?";
        _expected_str.copy(expected_str, 54);
    }
    char pt[54];

    std::vector<CubeOP> key;
    const CubeOP op = {1, 2, 1};
    key.push_back(op);

    decrypt(key, str, pt);
    assertEqual(expected_str, pt);
}

void encoding(const char (&plainblock)[45], char (&encoded_block)[54],
              const int blocknum) {
    for (int i = 0; i < 45; i++) {
        encoded_block[i] = plainblock[i];
    }
    for (int i = 0; i < 5; i++) {
        int sum = 0;
        for (int j = 0; j < 9; j++) {
            sum += plainblock[i * 9 + j];
        }
        encoded_block[45 + i] = (char)(sum % 26 + 'a');
    }
    encoded_block[50] = base62_table[blocknum / 62];
    encoded_block[51] = base62_table[blocknum % 62];

    const int chartype1 = rand() % 62;
    const int chartype2 = rand() % 62;

    encoded_block[52] = base62_table[chartype1];
    encoded_block[53] = base62_table[chartype2];
}

void encoding_test() {
    char encoded_block[54];
    char plainblock[45];
    {
        std::string _plainblock =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRS";
        _plainblock.copy(plainblock, 45);
    }
    encoding(plainblock, encoded_block, 0);

    char before_random_block[52];
    for (int i = 0; i < 52; i++) {  //後ろのrand以外をコピー
        before_random_block[i] = encoded_block[i];
    }
    char expectedblock[52];
    {
        std::string _expectedblock =
            "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSzczgjAA";
        _expectedblock.copy(expectedblock, 52);
    }
    assertEqual(before_random_block, expectedblock);
}

void en_masking1(const char (&plain)[45], char (&masked)[45],
                 std::vector<int>(&iv)) {
    for (int i = 0; i < 45; i++) {
        iv.push_back(rand() % tablesize);
        const int dis = static_cast<int>(
            std::distance(std::begin(printable_table),
                          std::find(std::begin(printable_table),
                                    std::end(printable_table), plain[i])));
        const int idx = (iv[iv.size() - 1] + dis) % tablesize;
        masked[i] = printable_table[idx];
    }
}

void en_masking2(const char (&plain)[54], char (&masked)[54],
                 std::vector<int>(&iv)) {
    for (int i = 0; i < 45; i++) {
        masked[i] = plain[i];
    }
    for (int i = 45; i < 52; i++) {
        iv.push_back(rand() % tablesize);
        const int dis = static_cast<int>(
            std::distance(std::begin(printable_table),
                          std::find(std::begin(printable_table),
                                    std::end(printable_table), plain[i])));
        const int idx = (iv[iv.size() - 1] + dis) % tablesize;
        masked[i] = printable_table[idx];
    }
    masked[52] = plain[52];
    masked[53] = plain[53];
}

void de_masking1(std::vector<char>(&plain), char (&masked)[45],
                 std::vector<int>(&iv), const int nowblock) {
    for (int i = 0; i < 45; i++) {
        const int dis = static_cast<int>(
            std::distance(std::begin(printable_table),
                          std::find(std::begin(printable_table),
                                    std::end(printable_table), plain[i])));
        const int idx = (tablesize + dis - iv[nowblock * 45 + i]) % tablesize;
        masked[i] = printable_table[idx];
    }
}

void de_masking2(const char (&plain)[54], char (&masked)[54],
                 std::vector<int>(&iv), const int nowblock) {
    for (int i = 0; i < 45; i++) {
        masked[i] = plain[i];
    }
    for (int i = 45; i < 52; i++) {
        const int dis = static_cast<int>(
            std::distance(std::begin(printable_table),
                          std::find(std::begin(printable_table),
                                    std::end(printable_table), plain[i])));
        const int idx =
            (tablesize + dis - iv[nowblock * 7 + i - 45]) % tablesize;
        masked[i] = printable_table[idx];
    }
    masked[52] = plain[52];
    masked[53] = plain[53];
}

void shuffle(std::vector<std::vector<char>>(&str)) {
    for (int i = str.size() - 1; i > 0; i--) {
        const int j = rand() % i;
        for (int k = 0; k < 68; k++) {
            std::swap(str[i][k], str[j][k]);
        }
    }
}

void cubingmode_en(const std::vector<CubeOP>& key, std::vector<char>(&str),
                   std::vector<char>(&ct), std::vector<int>(&iv1),
                   std::vector<int>(&iv2)) {
    std::vector<std::vector<char>> ShuffleText;
    std::vector<char> pt;
    for (int i = 0; i < str.size(); i++) {
        pt.push_back(str[i]);
    }
    if (pt.size() % 45 != 0) {
        pt.push_back('\0');
    }
    while (pt.size() % 45 != 0) {  //パディング処理
        const int chartype = rand() % 62;
        pt.push_back(base62_table[chartype]);
    }

    const int blocknum = pt.size() / 45;

    for (int i = 0; i < blocknum; i++) {
        char plain_block[45], encoded_block[54], cipher_block[54];
        char masked_block1[45], masked_block2[54];

        for (int j = 0; j < 45; j++) {  //平文から平文ブロック作成
            plain_block[j] = pt[i * 45 + j];
        }
        en_masking1(plain_block, masked_block1, iv1);
        encoding(masked_block1, encoded_block, i);
        en_masking2(encoded_block, masked_block2, iv2);
        encrypt(key, masked_block2, cipher_block);

        std::vector<char> tmp;
        for (auto ci : cipher_block) {  // char-vector変換
            tmp.push_back(ci);
        }

        for (int j = 0; j < 7;
             j++) {  // ivはint型だが暗号文はchar型なので，型変換
            if (iv2[7 * i + j] < 10) {
                tmp.push_back('0');
                tmp.push_back(iv2[7 * i + j] + '0');
            } else {
                tmp.push_back(iv2[7 * i + j] / 10 + '0');
                tmp.push_back(iv2[7 * i + j] % 10 + '0');
            }
        }
        ShuffleText.push_back(tmp);
    }

    shuffle(ShuffleText);

    for (int i = 0; i < ShuffleText.size(); i++) {
        for (int j = 0; j < 54 + 14; j++) {
            ct.push_back(ShuffleText[i][j]);
        }
    }
}

int sequencenum(char f, char s) {
    const int left = static_cast<int>(std::distance(
        std::begin(base62_table),
        std::find(std::begin(base62_table), std::end(base62_table), f)));
    const int right = static_cast<int>(std::distance(
        std::begin(base62_table),
        std::find(std::begin(base62_table), std::end(base62_table), s)));
    return left * 62 + right;
}

bool sortcomp(const std::vector<char>& l, const std::vector<char>& r) {
    const int leftnum = sequencenum(l[50], l[51]);
    const int rightnum = sequencenum(r[50], r[51]);
    return leftnum < rightnum;
}

void decoding(std::vector<std::vector<char>>& before_shuffle_text,
              std::vector<char>& pt, std::vector<int>& iv) {
    char tmp[45];
    sort(before_shuffle_text.begin(), before_shuffle_text.end(), sortcomp);
    for (int i = 0; i < before_shuffle_text.size(); i++) {
        de_masking1(before_shuffle_text[i], tmp, iv, i);
        for (int j = 0; j < 45; j++) {
            pt.push_back(tmp[j]);
        }
    }
    //パディング削除
    pt.erase(pt.begin() + static_cast<int>(std::distance(
                              std::begin(pt),
                              std::find(std::begin(pt), std::end(pt), '\0'))),
             pt.end());
}

void cubingmode_de(std::vector<CubeOP>& key, const std::vector<char>& str,
                   std::vector<char>& pt) {
    std::vector<char> ct;
    std::vector<int> iv1, tmpiv2, iv2;

    for (int i = 0; i < str.size() / 158 * 68;
         i++) {  //暗号文68/158がct+iv2,残りがiv1
        if (i % 68 < 54) {
            ct.push_back(str[i]);
        } else {
            tmpiv2.push_back(str[i] - '0');
        }
    }

    for (int i = str.size() / 158 * 68; i < str.size(); i += 2) {
        iv1.push_back((str[i] - '0') * 10 + (str[i + 1] - '0'));
    }

    for (int i = 0; i < tmpiv2.size() - 1; i += 2) {
        iv2.push_back(tmpiv2[i] * 10 + tmpiv2[i + 1]);
    }

    if (ct.size() % 54 != 0 || iv2.size() % 7 != 0) {
        printf("decryption error\n");
        return;
    }

    const int blocknum = ct.size() / 54;
    std::vector<std::vector<char>> before_shuffle_text;
    for (int i = 0; i < blocknum; i++) {
        char cipherblock[54];
        char decrypted_block[54];
        char masked[54];
        std::vector<char> tmp;

        for (int j = 0; j < 54; j++) {  //暗号文から暗号文ブロック作成
            cipherblock[j] = ct[i * 54 + j];
        }
        decrypt(key, cipherblock, decrypted_block);

        de_masking2(decrypted_block, masked, iv2, i);

        for (int j = 0; j < 54; j++) {
            tmp.push_back(masked[j]);
        }
        before_shuffle_text.push_back(tmp);
    }
    decoding(before_shuffle_text, pt, iv1);
}

void encode_decode_test() {
    char str[45];
    {
        std::string _str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRS";
        _str.copy(str, 54);
    }
    char chencoded[54], chdecoded[45];
    std::vector<char> vcdecoded, vcencoded;
    std::vector<std::vector<char>> todecode;
    std::vector<int> iv(45, 0);

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    key.push_back(op);

    encoding(str, chencoded, 0);
    for (int i = 0; i < 54; i++) {
        vcencoded.push_back(chencoded[i]);
    }
    todecode.push_back(vcencoded);

    decoding(todecode, vcdecoded, iv);
    for (int i = 0; i < 45; i++) {
        chdecoded[i] = vcencoded[i];
    }
    assertEqual(str, chdecoded);
}

void cubingmode_ende_test() {
    std::vector<char> str, ct, pt;
    std::string _str =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?"
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?"
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!?"
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!";
    std::copy(_str.begin(), _str.end(), std::back_inserter(str));

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    key.push_back(op);

    std::vector<int> iv1, iv2;

    cubingmode_en(key, str, ct, iv1, iv2);

    for (int i = 0; i < iv1.size(); i++) {
        if (iv1[i] < 10) {
            ct.push_back('0');
        } else {
            ct.push_back(iv1[i] / 10 + '0');
        }
        ct.push_back(iv1[i] % 10 + '0');
    }
    cubingmode_de(key, ct, pt);

    assertEqual(str, pt);
}

void usecubing_en() {
    char input_file_name[] = "./sampleIO/input.txt";
    char key_file_name[] = "./sampleIO/key.txt";
    char output_file_name[] = "./sampleIO/cipher.txt";
    std::vector<char> pt;
    {  // init output file
        FILE* fp;
        fp = fopen(output_file_name, "w");
        fclose(fp);
    }
    {  // plain input
        FILE* fp;
        fp = fopen(input_file_name, "r");

        char c;
        while ((c = fgetc(fp)) != EOF) {
            pt.push_back(c);
        }
        fclose(fp);
    }
    std::vector<CubeOP> key;
    {  // key input
        FILE* fp;
        fp = fopen(key_file_name, "r");

        char c;
        int num = 0;
        int tmpkey[3];
        while ((c = fgetc(fp)) != EOF) {
            tmpkey[num] = c - '0';
            num++;
            if (num % 3 == 0) {
                num = 0;
                CubeOP op = {tmpkey[0], tmpkey[1], tmpkey[2]};
                key.push_back(op);
            }
        }
        fclose(fp);
    }

    bool generatekey = 0;
    if (generatekey) {
        int keysize = 30;
        CubeOP op = {1, 2, 1};
        for (int i = 0; i < keysize; i++) {
            op.direction = 1 + rand() % 3;
            op.column = 1 + rand() % 3;
            op.times = 1 + rand() % 3;
            key.push_back(op);
        }
    }

    for (int i = 0; i < pt.size() / (62 * 62 * 45) + 1; i++) {
        std::vector<int> diviv1, diviv2;
        std::vector<char> divpt, divct;
        // 平文の分割処理
        for (int j = (62 * 62 * 45) * i;
             j < pt.size() && j < (62 * 62 * 45) * i + (62 * 62 * 45); j++) {
            divpt.push_back(pt[j]);
        }
        cubingmode_en(key, divpt, divct, diviv1, diviv2);

        {  // cipher & iv output
            FILE* fp;
            fp = fopen(output_file_name, "a");

            for (int i = 0; i < divct.size(); i++) {
                fprintf(fp, "%c", divct[i]);
            }
            for (int i = 0; i < diviv1.size(); i++) {
                fprintf(fp, "%02d", diviv1[i]);
            }
            fclose(fp);
        }
    }
    {  // key output
        FILE* fp;
        fp = fopen(key_file_name, "w");

        for (int i = 0; i < key.size(); i++) {
            fprintf(fp, "%d%d%d", key[i].direction, key[i].column,
                    key[i].times);
        }
        fclose(fp);
    }
}

void usecubing_de() {
    char input_file_name[] = "./io/cipher.txt";
    char key_file_name[] = "./io/key.txt";
    char output_file_name[] = "./io/plain.txt";
    std::vector<char> ct;
    {  // cipher input
        FILE* fp;
        fp = fopen(input_file_name, "r");

        char c;
        while ((c = fgetc(fp)) != EOF) {
            ct.push_back(c);
        }
        fclose(fp);
    }

    std::vector<CubeOP> key;
    CubeOP op = {1, 2, 1};
    {  // key input
        FILE* fp;
        fp = fopen(key_file_name, "r");

        char c;
        int oppos = 0;
        while ((c = fgetc(fp)) != EOF) {
            if (oppos % 3 == 0) {
                op.direction = c - '0';
            } else if (oppos % 3 == 1) {
                op.column = c - '0';
            } else {
                op.times = c - '0';
                key.push_back(op);
            }
            oppos = (oppos + 1) % 3;
        }
        fclose(fp);
    }
    std::vector<int> iv1, iv2;
    std::vector<char> pt;
    for (int i = 0; i < ct.size() / ((45 + 7 + 90 + 14 + 2) * 62 * 62) + 1;
         i++) {
        std::vector<int> diviv1, diviv2;
        std::vector<char> divpt;
        std::vector<char> divct;

        for (int j = (62 * 62 * (45 + 7 + 90 + 14 + 2)) * i;
             j < ct.size() && j < (62 * 62 * (45 + 7 + 90 + 14 + 2)) * i +
                                      (62 * 62 * (45 + 7 + 90 + 14 + 2));
             j++) {
            divct.push_back(ct[j]);
        }
        cubingmode_de(key, divct, divpt);
        // 結合処理
        for (int j = 0; j < divpt.size(); j++) {
            pt.push_back(divpt[j]);
        }
    }
    {  // plain output
        FILE* fp;
        fp = fopen(output_file_name, "w");

        for (int i = 0; i < pt.size(); i++) {
            fprintf(fp, "%c", pt[i]);
        }
        fclose(fp);
    }
}

int main() {
    unit_test();
    en_decode_test();
    encrypt_test();
    decrypt_test();
    encoding_test();
    encode_decode_test();
    cubingmode_ende_test();
}