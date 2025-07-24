const int MAX = 100000, D = 18;  // 2^(D-1) < MAX <= 2^D
int N, depth[MAX], sp[D][MAX];
vector<int> graph[MAX];
void lca_dfs(int x) {  // 모든 정점의 깊이와 부모를 전처리, 루트 노드의 부모가 자기 자신이 되도록 구현하면 편리함
    for (auto& nx : graph[x]) {
        if (depth[nx] > -1) continue;
        depth[nx] = depth[x] + 1;
        sp[0][nx] = x;
        lca_dfs(nx);
    }
}
int LCA(int a, int b) {
    if (depth[b] > depth[a]) swap(a, b);
    for (int j = D - 1; j >= 0; --j) {  // 두 정점의 깊이를 동일하게 만드는 과정
        if (depth[a] - depth[b] & (1 << j)) a = sp[j][a];
    }
    if (a == b) return a;  // a 또는 b가 LCA인 경우
    for (int j = D - 1; j >= 0; --j) {  // 공통 조상을 찾는 과정
        if (sp[j][a] != sp[j][b]) {
            a = sp[j][a];
            b = sp[j][b];
        }
    }
    return sp[0][a];
}
int main() { cin >> graph;
    memset(depth, -1, sizeof(depth)); depth[0] = 0;
    lca_dfs(0);
    for (int i = 1; i < D; ++i) {  // 희소 배열 구성
        for (int j = 0; j < N; ++j) {
            sp[i][j] = sp[i - 1][sp[i - 1][j]];
        }
    } // LCA를 원하는 곳에 사용
}