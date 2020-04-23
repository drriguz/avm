package com.op;

public class NativeCall {
    public static native void println(int value);
    public static int sum(int a, int b) {
        return a + b;
    }
    public static void main(String[] args) {
        int s = sum(1, 2);
        println(s);
    }
}