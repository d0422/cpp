#include <iostream>
using namespace std;

class BaseClass{
    int value;
    public:
        BaseClass():value(0){
            cout<<1;
        }
        BaseClass(int value):value(value){
            cout<<2;
        }
        ~BaseClass(){
            cout<<3;
        }
        BaseClass& operator = (const BaseClass& base){
            this->value=base.value;
            cout<<4; 
            return *this;
        }
        void function(){
            cout<<5;
        }
};
class SubClass:BaseClass{
    int value;
public:
    SubClass():value(0){cout<<6;}
    SubClass(int value):value(value){
        cout<<7;
    }

    ~SubClass(){cout<<8;}
    SubClass & operator =(const SubClass&sub){
        this->value=sub.value;
        cout<<9;
        return *this;
    }
    void function(){cout<<0;}
};
int main(){
    BaseClass instance;
    instance=1;
    instance.function();
}