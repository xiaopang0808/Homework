package com.xiaopang.object;

import java.util.Date;

public class Test {
    public static void main(String[] args){
        Student s1 = new Student(1001,"罗正阳","男",18,100);
        Student s2 = new Student(1002,"王伟","男",19,90);
        Student s3 = new Student(1003,"张丽","女",20,90);

        System.out.println("---------------------------------");
        s1.info();
        System.out.println("---------------------------------");
        s2.info();
        System.out.println("---------------------------------");
        s3.info();
        System.out.println("---------------------------------");
        int max=0;
        int min=100;
        int avg=0;
        if(s1.getJava()>max){
            max=s1.getJava();
        }
        if(s2.getJava()>max){
            max=s2.getJava();
        }
        if(s3.getJava()>max){
            max=s3.getJava();
        }
        if(s1.getJava()<min){
            min=s1.getJava();
        }
        if(s2.getJava()<min){
            min=s2.getJava();
        }
        if(s3.getJava()<min){
            min=s3.getJava();
        }
        avg=s1.getJava()+s2.getJava()+s3.getJava();
        System.out.println("最大成绩是："+max);
        System.out.println("最小成绩是："+min);
        System.out.println("平均成绩是："+avg/3);

        System.out.println("\n作者：罗正阳");
        Date date = new Date();
        System.out.println("时间："+date);
    }
}
