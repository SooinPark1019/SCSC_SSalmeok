const int MAX = 1000;
int N, M, dn[MAX], sn[MAX], dnum, snum;  // dfs number & scc number
vector<int> graph[MAX];
vector<vector<int>> scc;
stack<int> ST;
int scc_dfs(int x) {
    int ret = dn[x] = ++dnum;
    ST.push(x);
    for (auto& nx : graph[x]) {  // 문제에서 간선이 어떻게 주어지는지에 따라 수정이 필요할 수 있음    
        if (dn[nx] == 0) ret = min(ret, scc_dfs(nx));
        else if (sn[nx] == 0) ret = min(ret, dn[nx]);
    }
    if (ret == dn[x]) {
        ++snum;
        scc.push_back({});
        while (1) {
            int st_top = ST.top();
            ST.pop();
            sn[st_top] = snum;
            scc.back().push_back(st_top);
            if (st_top == x) break;
        }
    }
    return ret;
}
int main() { cin >> graph;
    // 2-SAT을 위해 사용할 경우 boolean 변수를 설정하여 해당 변수의 참, 거짓을 각각 하나의 정점으로 보고 명제에 따라 간선을 연결
    // 2-SAT의 해는 각 boolean 변수의 참, 거짓 정점에 대해 scc number가 작은 것으로 결정
    for (int i = 1; i <= N; ++i) {
        if (dn[i] == 0) scc_dfs(i);  // 방문하지 않은 모든 정점에 대해 scc_dfs를 실행
    }
}