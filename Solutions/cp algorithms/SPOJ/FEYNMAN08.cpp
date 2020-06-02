#include <iostream>
using namespace std;

int main() {
	
	int n, ans;
	cin >> n;
	while(n!=0){
		ans = (n*(n+1)*(2*n+1))/6;
		cout << ans << "\n";
		cin >> n;
	}

	return 0;
}
