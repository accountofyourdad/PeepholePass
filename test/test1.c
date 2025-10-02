int main() {
    int a = 10;
    int b = a + 0; // This line should be optimized
    int c = 0 + b; // This line should also be optimized
    return c;
}
