#include <iostream>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--){
		int a,b,ans=-1;
		cin >> a >> b;
		if(a==b){
			if(a%2==0)ans=2*a;
			else ans=(a-1)*2+1;
		}
		else if(a==b+2){
			if(a%2==0)ans=(a-2)*2+2;
			else ans=(a-3)*2+3;
		}
		else{
			cout << "No Number\n";
			continue;
		}
		cout << ans << "\n";
	}
	return 0;
}
