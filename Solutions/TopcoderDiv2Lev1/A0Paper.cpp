#include <bits/stdc++.h>
using namespace std;

class A0Paper {
    public:
    string canBuild(vector<int> a) {
        for(int i=a.size()-1; i>0; i--) a[i-1]+=a[i]/2;
        return (a[0] ? "Possible" : "Impossible");
        }
    };
