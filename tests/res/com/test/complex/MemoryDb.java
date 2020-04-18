package com.test.complex;

import com.test.i.Imaginable;
import com.test.i.Store;

public class MemoryDb extends Db implements Imaginable, Store {
    private int value;
    public MemoryDb(int id) {
        super(id);
    }

    public void put(int value) {
        this.value = value;
    }
    public int get() {
        return this.value;
    }
}