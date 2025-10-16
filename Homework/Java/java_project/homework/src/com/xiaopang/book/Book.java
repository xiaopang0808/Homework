package com.xiaopang.book;

public class Book {
    private String name;    // 书名
    private String[] author;    // 作者
    private String publisher;   // 出版社
    private int price;      // 价格
    private int pageNum;    // 页数
    private String[] pageContent; // 页面内容
    private int nowPage;    // 当前页

    /**
     * 默认构造函数
     */
    public Book(){
        this.pageContent = new String[100]; // 默认100页
    }

    /**
     * 带基本信息的构造函数
     * @param name 书名
     * @param publisher 出版社
     * @param author 作者数组
     */
    public Book(String name,String publisher,String[] author){
        this.name = name;
        this.publisher = publisher;
        this.author = author;
        this.pageContent = new String[100]; // 默认100页
    }

    /**
     * 包含所有信息的构造函数
     * @param name 书名
     * @param publisher 出版社
     * @param author 作者数组
     * @param price 价格
     * @param pageNum 页数
     */
    public Book(String name,String publisher,String[] author,int price,int pageNum){
        this.name = name;
        this.publisher = publisher;
        this.author = author;
        this.price = price;
        this.pageNum = pageNum;
        this.pageContent = new String[pageNum]; // 根据页数初始化
    }


    /**
     * 获取书名
     * @return 书名
     */
    public String getName() {
        return name;
    }

    /**
     * 设置书名
     * @param name 书名
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * 获取作者信息
     * @return 作者数组
     */
    public String[] getAuthor() {
        return author;
    }

    /**
     * 设置作者信息
     * @param author 作者数组
     */
    public void setAuthor(String[] author) {
        this.author = author;
    }

    /**
     * 获取出版社信息
     * @return 出版社
     */
    public String getPublisher() {
        return publisher;
    }

    /**
     * 设置出版社信息
     * @param publisher 出版社
     */
    public void setPublisher(String publisher) {
        this.publisher = publisher;
    }

    /**
     * 获取价格
     * @return 价格
     */
    public int getPrice() {
        return price;
    }

    /**
     * 设置价格
     * @param price 价格
     */
    public void setPrice(int price) {
        this.price = price;
    }

    /**
     * 获取总页数
     * @return 总页数
     */
    public int getPageNum() {
        return pageNum;
    }

    /**
     * 设置总页数
     * @param pageNum 总页数
     */
    public void setPageNum(int pageNum) {
        this.pageNum = pageNum;
        // 重新初始化 pageContent 数组以匹配新的页数
        if (this.pageContent == null) {
            this.pageContent = new String[pageNum];
        } else if (this.pageContent.length != pageNum) {
            // 创建新数组并保留原有内容
            String[] newPageContent = new String[pageNum];
            int copyLength = Math.min(this.pageContent.length, pageNum);
            System.arraycopy(this.pageContent, 0, newPageContent, 0, copyLength);
            this.pageContent = newPageContent;
        }
    }


    /**
     * 获取当前页面内容
     * @param page 目标页码
     * @return 页面内容
     */
    public String getPageContent(int page) {
        return pageContent[page-1];
    }

    /**
     * 设置当前页面内容
     * @param pageContent 页面内容
     */
    public void setPageContent(String pageContent) {
        this.pageContent[nowPage-1] = pageContent;
    }
    
    /**
     * 显示书籍主要信息（书名、作者、出版社）
     */
    public void mainInfo(){
        System.out.println("书名："+name);
        System.out.println("作者："+author[0]+"、"+author[1]);
        System.out.println("出版社："+publisher);
    }
    
    /**
     * 显示书籍详细信息（书名、作者、出版社、价格、页数）
     */
    public void show(){
        System.out.println("书名："+name);
        for(int i=0;i<author.length;i++){
            if(i==author.length-1){
                System.out.print(author[i]);
            }
            else {
                System.out.print(author[i]+"、");
            }
        }
        System.out.println("\n出版社："+publisher);
        System.out.println("价格："+price);
        System.out.println("页数："+pageNum);
    }
    
    /**
     * 翻页功能
     * @param page 目标页码
     */
    public void turnPage(int page){
        if(page>pageNum || page<1){
            System.out.println("没有此页");
        }else{
            nowPage = page;
        }
    }

    public void read(){
        System.out.println("正在阅读第"+nowPage+"页");
        System.out.println(pageContent[nowPage-1]);
    }
}
