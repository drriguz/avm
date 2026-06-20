package com.op;

/**
 * Tests object-related instructions: new, invokespecial, invokevirtual,
 * getfield, putfield, instanceof, checkcast.
 */
public class ObjectOperations {
    public static native void println(int value);

    // new + invokespecial (constructor)
    public static int testNewAndInit() {
        Counter c = new Counter(42);
        return c.getValue();
    }

    // putfield + getfield
    public static int testFieldAccess() {
        Counter c = new Counter(10);
        c.setValue(20);
        return c.getValue();
    }

    // invokevirtual
    public static int testInvokeVirtual() {
        Counter c = new Counter(100);
        return c.incrementAndGet();
    }

    // Multiple objects
    public static int testMultipleObjects() {
        Counter a = new Counter(10);
        Counter b = new Counter(20);
        return a.getValue() + b.getValue();
    }

    // instanceof
    public static int testInstanceof(Object obj) {
        if (obj instanceof Counter) return 1;
        return 0;
    }

    // checkcast
    public static int testCheckcast(Object obj) {
        Counter c = (Counter)obj;
        return c.getValue();
    }

    // Passing object as argument
    public static int testPassObject(Counter c) {
        return c.getValue();
    }

    // Returning object
    public static Counter testReturnObject(int v) {
        return new Counter(v);
    }

    public static void main(String[] args) {
        println(testNewAndInit());
    }
}
