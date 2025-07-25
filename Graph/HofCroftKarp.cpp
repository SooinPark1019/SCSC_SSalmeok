const int MAX = 10000;
int N, A[MAX], B[MAX], level[MAX], matches;
bool used[MAX];
vector<int> graph[MAX];
void fastbp_bfs() {  // Fast Bipartite Matching (similar to Dinic's algorithm)
    queue<int> q;
    for (int i = 0; i < N; ++i) {
        if (!used[i]) {
            level[i] = 0;
            q.push(i);
        }
        else level[i] = -1;
    }

    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (auto& nx : graph[x]) {
            if (B[nx] != -1 && level[B[nx]] < 0) {
                level[B[nx]] = level[x] + 1;
                q.push(B[nx]);
            }
        }
    }
}
bool fastbp_dfs(int x) {
    for (auto& nx : graph[x]) {
        if (B[nx] == -1 || level[B[nx]] == level[x] + 1 && fastbp_dfs(B[nx])) {
            used[x] = 1;
            A[x] = nx;
            B[nx] = x;
            return 1;
        }
    }
    return 0;
}
int main() { cin >> graph;
    memset(A, -1, sizeof(A)); memset(B, -1, sizeof(B));
    while (1) {
        fastbp_bfs();
        int new_flow = 0;
        for (int i = 0; i < N; ++i) {
            if (!used[i] && fastbp_dfs(i)) new_flow++;
        }
        if (new_flow == 0) break;
        matches += new_flow;
    }
}