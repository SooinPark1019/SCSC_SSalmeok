#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> G;
vector<int> L, S, D;
vector<vector<pair<int, int>>> X;
int getsize(int s, int p) {
    L.push_back(s);
    S[s] = 1;
    for(int e : G[s]) if(p != e && S[e] != -1) S[s] += getsize(e, s);
    return S[s];
}
int getcent(int s, int p, int m) {
    for(int e : G[s]) if(p != e && S[e] != -1) if(S[e] > m/2) return getcent(e, s, m);
    return s;
}
void dfs(int s, int p, int d, int x) {
    X[s].push_back({x, d});
    for(int e : G[s]) if(p != e && S[e] != -1) dfs(e, s, d+1, x);
}
void f(int s) {
    L.clear();
    int x = getcent(s, -1, getsize(s, -1));
    dfs(x, -1, 0, x);
    if(S[x] == 1) return;
    S[x] = -1;
    for(int y : G[x]) if(S[y] != -1) f(y);
}

// 트리와 쿼리 5
// 1 a : 정점 a 색 변경
// 2 a : 정점 a와 흰색 정점 사이 최소 거리 출력
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    G.resize(n);
    for(int i=0; i<n-1; i++) {
        int a, b; cin >> a >> b; a--, b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    S.resize(n);
    X.resize(n);
    f(0);

    vector<int> A(n);
    vector<set<pair<int, int>>> Q(n);
    int q; cin >> q;
    while(q--) {
        int t, a; cin >> t >> a; a--;
        if(t == 1) {
            A[a] ^= 1;
            if(A[a] == 1) for(auto p : X[a]) Q[p.first].insert({p.second, a});
            else for(auto p : X[a]) Q[p.first].erase({p.second, a});
        }
        else {
            int ans = n;
            for(auto p : X[a]) if(!Q[p.first].empty()) ans = min(ans, p.second+ Q[p.first].begin()->first);
            cout << (ans == n ? -1 : ans) << '\n';
        }
    }


}