package com.test.complex;

import com.test.i.Imaginable;
import com.test.i.Store;

public class Db{
    protected int id;

    public Db(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }
}