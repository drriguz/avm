package com.op;

public class Counter {
    int value;

    public Counter(int v) {
        this.value = v;
    }

    public int getValue() {
        return this.value;
    }

    public void setValue(int v) {
        this.value = v;
    }

    public int incrementAndGet() {
        this.value++;
        return this.value;
    }
}
