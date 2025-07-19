// 롤백유파에서는 경로압축하면 시간도 메모리도 터지고 망함
// 그래서 log를 보장하기 위해 union by rank를 사용

struct UFrollback{
    vector<int> par, sz, rank;
    int n;

    struct info{
        int u, v, pu, pv, szu, szv, ru, rv;
    };
    vector<info> trace;
    
    UFrollback(int n_){
        n = n_;
        par.resize(n+1);
        sz.resize(n+1);
        rank.resize(n+1);
        init();
        trace.clear();
    }
    
    void init(){
        for (int i = 1; i <= n; i++){
            par[i] = i;
            sz[i] = 1;
            rank[i] = 0;
        }
    }
    int get(int u){
        if (u == par[u]) return u;
        return get(par[u]);
    }
    void merge(int u, int v){
        u = get(u);
        v = get(v);

        if (u == v) return;
        if (rank[v] > rank[u]) swap(u, v);

        trace.push_back({u, v, par[u], par[v], sz[u], sz[v], rank[u], rank[v]});

        par[v] = u;
        sz[u] += sz[v];
        rank[u] = max(rank[u], rank[v] + 1);
    }
    int getsz(int u){
        return sz[get(u)];
    }
    bool same(int u, int v){
        return get(u) == get(v);
    }
    void rollback(int SZ=0){
        // 가장 최근 merge부터 순차적으로 rollback
        // 전체 롤백하려면 rollback()
        // 특정 시점까지 롤백하려면
        // 원하는 시점의 sz:=trace.size()를 저장하고 rollback(sz)

        while (trace.size() > SZ){
            info cur = trace.back();

            int u = cur.u;
            int v = cur.v;
            // par[u] = cur.pu;
            par[v] = cur.pv;
            sz[u] = cur.szu;
            rank[u] = cur.ru;
            // sz[v] = cur.szv;

            trace.pop_back();
        }
    }
};
