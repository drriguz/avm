package com.test.resolve;

public class Dog extends Animal implements Friend{
    protected int weight;

    public Dog() {
    }

    public Dog(int weight) {
        this.weight = weight;
    }

    public int getWeight() {
        return weight;
    }

    @Override
    public int years() {
        return 2000;
    }

    public void update(int age, boolean gender) {
        this.age = age;
        this.gender = gender;
    }
}