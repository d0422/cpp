#include <iostream>
using namespace std;
class Shape{
    public:
        void type(){
            cout<<"ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ô´Ï´ï¿½."<<endl;
        }
        void myeon(){}
};
class Tri:public Shape{
    public:
        void type(){
            cout<<"µÊ"<<endl;
        }
        virtual void myeon(){
            cout<<"µÊ"<<endl;
        }
};
class Square:public Shape{
    public:
        void type(){
            cout<<"ï¿½ï¿½ï¿½ï¿½ ï¿½×¸ï¿½ï¿½ï¿½"<<endl;
        }
        virtual void myeon(){
            cout<<"ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½×°ï¿½ï¿½ï¿½"<<endl;
        }
};
int main(){
    Tri tri;
    tri.myeon();
    tri.type();
}