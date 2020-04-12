package com.vm;

public class App {
    private static final int majorVersion = 51;
    private static final int minorVersion = 1;

    private static final int version;
    static {
        version = majorVersion * 100 + minorVersion;
    }

    public static void main(String[] args) {
        int appVersion = App.version;
        System.out.println(appVersion);
    }
}