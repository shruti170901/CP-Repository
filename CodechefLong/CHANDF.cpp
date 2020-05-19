#include<bits/stdc++.h>
using namespace std;

int cmp(double a, double b){
        if(a==b)return 0;
        return ((a > b)?1:-1);
}

double mult(long long int a, long long int b) { 
    return ((double(a)/100000000LL)*(double(b)/100000000LL));
}

int main(){
    int t;
    cin>>t;
    for(int q=1;q<=t;q++){
        long long int x, y, l, r,temp = 1, z = 0,z0;
        cin>>x>>y>>l>>r;
        //vector<long long int> m(3);
        double m0=0;
        while(temp <= r){
            while(temp & r)temp=temp<<1;
            while(temp <= r && ((temp&r)==0))temp=temp<<1;
            long long int sp = ((temp-1)|(((-1^(temp-1))<<1)&r) );
            z0 = (sp & (x|y));
            double mul = mult((sp&x), (sp&y));
            int val = cmp(mul, m0);
            if( val==0 && z > z0 ) z = z0;
            if( val==1 ){
                m0 = mult((sp&x),(sp&y));
                z = z0;
            }
            temp = temp<<1;
        }
        double mul = mult((r&x), (r&y));
        int val = cmp(mult((r&x), (r&y)), m0);
        if(val==1)z = (r&(x|y));
        cout<<z<<endl;
    }
    return 0;
}
