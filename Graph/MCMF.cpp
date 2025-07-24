vector<int> graph[205];
int d[205][205]={};//비용
int c[205][205]={};//용량
int f[205][205]={};//유량
int inqueue[205]={}, vis[205]={}, dist[205]={}, s=201, e=202, N, M;
int main() {
    cin >> N >> M;
    //그래프 구성
    int result=0;//최소비용
    int maxflow=0;//최대유량
    while(1){
        memset(vis, -1, sizeof(vis));
        memset(inqueue, 0, sizeof(inqueue));
        fill(dist, dist+204, INF);
        queue<int> Q;
        dist[s]=0;
        vis[s]=0;
        inqueue[s]=1;
        Q.push(s);
        while(!Q.empty()){
            int x=Q.front();
            Q.pop();
            inqueue[x]=0;
            for(auto i : graph[x]){
                if(dist[i]>dist[x]+d[x][i]&&c[x][i]>f[x][i]){
                    dist[i]=dist[x]+d[x][i];
                    vis[i]=x;
                    if(inqueue[i]==0){
                        Q.push(i);
                        inqueue[i]=1;
                    }
                }
            }
        }
        if(vis[e]==-1) break;
        int a=INF;
        for(int i=e; i!=s; i=vis[i]){
            a=min(a, c[vis[i]][i]-f[vis[i]][i]);
        }
        for(int i=e; i!=s; i=vis[i]){
            f[vis[i]][i]+=a;
            f[i][vis[i]]-=a;
            result+=d[vis[i]][i]*a;
        }
        maxflow+=a;
    }
    return 0;
}