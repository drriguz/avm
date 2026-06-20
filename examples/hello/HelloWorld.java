public class HelloWorld {
    public static native void println(int value);

    public static int fibonacci(int n) {
        if (n <= 1) return n;
        int a = 0;
        int b = 1;
        for (int i = 2; i <= n; i++) {
            int temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    }

    public static void main(String[] args) {
        println(42);
        println(1 + 2 + 3);
        println(fibonacci(10));
    }
}
