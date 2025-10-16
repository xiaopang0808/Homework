package com.xiaopang.object;
//明星类：明星对象的模板
public class Star {
    String name;
    String sex;
    int age;
    int height;
    int weight;

    //无参构造器，名称必须是类名，类默认自动生成一个无参构造器
    public Star()
    {
    	System.out.println("无参构造器调用，对象创建成功！");
    }

    //有参构造器，构造器可重复定义，可改变参数个数，可改变参数顺序实现重构
    //定义了有参构造器，则无参构造器将不再自动生成，需要手动定义
    public Star(String name, String sex, int age, int height, int weight)
    {
    	this.name = name;
    	this.sex = sex;
    	this.age = age;
    	this.height = height;
    	this.weight = weight;
        System.out.println("有参构造器调用，对象创建成功！");
    }

    public void show()
    {
    	System.out.println("姓名：" + name);
    	System.out.println("性别：" + sex);
    	System.out.println("年龄：" + age);
    	System.out.println("身高：" + height);
    	System.out.println("体重：" + weight);
    }
}
