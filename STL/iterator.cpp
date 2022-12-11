#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;
int main(){
    vector<int> integer_vector;
    integer_vector.push_back(1);
    integer_vector.push_back(2);
    integer_vector.push_back(3);
    vector<int>::iterator iter=integer_vector.begin();
    for(; iter!=integer_vector.end(); iter++){
        cout << *iter<<endl;
    }
    return 0;
}