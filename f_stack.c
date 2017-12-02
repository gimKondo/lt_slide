void func1(int n) {
    int a[3] = {0, 1, 2};
    if (n <= 0) {
        func1(n - 1);
    } else {
        func2();
    }
}
void func2() {
    // do something
}
void main(int argc, char* argv[]) {
    int x = 2;
    func1(x);
}
