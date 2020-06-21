#include <bits/stdc++.h>
using namespace std;
class GoblinRabblemaster{
    public:
    long totalDamage(int t){
        long ans=0;
        for(int i=1;i<=t;i++){
            ans+=long((i*i+1)/2 + (i-1)*(i+((i*i+1)/2)));
        }
        return ans;
    }
};
