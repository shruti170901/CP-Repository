#include <bits/stdc++.h>
using namespace std;
class EllysPalMulDiv2 {
 public:
  int getMin(int X) {
    string s, r;
    int Y = 1, Z;
    for (; Y <= 1000; Y++) {
      Z = X * Y;
      s = to_string(Z);
      r = s;
      reverse(r.begin(), r.end());
      if(r == s) return Y;
    }
    return -1;
  }
};
