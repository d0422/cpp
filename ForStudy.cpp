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
            cout<<"나는 도형입니다."<<endl;
        }
        virtual void myeon()=0;
};
class Tri:public Shape{
    public:
        void type(){
            cout<<"나는 세모입니다."<<endl;
        }
        virtual void myeon(){
            cout<<"나는 면이 세개임"<<endl;
        }
};
class Square:public Shape{
    public:
        void type(){
            cout<<"나는 네모임"<<endl;
        }
        virtual void myeon(){
            cout<<"나는 면이 네개임"<<endl;
        }
};

int main(){
    // Base b;
    // Sub1 s;
    // Base *pb;
    // Sub1 *ps;
    // pb=&b; //Base를 pb에 할당함
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
    cout << "면이 몇개죠?" <<endl;
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