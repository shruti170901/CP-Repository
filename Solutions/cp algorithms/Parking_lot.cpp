#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n; cin >> n;
    unsigned long long ans = (6*(pow(4,n-3) * 4) + (n-3)*9*pow(4,n-3));
    cout << ans;
    return 0;
}

//6*(4^{n-3} * 4) + (n-3)*9*4^{n-3}
