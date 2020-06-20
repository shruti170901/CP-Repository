#include <bits/stdc++.h>
using namespace std;
 
class CutTheCube {
    public: 
    	int findWinner(int L, int B, int H) {
        int v = ((L%10 * B%10 * H%10) - 1)%2;
        return v?2:1;
    }
};
