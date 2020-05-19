#include<bits/stdc++.h>
using namespace std;

void cyclic_shift(long int*, long int, long int, long int);

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);
    int t;cin>>t;
	for(int q=1;q<=t;q++)
	{
		long int n,k;
		cin>>n>>k;
		long int a[n],s[n];
		for(long int i=0;i<n;i++){
			cin>>a[i];
			s[i] = a[i];	
		}
		sort(s,s+n);
        unordered_map<long int,long int>indx;
		for(long int i=0; i<n;i++)indx[s[i]] = i;
        long int ans = 0;
		vector<pair<long int,pair<long int,long int>>> steps;
		long int prevf=-1,prevs=-1,i1,i2,i3;
		long int ii=0;
		while(ii<n){
			if(a[ii]==s[ii] || prevs==ii){
			    ii++;continue;
	    	}
			i1 = ii;
			i2 = indx[a[i1]];
			i3 = indx[a[i2]];
			if(i3==i1 && prevf==-1){
				prevf = i1;
				prevs = i2;
				ii++;
				continue;
			}
			else if(i3==i1){
				i1 = prevf;
				i2 = prevs;
				i3 = ii;
				prevf=-1;
				prevs=-1;
			}

			cyclic_shift(a,i1,i2,i3);
			ans++;
			steps.push_back({i1+1,{i2+1,i3+1}});
			if(a[i1]==s[i1])ii++;
            if(ans>k){ans = -1;break;}
		}

		if(prevf!=-1) ans = -1;
		
        if(ans<=k && ans!=-1){
			cout<<ans<<"\n";
			for(auto &x: steps)
				cout<<x.first<<" "<<x.second.first<<" "<<x.second.second<<"\n";
		}
		else cout<<"-1\n";
	}

	return 0;
}

void cyclic_shift(long int *a, long int i1, long int i2, long int i3)
{
	long int temp = a[i3];
	a[i3] = a[i2];
	a[i2] = a[i1];
	a[i1] = temp;
}
