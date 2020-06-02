#include <iostream>
using namespace std;

int main() {
	
	float a, b, c, ans;
	cin >> a >> b >> c;
	while(!(a==0&&b==0&&c==0)){
		if(b-a==c-b){
		    ans=c + (b-a);
		    cout << "AP " << ans << "\n";
		}
		else {
		    ans=c * (b/a);
		    cout << "GP " << ans << "\n";
		}
		cin >> a >> b >> c;
	}

	return 0;
}
