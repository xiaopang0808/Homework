package com.xiaopang.array;

import java.util.Date;

public class BirdDistribution {
    public static void main(String[] args) {
        int [][] Distribution = new int[10][10];
        int max = 0;
        int mx = 0;
        int my = 0;
        int sum = 0;
        System.out.println("鸟儿分布情况(10X10)：");
        for(int i=0;i<Distribution.length;i++){
            for(int j=0;j<Distribution[i].length;j++){
                Distribution[i][j] = (int)(Math.random()*50);
                sum += Distribution[i][j];
                if(Distribution[i][j]>max){
                    max = Distribution[i][j];
                    mx = i;
                    my = j;
                }
                System.out.printf("%4d",Distribution[i][j]);
            }
            System.out.println();
        }
        System.out.printf("鸟儿数量最多的网格坐标：(%d,%d)\n",mx,my);
        System.out.printf("鸟儿总数:%d\n",sum);
        System.out.println("\n作者：罗正阳");
        Date date = new Date();
        System.out.println("时间："+date);
    }
}
