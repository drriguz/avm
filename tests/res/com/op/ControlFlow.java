package com.op;

/**
 * Tests comparison and control flow instructions:
 * ifeq, ifne, iflt, ifge, ifgt, ifle,
 * if_icmpeq, if_icmpne, if_icmplt, if_icmpge, if_icmpgt, if_icmple,
 * goto, ifnull, ifnonnull, lcmp.
 */
public class ControlFlow {
    public static native void println(int value);

    // ifeq / ifne
    public static int testIfEq(int a) {
        if (a == 0) return 1;
        return 0;
    }
    public static int testIfNe(int a) {
        if (a != 0) return 1;
        return 0;
    }

    // iflt / ifge
    public static int testIfLt(int a) {
        if (a < 0) return 1;
        return 0;
    }
    public static int testIfGe(int a) {
        if (a >= 0) return 1;
        return 0;
    }

    // ifgt / ifle
    public static int testIfGt(int a) {
        if (a > 0) return 1;
        return 0;
    }
    public static int testIfLe(int a) {
        if (a <= 0) return 1;
        return 0;
    }

    // if_icmpeq
    public static int testIfIcmpEq(int a, int b) {
        if (a == b) return 1;
        return 0;
    }

    // if_icmpne
    public static int testIfIcmpNe(int a, int b) {
        if (a != b) return 1;
        return 0;
    }

    // if_icmplt
    public static int testIfIcmpLt(int a, int b) {
        if (a < b) return 1;
        return 0;
    }

    // if_icmpge
    public static int testIfIcmpGe(int a, int b) {
        if (a >= b) return 1;
        return 0;
    }

    // if_icmpgt
    public static int testIfIcmpGt(int a, int b) {
        if (a > b) return 1;
        return 0;
    }

    // if_icmple
    public static int testIfIcmpLe(int a, int b) {
        if (a <= b) return 1;
        return 0;
    }

    // goto (loop)
    public static int testGoto(int n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += i;
        }
        return sum;
    }

    // ifnull
    public static int testIfNull(Object obj) {
        if (obj == null) return 1;
        return 0;
    }

    // ifnonnull
    public static int testIfNonNull(Object obj) {
        if (obj != null) return 1;
        return 0;
    }

    // Nested if (tests multiple branches)
    public static int testNestedIf(int a, int b) {
        if (a > 0) {
            if (b > 0) return 2;
            return 1;
        }
        return 0;
    }

    public static void main(String[] args) {
        println(testIfEq(0));
        println(testIfEq(1));
        println(testIfNe(0));
        println(testIfNe(5));
        println(testIfLt(-1));
        println(testIfLt(1));
        println(testIfGe(0));
        println(testIfGe(-1));
        println(testIfGt(1));
        println(testIfGt(0));
        println(testIfLe(0));
        println(testIfLe(1));
        println(testIfIcmpEq(3, 3));
        println(testIfIcmpEq(3, 4));
        println(testIfIcmpNe(3, 4));
        println(testIfIcmpNe(3, 3));
        println(testIfIcmpLt(1, 2));
        println(testIfIcmpLt(2, 1));
        println(testIfIcmpGe(2, 2));
        println(testIfIcmpGe(1, 2));
        println(testIfIcmpGt(2, 1));
        println(testIfIcmpGt(1, 2));
        println(testIfIcmpLe(1, 1));
        println(testIfIcmpLe(2, 1));
        println(testGoto(10));
        println(testIfNull(null));
        println(testIfNonNull(new Object()));
        println(testNestedIf(1, 1));
        println(testNestedIf(1, -1));
        println(testNestedIf(-1, 1));
    }
}
