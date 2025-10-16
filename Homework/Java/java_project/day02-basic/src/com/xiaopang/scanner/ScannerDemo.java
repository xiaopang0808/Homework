package com.xiaopang.scanner;
import java.util.Scanner;

public class ScannerDemo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("请输入用户名：");
        String username = sc.next();
        System.out.println("您的用户名为："+ username);

        System.out.println("请输入密码：");
        String password = sc.next();
        System.out.println("您的密码为："+ password);

        System.out.println("请输入年龄：");
        int age = sc.nextInt();
        System.out.println("您的年龄为："+ age);
    }
}
