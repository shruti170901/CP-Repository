/*2
2 3 5
2 2147483647 13
0*/

#include <iostream>
using namespace std;

int binexp(int x, long int y, int n){
    if(y==0) return 1;
    int ans = (binexp(x,y/2,n))%n;
    if(y&1) return ((ans*ans*x)%n);
    return ((ans*ans)%n);
}

int main(){
    int t, x, n;
    long int y;
    cin >> t;
    while(t--){
        cin >> x >> y >> n;
        cout << binexp(x,y,n) << "\n";
    }
    return 0;
}
