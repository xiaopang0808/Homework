#include<iostream>
#include<cmath>
#define OK 1
using namespace std;
typedef double Elemtype;
typedef int Status;

typedef struct{
	Elemtype real;
	Elemtype imag;
}Complex;


//初始化
Status InitComplex(Complex *&z){
	z=new(Complex);
	z->real=0;
	z->imag=0;
	return OK;
}

//赋值
Status AssignComplex(Complex &z,Elemtype a,Elemtype b){
	z.real=a;
	z.imag=b;
	return OK;
}

//取模
double Complex_abs(Complex z){
	return (double)sqrt(z.real*z.real+z.imag*z.imag);
}

//销毁
Status DestroyComplex(Complex *&z){
	delete z;
	z=NULL;
	return OK;
}

//输出
Status GetComplex(Complex z){
	if(z.real)cout<<z.real;
	if(z.imag>0){
		if(z.real) cout<<'+';
		cout<<z.imag<<'i';
	}
	else if(z.imag<0){
		cout<<z.imag<<'i';
	}
	if(!z.real&&!z.imag) cout<<0;
	cout<<endl;
	return OK;
}

//加法
Complex Complex_add(Complex a, Complex b){
	Complex result;
	result.real=a.real+b.real;
	result.imag=a.imag+b.imag;
	return result;
}

//减法,区别被减数与减数
Complex Complex_sub(Complex a,Complex b){
	Complex result;
	result.real=a.real-b.real;
	result.imag=a.imag-b.imag;
	return result;
}

//乘法
Complex Complex_mul(Complex a,Complex b){
	Complex result;
	result.real=a.real*b.real-a.imag*b.imag;
	result.imag=a.imag*b.real+a.real*b.imag;
	return result;
}

//除法
Complex Complex_div(Complex a,Complex b){
	Complex result;
	double temp=b.real*b.real+b.imag*b.imag;
	result.real=(a.real*b.real+a.imag*b.real)/temp;
	result.imag=(a.imag*b.real-a.real*b.imag)/temp;
	return result;
}
int main(){
	//初始化
	Complex *com1,*com2;
	InitComplex(com1);
	InitComplex(com2);
	Elemtype a,b,c,d;
	cout<<"请输入第一个复数complex1的实部和虚部（使用空格隔开如2 3或4 -5,支持浮点数，下同）：";
	cin>>a>>b;
	cout<<"请输入第二个复数complex2的实部和虚部：";
	cin>>c>>d;
	//赋值
	AssignComplex(*com1,a,b);
	AssignComplex(*com2,c,d);
	//输出
	cout<<"complex1=";
	GetComplex(*com1);
	cout<<"complex2=";
	GetComplex(*com2);
	//取模
	cout<<"|complex1|="<<Complex_abs(*com1)<<endl;
	cout<<"|complex2|="<<Complex_abs(*com2)<<endl;
	//加法
	cout<<"complex1+complex2=";
	GetComplex(Complex_add(*com1,*com2));
	//减法
	cout <<"complex1-complex2=";
	GetComplex(Complex_sub(*com1,*com2));
	//乘法
	cout <<"complex1*complex2=";
	GetComplex(Complex_mul(*com1,*com2));
	//除法
    if (Complex_abs(*com2) == 0) {
        cout << "错误：除数不能为零！" << endl;
    } else {
		cout <<"complex1/complex2=";
        GetComplex(Complex_div(*com1, *com2));
    }
	//销毁
	DestroyComplex(com1);
	DestroyComplex(com2);
	return 0;
}
