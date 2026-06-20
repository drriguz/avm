package com.op;

/**
 * Tests constant push instructions: bipush, sipush, ldc, ldc_w, ldc2_w
 * and iconst_m1, lconst, fconst, dconst.
 */
public class ConstantOperations {
    public static native void println(int value);

    // iconst_m1 (-1)
    public static int testIconstM1() {
        return -1;
    }

    // bipush (100)
    public static int testBipush() {
        return 100;
    }

    // sipush (300)
    public static int testSipush() {
        return 300;
    }

    // ldc int (40000, > 32767 so it uses ldc not sipush)
    public static int testLdcInt() {
        return 40000;
    }

    // ldc float (3.14f) - just store it, don't return
    public static int testLdcFloat() {
        float f = 3.14f;
        if (f > 3.0f) return 1;
        return 0;
    }

    // ldc2_w long (100000L) - compare and return int
    public static int testLdcLong() {
        long l = 100000L;
        if (l > 99999L) return 1;
        return 0;
    }

    // ldc2_w double (2.718) - compare and return int
    public static int testLdcDouble() {
        double d = 2.718;
        if (d > 2.0) return 1;
        return 0;
    }

    // lconst_0, lconst_1
    public static int testLconst() {
        long a = 0L;
        long b = 1L;
        if (a + b == 1L) return 1;
        return 0;
    }

    // fconst_0, fconst_1, fconst_2
    public static int testFconst() {
        float a = 0.0f;
        float b = 1.0f;
        float c = 2.0f;
        if (a + b + c > 2.9f) return 1;
        return 0;
    }

    // dconst_0, dconst_1
    public static int testDconst() {
        double a = 0.0;
        double b = 1.0;
        if (a + b == 1.0) return 1;
        return 0;
    }

    public static void main(String[] args) {
        println(testIconstM1());
        println(testBipush());
        println(testSipush());
        println(testLdcInt());
    }
}
