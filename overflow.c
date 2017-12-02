void danger_func() { printf("danger!!!\n"); }
void sample_func(char* arg, int i) {
    int c[3] = {1,2,3};
    strcpy((char*)&c[i], arg);
    printf("end of func\n");
}
int main(int argc, char *argv[]) {
    // 便宜上、ハードコーディング(実際はユーザ入力等から入れる)
    char* p = (char*)danger_func;
    char c[] = {p[2], p[3], p[0], p[1], '\0'};
    sample_func(c, 4);
    return 0;
}
