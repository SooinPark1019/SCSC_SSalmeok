vector<int> graph[MAX+5];
int lvl[MAX+5];
vector<pii> bridge;
vector<int> artpoint;
int DP[MAX+5];
int down[MAX+5];
int cycle[MAX+5];
int cidx;
//*****주의!!!!!!!!! 반드시!!!!!!!! lvl[root]=1 하고 해야 함!!!!!!!! 제발 봐줘!!!!! 놓치면 인생망한다!!!!*****
void dfs(int cur_node, int p){
    DP[cur_node]=0;
    cycle[cur_node]=cur_node;
    int f=0;
    int cnt=0, pre=0;
    for(int nxt : graph[cur_node]){
        if(nxt==p) continue;
        if(lvl[nxt]==0){//spanning edge
            lvl[nxt]=lvl[cur_node]+1;
            dfs(nxt, cur_node);
            DP[cur_node]+=DP[nxt];
            cnt+=DP[cur_node]==pre;
        }
        else if(lvl[nxt]<lvl[cur_node]){
            DP[cur_node]++;
            DP[nxt]--;
            down[nxt]++;
            f=1;
        }
        pre=DP[cur_node];
    }
    if(lvl[cur_node]!=1&&DP[cur_node]==0){//bridge
        bridge.push_back({cur_node, p});
    }
    if((!p&&cnt>1)||(p&&cnt)){
        artpoint.push_back(cur_node);
    }
    if(f){//cycle compression(if cactus)
        cycle[cur_node]=cidx++;
    }
    else{
        for(auto nxt : graph[cur_node]){
            if(cycle[nxt]!=nxt&&!down[nxt]) cycle[cur_node]=cycle[nxt];
        }
    }
}

//lvl[1]=1;
//cidx=N+1
