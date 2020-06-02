#include <iostream>
#include <fstream>
using namespace std;

long int gcd(long int a, long int b, long int *x, long int *y){
    long int d, x1, y1;
    if(b==0){
        *x = 1;
        *y = 0;
        return a;
    }
    d = gcd(b, a%b, *x1, *y1);
    *x = y1;
    *y = x1 - y1*(a/b);
    return d;
}

int main(){
    //driver
    return 0;
}
