#include <iostream>
#include <cmath>
using namespace std;

int ftd(int n,int k){
    double power = double(k*log10(n));
    int ans = int(100.0 * pow(10,power-floor(power)));
    return ans;
}

int expmod(int x, int y, int n){
     if(y==0) return 1;
    int ans = (expmod(x,y/2,n))%n;
    if(y&1) return ((ans*ans*(x%n))%n);
    return ((ans*ans)%n);
}

int main(){
    int t,x,y;
    cin >> t;
    while(t--){
        cin >> x >> y;
        cout << ftd(x,y);
        cout << "..." << expmod(x,y,1000) <<"\n";
    }
	return 0;
}
