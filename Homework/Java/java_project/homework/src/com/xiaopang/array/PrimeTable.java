package com.xiaopang.array;

import java.util.Scanner;

public class PrimeTable {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("请输入输出素数的范围：");
        int n = in.nextInt();
        int [] arr = new int[n];
        for(int x=2;x<n;x++){
            if(arr[x]!=1){
                for(int i=2;x*i<n;i++){
                    arr[x*i]=1;
                }
            }

        }
        for(int i=2;i<n;i++){
            if(arr[i]!=1){
                System.out.println(i);
            }
        }

    }
}
