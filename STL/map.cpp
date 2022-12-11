#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
using namespace std;
int main(){
    map<int,int> integer_map;
    integer_map.insert({1,30});
    integer_map.insert({2,100});
    map<int,int>::iterator i=integer_map.begin();
    for(; i!=integer_map.end(); i++){
        cout<< i->first << ": "
        << i->second <<endl;
    }
    return 0;
}