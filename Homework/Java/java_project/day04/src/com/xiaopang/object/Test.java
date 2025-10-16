package com.xiaopang.object;

public class Test {
    public static void main(String[] args) {
        Star s1 = new Star();
        s1.name = "小宝";
        s1.sex = "男";
        s1.age = 18;
        s1.height = 180;
        s1.weight = 80;
        s1.show();

        Star s2 = new Star("小机", "男", 22, 175, 60);
        s2.show();
    }
}
