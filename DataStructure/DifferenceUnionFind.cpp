/// @brief 두 원소간의 차이를 관리하는 유니온파인드
/// 다음과 같은 쿼리를 갖는 문제를 해결할 수 있다
/// 1 u v w : X_u - X_v = w 조건 추가
/// 2 u v : X_u - X_v 출력
/// 이때 출력 불가능한지, 모순이 생기는지도 판단해야 함
/// false, 0 은 출력 불가능(모름), false, -1은 모순
/// @tparam cost_t 
template<typename cost_t>
struct weighted_union_find{
    vector<int> p, die;
    vector<cost_t> d;
    weighted_union_find(int n) : p(n), die(n,0), d(n,0) { iota(p.begin(), p.end(), 0); }
    pair<int,cost_t> find(int v){
        if(v == p[v]) return {v, 0};
        auto [root,diff] = find(p[v]);
        p[v] = root; d[v] += diff;
        return {p[v], d[v]};
    }
    void merge(int u, int v, cost_t w){
        auto [pu,wu] = find(u);
        auto [pv,wv] = find(v);
        if(pu == pv){ die[pv] |= wv - wu - w != 0; return; }
        p[pu] = pv; die[pv] |= die[pu];
        d[pu] = wv - wu - w;
    }
    pair<bool,cost_t> get_difference(int u, int v){ // return W[v] - W[u]
        auto [pu, du] = find(u);
        auto [pv, dv] = find(v);
        if(pu == pv && !die[pv]) return {true, dv - du};
        else if(pu == pv && die[pv]) return {false, cost_t(-1)};
        else return {false, cost_t(0)};
    }
};
