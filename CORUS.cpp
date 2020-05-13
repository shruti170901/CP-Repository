#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	int t;cin>>t;
	for(int y=1;y<=t;y++){
	    int n,q;
        cin>>n>>q;
        string s;
        cin>>s;
        int arr[26] = {0};
        for(int i=0;i<n;i++){
            arr[s[i] - 'a']++;
        }
        int c;
        for(int i=0;i<q;i++){
            cin>>c;
            int count = 0;
            for(int j=0;j<26;j++){
                if(arr[j] > c)
                    count = count + (arr[j] - c);
            }
            cout<<count<<"\n";
        }
	}
	return 0;
} 
