const int MAX = 1000;
int N, M, A[MAX], B[MAX], matches;  // A, B는 이분 그래프의 각 정점
bool visited[MAX];
vector<int> graph[MAX]  // 문제에 따라 간선 수정 필요
bool bp_dfs(int x) {
    visited[x] = 1;
    for (auto& nx : graph[x]) {
        if (B[nx] == -1 || !visited[B[nx]] && bp_dfs(B[nx])) {
            A[x] = nx;
            B[nx] = x;
            return 1;
        }
    }
    return 0;
}
int main() { cin >> graph;
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    for (int i = 0; i < N; ++i) {
        memset(visited, 0, sizeof(visited));
        if (bp_dfs(i)) matches++;
    }
}