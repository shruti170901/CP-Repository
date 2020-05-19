#include<bits/stdc++.h>
using namespace std;

int bfsearch(vector<vector<int>> rGraph, int t, int s, int parent[]) { 
    int V = rGraph.size();
    bool visited[V]; 
    memset(visited, 0, sizeof(visited)); 
    queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parent[s] = -1; 
    while (!q.empty()) { 
        int u = q.front(); 
        q.pop(); 
        for (int v=0; v<V; v++) { 
            if (visited[v]==false && rGraph[u][v] > 0) { 
                q.push(v); 
                parent[v] = u; 
                visited[v] = true; 
            } 
        } 
    } 
    return (visited[t] == true); 
} 

void dfsearch(vector<vector<int>> rGraph, int s, bool visited[]) { 
    int V = rGraph.size();
    visited[s] = true; 
    stack<int> st;
    st.push(s);
    while(!st.empty()){
        int u = st.top();
        bool flag = true;
        for(int v = 0; v < V; v++){
            if(rGraph[u][v] && !visited[v]){
                flag = false;
                visited[v] = true;
                st.push(v);
                break;
            }
        }
        if(flag)st.pop();
    }
} 
  
void min_cut(vector<vector<int>> graph, int t, int s, int alsum) { 
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int V = graph.size();
    int u, v; 
    vector<vector<int>> rGraph(V);
    vector<int> tGraph(V);
    for(int n = 0; n < V; n++)tGraph[n] = 0;
        for(int n = 0; n < V; n++)rGraph[n] = tGraph;
    for (u = 0; u < V; u++) 
        for (v = 0; v < V; v++) 
             rGraph[u][v] = graph[u][v]; 
    int parent[V]; 
    while (bfsearch(rGraph, t, s, parent)) { 
        int path_flow = INT_MAX; 
        for (v=t; v!=s; v=parent[v]) { 
            u = parent[v]; 
            path_flow = min(path_flow, rGraph[u][v]); 
        } 
        for (v=t; v != s; v=parent[v]) { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 
    } 
    bool visited[V]; 
    memset(visited, false, sizeof(visited)); 
    dfsearch(rGraph, s, visited); 
    int cost = 0;
    for (int i = 0; i < V; i++) 
      for (int j = 0; j < V; j++) 
         if (visited[i] && !visited[j] && graph[i][j]) 
              cost += graph[i][j] + graph[j][i];
    cout<<alsum-cost<<endl;
    for(int i = V/2; i < V-1; i++) {
        if(visited[i])cout<<1<<" ";
        else cout<<-1<<" ";
    }
    cout<<"\n"; 
} 

int main(void) {
    ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    int t;
    cin>>t;
    for(int q=1;q<=t;q++){
        int H, W, N;
        cin>>H>>W>>N;
        int arr[H][W];
        bool points[H][W];
        for(int h = 0; h < H; h++) {
            for(int w = 0; w < W; w++){
                points[h][w] = false;
                cin>>arr[h][w];
            }
        }
        vector<pair<pair<int, int>, int > >  P(N);
        pair<pair<int, int>, int> p;
        pair<int, int> pt;
        unordered_map<int, int> idx;
        for(int n = 0; n < N; n++){
            cin>>pt.first>>pt.second;
            pt.first--;pt.second--;
            cin>>p.second;
            p.first=pt;
            points[pt.first][pt.second] = true;
            P[n] = p;
            idx[pt.first*W + pt.second] = n;
        }
        vector<vector<int>> graph(2*N+2);
        vector<int> tgraph(2*N+2);
        for(int n = 0; n < 2*N+2; n++)tgraph[n] = 0;
        for(int n = 0; n < 2*N+2; n++)graph[n] = tgraph;
        int s = 0;
        for(int n = 0; n <N; n++){
            if(arr[P[n].first.first][P[n].first.second] > 0){
                graph[n+1][N+n+1] = graph[N+n+1][n+1] = abs(P[n].second*arr[P[n].first.first][P[n].first.second]);
                s+=abs(P[n].second*arr[P[n].first.first][P[n].first.second]);
                graph[0][n+1] = 1000000000;
            }
            else {
                graph[n+1][2*N+1] = 1000000000;
                graph[N+n+1][n+1] = graph[n+1][N+n+1] = abs(P[n].second*arr[P[n].first.first][P[n].first.second]);
                s += abs(P[n].second*arr[P[n].first.first][P[n].first.second]);
            }
            if(P[n].first.first < H-1 && points[P[n].first.first+1][P[n].first.second]){
                int id = N+idx[(P[n].first.first+1)*W + P[n].first.second]+1;
                int idn = N+n+1;
                graph[id][idn] = graph[idn][id] = abs(P[n].second * P[id - N-1].second);
                s += abs(P[n].second * P[id - N-1].second);
            }
            if(P[n].first.second < W-1 && points[P[n].first.first][P[n].first.second +1]){
                int id = N+idx[(P[n].first.first)*W + P[n].first.second + 1]+1;
                int idn = N+n+1;
                graph[id][idn] = graph[idn][id] = abs(P[n].second * P[id - N-1].second);
                s += abs( P[n].second * P[id - N-1].second);
            }
        }
        min_cut(graph, 2*N+1,0, s);
    }
    return 0;
}
