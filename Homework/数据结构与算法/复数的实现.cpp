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


//��ʼ��
Status InitComplex(Complex *&z){
	z=new(Complex);
	z->real=0;
	z->imag=0;
	return OK;
}

//��ֵ
Status AssignComplex(Complex &z,Elemtype a,Elemtype b){
	z.real=a;
	z.imag=b;
	return OK;
}

//ȡģ
double Complex_abs(Complex z){
	return (double)sqrt(z.real*z.real+z.imag*z.imag);
}

//����
Status DestroyComplex(Complex *&z){
	delete z;
	z=NULL;
	return OK;
}

//���
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

//�ӷ�
Complex Complex_add(Complex a, Complex b){
	Complex result;
	result.real=a.real+b.real;
	result.imag=a.imag+b.imag;
	return result;
}

//����,���𱻼��������
Complex Complex_sub(Complex a,Complex b){
	Complex result;
	result.real=a.real-b.real;
	result.imag=a.imag-b.imag;
	return result;
}

//�˷�
Complex Complex_mul(Complex a,Complex b){
	Complex result;
	result.real=a.real*b.real-a.imag*b.imag;
	result.imag=a.imag*b.real+a.real*b.imag;
	return result;
}

//����
Complex Complex_div(Complex a,Complex b){
	Complex result;
	double temp=b.real*b.real+b.imag*b.imag;
	result.real=(a.real*b.real+a.imag*b.real)/temp;
	result.imag=(a.imag*b.real-a.real*b.imag)/temp;
	return result;
}
int main(){
	//��ʼ��
	Complex *com1,*com2;
	InitComplex(com1);
	InitComplex(com2);
	Elemtype a,b,c,d;
	cout<<"�������һ������complex1��ʵ�����鲿��ʹ�ÿո������2 3��4 -5,֧�ָ���������ͬ����";
	cin>>a>>b;
	cout<<"������ڶ�������complex2��ʵ�����鲿��";
	cin>>c>>d;
	//��ֵ
	AssignComplex(*com1,a,b);
	AssignComplex(*com2,c,d);
	//���
	cout<<"complex1=";
	GetComplex(*com1);
	cout<<"complex2=";
	GetComplex(*com2);
	//ȡģ
	cout<<"|complex1|="<<Complex_abs(*com1)<<endl;
	cout<<"|complex2|="<<Complex_abs(*com2)<<endl;
	//�ӷ�
	cout<<"complex1+complex2=";
	GetComplex(Complex_add(*com1,*com2));
	//����
	cout <<"complex1-complex2=";
	GetComplex(Complex_sub(*com1,*com2));
	//�˷�
	cout <<"complex1*complex2=";
	GetComplex(Complex_mul(*com1,*com2));
	//����
    if (Complex_abs(*com2) == 0) {
        cout << "���󣺳�������Ϊ�㣡" << endl;
    } else {
		cout <<"complex1/complex2=";
        GetComplex(Complex_div(*com1, *com2));
    }
	//����
	DestroyComplex(com1);
	DestroyComplex(com2);
	return 0;
}
