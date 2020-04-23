package com.test.resolve;

public class Animal {
    protected int age;
    protected boolean gender;

    public Animal() {
    }

    public Animal(int age, boolean gender) {
        this.age = age;
        this.gender = gender;
    }

    public boolean isOld() {
        return age > 10;
    }
}