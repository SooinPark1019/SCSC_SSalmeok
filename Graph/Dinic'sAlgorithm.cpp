const int MAX = 500 + 2, INF = 1e9 + 7, S = MAX - 2, T = MAX - 1;  // source & sink
int N, cap[MAX][MAX], flow[MAX][MAX], level[MAX], work[MAX];
bool visited[MAX];
vector<int> graph[MAX];
bool dinic_bfs() {  // 레벨 그래프를 만들기 위한 BFS
    memset(level, -1, sizeof(level));
    level[S] = 0;

    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto& nx : graph[x]) {
            if (level[nx] < 0 && cap[x][nx] > flow[x][nx]) {
                level[nx] = level[x] + 1;
                q.push(nx);
            }
        }
    }
    return level[T] != -1;
}
int dinic_dfs(int x, int dest, int max_flow) {
    if (x == dest) return max_flow;
    for (int& i = work[x]; i < graph[x].size(); ++i) {  // 이미 탐색한 간선을 재탐색하지 않기 위해 work 배열 사용
        int nx = graph[x][i];
        if (level[nx] == level[x] + 1 && cap[x][nx] > flow[x][nx]) {  // level 차이 1인 간선만 이용 가능
            int new_flow = dinic_dfs(nx, dest, min(cap[x][nx] - flow[x][nx], max_flow));
            if (new_flow > 0) {
                flow[x][nx] += new_flow;
                flow[nx][x] -= new_flow;
                return new_flow;
            }
        }
    }
    return 0;
}
int main() { cin >> graph;  // graph 입력
    int ans = 0;  // max-flow = min-cut
    while (dinic_bfs()) {  // 1. 레벨 그래프 생성
        memset(work, 0, sizeof(work));
        while (1) {  // 2. 차단 유량 계산
            int new_flow = dinic_dfs(S, T, INF);
            if (new_flow == 0) break;
            ans += new_flow;
        }
    }
    visited[S] = 1;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {  // source에서 방문 가능한 정점과 그렇지 않은 정점들이 min-cut으로 나뉘게 됨
        int x = q.front();
        q.pop();
        for (auto& nx : graph[x]) {
            if (visited[nx]) continue;
            if (cap[x][nx] > flow[x][nx]) {
                visited[nx] = 1;
                q.push(nx);
            }
        }
    }
}