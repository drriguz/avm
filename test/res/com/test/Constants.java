package com.test;

import java.util.function.Supplier;

public class Constants {
    private final String str = "我能吞下玻璃而不伤身体";
    private final float pi = 3.1415926f;
    
    // https://stackoverflow.com/questions/42265265/can-not-see-integer-value-in-constant-pool
    private final int k = 1024;
    private final long c = 299792458L;
    private final double pi1 = 3.1415926535898d;
    
    private final Supplier<String> builder = () -> "hello world!";
}