#include <iostream>
using namespace std;

class Base{
    public:
        void f1(){
            cout<<"Basef1"<<endl;
        }
        virtual void v1(){
            cout << "Basev1" <<endl;
        }
};
class Sub1: public Base{
    public:
        void f1(){
            cout<<"Sub1"<<endl;
        }
        virtual void v1(){
            cout << "Sub1v1"<<endl;
        }
};

class Shape{
    public:
        void type(){
            cout<<"���� �����Դϴ�."<<endl;
        }
        virtual void myeon()=0;
};
class Tri:public Shape{
    public:
        void type(){
            cout<<"���� �����Դϴ�."<<endl;
        }
        virtual void myeon(){
            cout<<"���� ���� ������"<<endl;
        }
};
class Square:public Shape{
    public:
        void type(){
            cout<<"���� �׸���"<<endl;
        }
        virtual void myeon(){
            cout<<"���� ���� �װ���"<<endl;
        }
};

int main(){
    // Base b;
    // Sub1 s;
    // Base *pb;
    // Sub1 *ps;
    // pb=&b; //Base�� pb�� �Ҵ���
    // pb->v1(); //Basev1
    // pb->f1(); //Basef1
    // pb=&s;
    // ps=&s;
    // cout << "Sub1"<<endl;
    // pb->v1(); //Subv1
    // pb->f1(); //Sub1 -> Basef1
    // ps->v1();
    // ps->f1();
    int i;
    Shape *ps;
    cout << "���� ���?" <<endl;
    cin >> i;
    if (i==3){
        ps=new Tri();
    }
    else{
        ps=new Square();
    }
    ps->type();
    ps->myeon();

}