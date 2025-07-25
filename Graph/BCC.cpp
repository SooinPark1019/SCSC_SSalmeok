const int MAX = 100000;
int N, M, dn[MAX], dnum;
vector<int> graph[MAX];
vector<int> ap;  // 단절점 (필요하지 않은 경우 // 단절점 코드 주석으로 사용)
vector<pair<int, int>> bridges;  // 단절선 (필요하지 않은 경우 // 단절선 코드 주석으로 사용)
vector<vector<pair<int, int>>> bcc;
stack<pair<int, int>> ST;
int bcc_dfs(int x, int px) {
    int ret = dn[x] = ++dnum;
    int is_art_point = 0, childs = 0;  // 단절점
    int is_bridge = 0;  // 단절선
    for (auto& nx : graph[x]) {
        if (nx == px) continue;
        if (dn[nx] > 0) ret = min(ret, dn[nx]);  // 역방향 간선
        else {  // 정방향 간선 (트리 간선)
            ST.push({ x, nx });  // 서로 다른 BCC에 같은 간선이 포함될 수 있는 이유
            int next_dn = bcc_dfs(nx, x);
            ret = min(ret, next_dn);
            childs++;  // 단절점
            if (next_dn > dn[x]) bridges.push_back({ nx, x });  // 단절선
            if (next_dn >= dn[x]) {
                if (px > -1) is_art_point = 1;  // 단절점
                bcc.push_back({});
                while (1) {
                    pair<int, int> st_top = ST.top();
                    ST.pop();
                    bcc.back().push_back(st_top);
                    if (st_top == pair<int, int>{ x, nx }) break;
                }
            }
        }
    }
    if (px == -1 && childs > 1 || is_art_point) ap.push_back(x);  // 단절점
    return ret;
}
int main() { cin >> graph;
    for (int i = 0; i < N; ++i) {  // 방문하지 않은 모든 정점에 대해 bcc_dfs 진행
        if (dn[i] == 0) bcc_dfs(i, -1);
    }
}