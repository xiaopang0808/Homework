package com.xiaopang.ifelse;

public class GetCode {
    public static void main(String[] args) {
        System.out.println(getCode(10));
    }
    public static String getCode(int num) {
        String code = "";
        for(int i=0;i<num;i++){
            int type = (int)(Math.random()*3);
            switch (type){
                case 0:
                    code += (char)(Math.random()*26+'a');
                    break;
                case 1:
                    code += (char)(Math.random()*26+'A');
                    break;
                case 2:
                    code += (int)(Math.random()*10);
                    break;


            }
        }
        return code;
    }
}
