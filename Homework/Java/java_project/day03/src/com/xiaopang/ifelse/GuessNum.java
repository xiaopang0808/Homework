package com.xiaopang.ifelse;

import java.util.Random;
import java.util.Scanner;

public class GuessNum {
    /*方法一：Math.random()返回[0,1)之间的随机小数=>[0,99]=>[1,100]=>强转为int
    */
    public static final int rnum=(int)(Math.random()*100);
    /*方法二：创建随机数对象[0,99]=>[1,100]*/
//    public static final int rnum=new Random().nextInt(100)+1;
    public static void main(String[] args) {
        GessNum();
    }
    public static void GessNum() {
        int times=7;
        int min=0;
        int max=100;
        int num=0;
        System.out.println("猜数字小游戏");
        System.out.println("目标数字所在区间为["+min+","+max+"] 共有"+times+"次机会！");
        do{
            System.out.println("请输入猜测的数字：");
            Scanner sc = new Scanner(System.in);
            num=sc.nextInt();
            if(num==rnum){
                System.out.println("恭喜你猜对了！");
                break;
            }
            else if(num>rnum){
                System.out.println("你猜的数字太大了！");
                max=num;
            }
            else{
                System.out.println("你猜的数字太小了！");
                min=num;
            }
            System.out.println("目标数字所在区间为["+min+","+max+"] 共剩"+--times+"次机会！");
        }while (times>0);

    }
}
