package com.xiaopang.object;

public class Student {
    private int sNO;
    private String SName;
    private String sSex;
    private int sAge;
    private int sJava;

    //无参构造器
    public Student(){

    }
    //有参构造器
    public Student(int sNO,String SName,String sSex,int sAge,int sJava){
        this.sNO = sNO;
        this.SName = SName;
        this.sSex = sSex;
        this.sAge = sAge;
        this.sJava = sJava;
        System.out.println("学生对象创建成功！");
    }
    public int getNO(){
        return sNO;
    }
    public String getName(){
        return SName;
    }
    public String getSex(){
        return sSex;
    }
    public int getAge(){
        return sAge;
    }
    public int getJava(){
        return sJava;
    }
    public void info(){
        System.out.println("学号：" + sNO);
        System.out.println("姓名：" + SName);
        System.out.println("性别：" + sSex);
        System.out.println("年龄：" + sAge);
        System.out.println("Java成绩：" + sJava);
    }
}
