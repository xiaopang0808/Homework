package com.xiaopang.book;

import java.util.Date;

public class Test {
    public static void main(String[] args) {
        Book book1 = new Book("《Java从入门到精通》","广东技术师范大学出版社",new String[]{"小立","小航"});
        book1.setPrice(100);
        book1.setPageNum(200);

        Book book2 = new Book("《C++从入门到精通》","广东技术师范大学出版社",new String[]{"小张","小航"},100,100);
        book2.setPrice(88);
        book2.setPageNum(234);

        Book book3 = new Book("《Python从入门到精通》","广东技术师范大学出版社",new String[]{"小王","小航"},100,100);
        book3.setPrice(66);
        book3.setPageNum(112);

        System.out.println("--------------------------------");
        book1.show();
        System.out.println("--------------------------------");
        book2.show();
        System.out.println("--------------------------------");
        book3.show();
        System.out.println("--------------------------------");

        int totalPrice = book1.getPrice()+book2.getPrice()+book3.getPrice();
        System.out.println("总价格："+totalPrice);
        System.out.println("--------------------------------");
        book1.turnPage(1);
        book1.setPageContent("一定要自己动手写代码和调试！");
        book1.read();

        System.out.println("--------------------------------");
        System.out.println("\n作者：罗正阳");
        Date date = new Date();
        System.out.println("时间："+date);
    }

}
