#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	
	int n, ans;
	cin >> n;
	while(n!=-1){
		int arr[n];
		int mean=0;
		for(int i=0;i<n;i++){
			cin >> arr[i];
			mean += arr[i];
		}
		if(mean-((mean/n)*n)!=0){
			cout << "-1\n";
		}
		else{
			mean/=n;
			ans=0;
			sort(arr,arr+n);
			for(int i=n-1;i>=0&&arr[i]>mean;i--){
				ans+=arr[i]-mean;
			}
			cout << ans << "\n";
		}
		cin >> n;
	}

	return 0;
}
