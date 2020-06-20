#include<bits/stdc++.h>
using namespace std;
class PosNegDice {
  public:
  vector<int> evaluateRoll(int T, vector <int> pos, vector <int> neg) {
    vector<int> cnt_pos(6), cnt_neg(6);
    for(auto i:pos) cnt_pos[i-1]++;
    for(auto i:neg) cnt_neg[i-1]++;
    for(int i=0;i<6;i++) {
      int van=min(cnt_pos[i], cnt_neg[i]);
      cnt_pos[i]-=van;
      cnt_neg[i]-=van;
    } 
    vector<int> res={0,0};
    for(int i=0;i<=T;i++) if(cnt_pos[i]>0) res[0]=1;
    for(int i=0;i<6;i++) res[1]+=cnt_neg[i];   
    return res;
  }
};
