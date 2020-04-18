package com.test.i;
public interface Circle {
    float pi = 3.14f;

    default float getArea() {
        return pi * getRadius() * getRadius();
    }

    float getRadius();
}