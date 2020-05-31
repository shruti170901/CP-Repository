#include <iostream>
using namespace std;

int expmod(int a, int b, int c){
    if(b==0) return 1;
    if(b%2==0){
        int x=expmod(a,b/2,c);
        return (x*x)%c;
    }
    return (a%c * expmod(a,b-1,c))%c;
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int B,P,M;
    while(cin>>B>>P>>M)
        cout<<expmod(B,P,M)<<"\n";
	return 0;
}
