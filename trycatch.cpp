#include <stdio.h>
#include <exception>
#include <iostream>
using namespace std;

int main(){
    try{
        cout<< "try" <<endl;
       throw string("error");
    }
    catch(const exception& exception_obejct){
        cout<<exception_obejct.what()<<endl;
    }
    catch(int number){
        cout<<number<<endl;
    }
    catch(string str){
        cout<<str<<endl;
    }
    catch(...){
        cout<<"catch all"<<endl;
    }
    getchar();
    return 0;
}