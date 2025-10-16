package com.xiaopang.javabean;
//实体类
public class Student {
    //私有成员变量
    private String name;
    private int age;
    private int score;
    //提供无参构造方法
    public Student()
    {
        System.out.println("无参构造方法");
    }
    //提供public修饰的getter和setter方法
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }
}
