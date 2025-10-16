package com.xiaopang.array;

public class ArrayDemo  {

    public static void main(String[] args) {
        int [] arr = GetArray(20,-100,100);
        PrintArray(arr);
        int [] arr_sort = BubbleSort(arr);
        PrintArray(arr_sort);
        System.out.println("作者：罗正阳 日期：2025.9.15");
        System.out.println("排序算法：冒泡排序");
    }
    /*
    * 获取len长度的数组，数组元素范围是[min,max]
    * */
    public static int[] GetArray(int len,int min,int max){
        int[] arr = new int[len];
        for(int i=0;i<len;i++){
            arr[i] = (int)(Math.random()*(max-min+1)+min);
        }
        return arr;
    }

    public static void PrintArray(int[] arr){
        for (int j : arr) {         //增强型for循环
            System.out.print(j + " ");
        }
        System.out.println();
    }

    public static int [] BubbleSort(int[] arr){
        for(int i=0;i<arr.length-1;i++){
            for(int j=0;j<arr.length-1-i;j++){
                if(arr[j]>arr[j+1]){
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
        return arr;
    }
}
