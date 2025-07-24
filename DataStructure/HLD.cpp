vector<ll> V(MAXN, 0);
vector<int> graph[MAXN];
ll sz[MAXN], dep[MAXN], top[MAXN], par[MAXN], in[MAXN], out[MAXN];
vector<int> child[MAXN];
int pv=0, N;

////Seg 알아서 구현

void dfs1(int cur_node, int p){
    for(auto i : graph[cur_node]){
        if(i==p) continue;
        par[i]=cur_node;
        child[cur_node].push_back(i);
        dfs1(i, cur_node);
    }
}
void dfs2(int cur_node){
    sz[cur_node]=1;
    for(auto &i : child[cur_node]){
        dep[i]=dep[cur_node]+1;
        dfs2(i);
        sz[cur_node]+=sz[i];
        if(sz[i]>sz[child[cur_node][0]]) swap(i, child[cur_node][0]);
    }
}
void dfs3(int cur_node){
    in[cur_node]=++pv;
    for(auto i : child[cur_node]){
        if(i==child[cur_node][0]) top[i]=top[cur_node];
        else top[i]=i;
        dfs3(i);
    }
    out[cur_node]=pv;
}

void hldplusupd(int a, int b, int val){//rangeHldUpdate
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]) swap(a, b);
        int st=top[a];
        seg.UpdateSeg(1, 0, N, in[st], in[a], 1, val);
        a=par[st];
    }
    if(dep[a]>dep[b]) swap(a, b);
    seg.UpdateSeg(1, 0, N, in[a], in[b], 1, val);
    return;
}
ll hldquery(int a, int b){//rangeHldSumQuery
    ll ret=0;
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]) swap(a, b);
        int st=top[a];
        ret+=seg.SumSeg(1, 0, N, in[st], in[a]);
        ret%=mod;
        a=par[st];
    }
    if(dep[a]>dep[b]) swap(a, b);
    ret+=seg.SumSeg(1, 0, N, in[a], in[b]);
    ret%=mod;
    return ret;
}