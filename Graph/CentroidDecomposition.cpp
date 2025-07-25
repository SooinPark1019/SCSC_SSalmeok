const int MAX = 200000;
int N, K, sub[MAX];
vector<int> graph[MAX];
bool visited[MAX];
int getSub(int x, int px) {
    sub[x] = 1;
    for (auto& nx : graph[x]) {
        if (visited[nx] || nx == px) continue;
        sub[x] += getSub(nx, x);
    }
    return sub[x];
}
int getCentroid(int x) {  // 조금 더 빠르고 센트로이드를 구할 때마다 getSub을 호출하지 않아도 가능
    for (auto& nx : graph[x]) {
        if (sub[x] < 2 * sub[nx] && sub[nx] < sub[x]) {
            sub[x] -= sub[nx];
            sub[nx] += sub[x];
            return getCentroid(nx);
        }
    }
    return x;
}
int getCentroid(int x, int px, int cap) {  // 센트로이드를 구할 때마다 getSub을 호출
    for (auto& nx : graph[x]) {
        if (!visited[nx] && nx != px && sub[nx] * 2 > cap) return getCentroid(nx, x, cap);
    }
    return x;
}
/* Divide & Conquer 구성 방법
 * dnc(x): 현재 x번 노드를 포함하는 서브 트리에서 문제를 해결
 * getCentroid(x): x에 센트로이드 구해서 대입
 * solve(x): x를 지나는 모든 경로에 대해 계산
 * x를 트리에서 제거, x와 인접한 모든 노드 y에 대해 dnc(y) 실행 (상황에 따라 전역 벡터 visited로 관리)
 */
void solve(int x) {}
void dnc(int x) {
    x = getCentroid(x);  // x = getCentroid(x, -1, getSub(x, -1));

    visited[x] = 1;  // 센트로이드가 되었던 정점은 더이상 사용하지 않는 것을 유의
    for (auto& nx : graph[x]) {
        if (visited[nx]) continue;
        solve(nx);
    }
    
    for (auto& nx : graph[x]) {
        if (visited[nx]) continue;
        dnc(nx);
    }
}