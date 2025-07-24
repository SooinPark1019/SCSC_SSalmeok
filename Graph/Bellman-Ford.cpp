struct edge {
    int x, y, w;
};
const int MAX = 1000, INF = 1e9 + 7;  // 범위에 맞게 자료형과 값 수정
int N, M, dist[MAX], negative_cycle;
int main() { vector<edge> edges(M); cin >> edges; // 문제에 맞게 간선 수정
    for (int i = 1; i <= N; ++i) dist[i] = INF; dist[1] = 0;  // 출발점 위치에 맞게 인덱스 수정
    for (int i = 0; i < N; ++i) {
    	for (auto& ed : edges) {
  	        int x = ed.x, y = ed.y, w = ed.w;
    	    if (dist[x] < INF && w + dist[x] < dist[y]) {
      	        if (i == N - 1) {
          		    negative_cycle = 1;  // 음수 사이클 존재
          		    break;
          		}
      	        dist[y] = w + dist[x];
      	    }
        }
    }
}
//벨만-포드로 부등식 시스템 풀기
//간략히 말하자면 변수 x1 ... xn N개와, xj - xi <= T 꼴의 부등식 M개가 있을 때, 
//이를 만족하는 변수 {x1 ... xn} 를 O(NM)에 벨만 포드로 찾을 수 있다는 것이다. 
//부등식의 꼴이 간단하기 때문에 복잡한 선형 계획법 알고리즘을 요하지 않는다.
//방법은, xj - xi <= T일때, i -> j로 가는 가중치 T의 간선을 만들어주는 것이다. 
//이러한 일련의 작업이 끝났다면, 임의의 정점 i에서 벨만 포드를 돌렸을 때, xj = xi + ShortestPath(i, j) 라는 값을 대입했을 때 저것을 만족함을 보장할 수 있다. 