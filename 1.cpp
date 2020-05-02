#include <iostream>
#include <vector>
using namespace std;

int dfsearch(int indx, int n, int arr[], vector<bool> &vis, int count){
    if(indx == n-1){
        vis[indx] = true;
        return count;
    }
    vis[indx] = true;
    if(arr[indx+1] - arr[indx] <= 2)
        return dfsearch(indx+1,n,arr,vis,count+1);
    else return count;
}

int main() {
    int t;cin>>t;
    for(int y=1;y<=t;y++){
        int n;cin>>n;
        int arr[n];
        int best = 9999,worst = 1;
        for(int i=0;i<n;i++) cin>>arr[i];
        vector<bool> vis(n,false);
        for(int i=0;i<n;i++){
            if(!vis[i]){
                int count = dfsearch(i,n,arr,vis,1);
                best = min(count,best);
                worst = max(count,worst);
            }
        }
        cout<<best<<" "<<worst<<"\n";
    }
    return 0;
}
