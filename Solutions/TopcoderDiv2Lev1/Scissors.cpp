#include <bits/stdc++.h>
using namespace std;
class Scissors {
     public:
        int openingTime(int N) {
            int ans = 0;
            while (N > 0) {
                N /= 2;
                ans++;
            }
            ans *= 10;
            return ans;
        }
};
