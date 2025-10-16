package com.xiaopang.thisdemo;

public class Student {
    String name;
    int age;
    int score;

    //this构造方法,返回当前对象的地址，常用于在构造方法时防止变量冲突
    public Student(String name, int age, int score) {
        this.name = name;
        this.age = age;
        this.score = score;
    }
}
