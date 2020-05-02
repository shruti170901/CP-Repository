#include <iostream>
#include <vector>
using namespace std;

int dfs(int arr[], int idx, int n, vector<bool> &vis, int count)
{
    if(idx == n-1)
    {
        vis[idx] = true;
        return count;
    }
    vis[idx] = true;
    if(arr[idx+1] - arr[idx] <= 2)
        return dfs(arr,idx+1,n,vis,count+1);
    else
        return count;
}

int main() 
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int arr[n];
        int prev,minsize = 8,maxsize = 1,size=1;
        for(int i=0;i<n;i++)
            cin>>arr[i];
        vector<bool> vis(n,false);
        for(int i=0;i<n;i++)
        {
            if(!vis[i])
            {
                int size = dfs(arr,i,n,vis,1);
                minsize = min(size,minsize);
                maxsize = max(size,maxsize);
            }
        }
        
        cout<<minsize<<" "<<maxsize<<endl;
    }
	return 0;
}
