import java.io.Serializable;

public class Complex implements Serializable {
    private static final long serialVersionUID = 1024L;
    private static final String message = "你好!";
    private static final int age = 99;
    private static final long length = 28229;
    private static final double balance = 11.5d;
    private static final float rate = 1.1f;

    public String sayHi(){
        return message;
    }
}

