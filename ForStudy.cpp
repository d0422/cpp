#include <iostream>
using namespace std;
class Shape{
    public:
        void type(){
            cout<<"���� �����Դϴ�."<<endl;
        }
        void myeon(){}
};
class Tri:public Shape{
    public:
        void type(){
            cout<<"��"<<endl;
        }
        virtual void myeon(){
            cout<<"��"<<endl;
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
    Tri tri;
    tri.myeon();
    tri.type();
}