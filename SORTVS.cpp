#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int T;cin>>T;
    for(int q=1;q<=T;q++)
    {
        int NN, MM;
        cin>>NN>>MM;
        int arr[NN];
        bool graph[NN][NN];
        for(int i = 0; i < NN; i++)
            for(int j = 0; j < NN; j++)
                graph[i][j] = false;
        for(int n = 0; n < NN; n++){
            cin>>arr[n];
            arr[n]--;
        }
        for(int m = 0; m < MM; m++){   
            int x, y;
            cin>>x>>y;
            graph[x-1][y-1] = graph[y-1][x-1] = true;
        }
        int id = 0;
        int group[NN] = {0};
        bool visited[NN];
        memset(visited, false, sizeof(visited));
        for(int n = 0; n < NN; n++){
            if(!visited[n]){
                id++;
                queue<int> q;
                q.push(n);
                visited[n] = true;
                group[n] = id-1;
                while(!q.empty()){
                    int u = q.front();
                    q.pop();
                    for(int v = 0; v < NN; v++){
                        if(!visited[v] && graph[u][v]){
                            visited[v] = true;
                            group[v] = id-1;
                            q.push(v);
                        }
                    }
                }
            }
        }
        int cross[id][id];
        for(int i = 0; i < id; i++)
            for(int j = 0; j < id; j++)
                cross[i][j] = 0;
        for(int n = 0; n < NN; n++)
            cross[group[n]][group[arr[n]]]++;
        for(int n = 0; n < id; n++)
            cross[n][n]=0;
        int num = 0;
        for(int k = 0; k < NN; k++){
            for(int i = 0; i < id; i++){
                for(int j = 0; j < id; j++){
                    if(cross[i][j] > 0 && i!=j){
                        bool visit[id];
                        memset(visit, false, sizeof(visit));
                        vector<int> st;
                        st.push_back(i);
                        visit[i] = true;
                        bool flag = false;
                        int el;
                        while(!st.empty()){
                            flag = true;
                            int u = st.back();
                            for(int vv = st.size()-1; vv >= 0; vv--){
                                if(cross[u][st[vv]] > 0){
                                    flag = false;
                                    el = st[vv];
                                    break;
                                }
                            }
                            if(flag){
                                for(int v = 0; v < id; v++){
                                    if(cross[u][v] > 0){
                                        if(!visit[v]){
                                            st.push_back(v);
                                            visit[v] = true;
                                            break;
                                        }
                                        if(visit[v]){
                                            el = v;
                                            break;
                                        }
                                    }
                                }
                            }
                            if(st.back()==u) break;
                            assert(!st.empty());
                        }
                        int v = el;
                        while(!st.empty() && st.back() != el){
                            int u = st.back();
                            cross[u][v]--;
                            num++;
                            st.pop_back();
                            v = u;
                        }
                        assert(st.back() == el);
                        cross[el][v]--;
                    }
                }
            }
        }
        cout<<num<<'\n';
    }
    return 0;
}
