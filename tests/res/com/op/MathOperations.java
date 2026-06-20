package com.op;

/**
 * Tests math instructions: isub, imul, idiv, irem, ineg, iinc,
 * bitwise ops (ishl, ishr, iushr, iand, ior, ixor),
 * and type conversions (i2l, i2f, i2d, l2i, f2i, d2i).
 */
public class MathOperations {
    public static native void println(int value);

    // isub
    public static int testIsub(int a, int b) {
        return a - b;
    }

    // imul
    public static int testImul(int a, int b) {
        return a * b;
    }

    // idiv
    public static int testIdiv(int a, int b) {
        return a / b;
    }

    // irem
    public static int testIrem(int a, int b) {
        return a % b;
    }

    // ineg
    public static int testIneg(int a) {
        return -a;
    }

    // iinc
    public static int testIinc(int a) {
        a++;
        return a;
    }

    // iand
    public static int testIand(int a, int b) {
        return a & b;
    }

    // ior
    public static int testIor(int a, int b) {
        return a | b;
    }

    // ixor
    public static int testIxor(int a, int b) {
        return a ^ b;
    }

    // ishl
    public static int testIshl(int a, int b) {
        return a << b;
    }

    // ishr
    public static int testIshr(int a, int b) {
        return a >> b;
    }

    // iushr
    public static int testIushr(int a, int b) {
        return a >>> b;
    }

    // i2l (returns int after conversion)
    public static int testI2l(int a) {
        long l = (long)a;
        return (int)l;
    }

    // l2i (takes long via computation, returns int)
    public static int testL2i() {
        long a = 100000L;
        return (int)a;
    }

    public static void main(String[] args) {
        println(testIsub(10, 3));
        println(testImul(6, 7));
        println(testIdiv(20, 4));
        println(testIrem(17, 5));
        println(testIneg(42));
        println(testIinc(99));
        println(testIand(0xFF, 0x0F));
        println(testIor(0xF0, 0x0F));
        println(testIxor(0xFF, 0x0F));
        println(testIshl(1, 4));
        println(testIshr(32, 3));
        println(testIushr(-1, 28));
    }
}
