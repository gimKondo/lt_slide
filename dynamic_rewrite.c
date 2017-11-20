typedef int CalcFunc(int);
int main() {
    unsigned char code[] = {
        0x8B, 0x44, 0x24, 0x04, 0x83, 0xC0/* add */, 0x09, 0xC3
    };
    CalcFunc* pFunc = (CalcFunc*)&code;
    int ret1 = pFunc(3);
    printf("n = %d\n", ret1);
    // コードを書き換える
    code[5] = 0xE8; // sub
    int ret2 = pFunc(3);
    printf("n = %d\n", ret2);
    return 0;
}
