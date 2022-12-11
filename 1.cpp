#include <iostream>
using namespace std;
class MyClass{
    private:
        void private_function();
    protected:
        void protected_function();
    public:
        void public_function();
};
class PrivateClass:private MyClass{
    PrivateClass(){
        public_function();
    }
    private:
        void private_function();
    protected:
        void protected_function();
    public:
        void public_function();
};
class PublicClass:public MyClass{
    private:
        void private_function();
    protected:
        void protected_function();
    public:
        void public_function();
};
int main(){
    MyClass myclass;
    PrivateClass pclass;
    myclass.public_function();
    pclass.public_function();

}