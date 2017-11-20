void danger_func() { printf("danger!!!\n"); }
void sample_func(char* arg, int i) {
    char c[5] = {1,2,3,4,5};
    strcpy(&c[i], arg);
    printf("end of func\n");
}
int main(int argc, char *argv[]) {
    // 便宜上、ハードコーディング(実際はユーザ入力等から入れる)
    char* p = (char*)danger_func;
    char c[] = {p[2], p[3], p[0], p[1], '\0'};
    sample_func(c, 20);
    return 0;
}
