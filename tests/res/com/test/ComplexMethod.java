package com.test;

import java.io.IOException;

public class ComplexMethod {
    public static class CustomException extends Exception {

    }
    public int sum(int a, int b) throws IOException, CustomException {
        return a + b;
    }
}