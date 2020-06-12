#include <iostream>

#include "./cubing.cpp"

void print_file(char inputFileName[]) {
    FILE *fp;
    fp = fopen(inputFileName, "r");
    printf("%s : ", inputFileName + 5);

    char c;
    int num = 0;
    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
        if (++num >= 10) {
            break;
        }
    }
    printf("\n");
    fclose(fp);
}

int main(int ac, char **av) {
    srand((unsigned)time(NULL));

    printf("\n----unit_test----\n");
    unit_test();

    printf("\n----en_decode_test(Cube)----\n");
    en_decode_test();

    printf("\n----encrypt_test----\n");
    encrypt_test();

    printf("\n----decrypt_test----\n");
    decrypt_test();

    printf("\n----encoding_test----\n");
    encoding_test();

    printf("\n----cubingmode_ende_test----\n");
    cubingmode_ende_test();

    printf("\n----encode_decode_test(cubingmode)----\n");
    encode_decode_test();

    usecubing_en();

    usecubing_de();

    char input[] = "./io/input.txt";
    print_file(input);

    char cipher[] = "./io/cipher.txt";
    print_file(cipher);

    char plain[] = "./io/plain.txt";
    print_file(plain);

    char key[] = "./io/key.txt";
    print_file(key);

    return 0;
}
