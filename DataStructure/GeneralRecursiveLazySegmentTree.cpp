@param
// a : 초기 배열
// n : a.size()
// T : 트리 노드의 type
// S : 레이지의 type
// change하라는 부분만 수정하면 됨

template <class T, class S>
class lazySegTree{
public:
    lazySegTree(vector<T> a_, int n_) : a(a_), n(n_) {
        // change from here
        f_identity = ; // TODO
        lazy_identity = ; // TODO
        // to here

        int maxn = getMax(n);
        tree = vector<T>(maxn, f_identity);
        lazy = vector<S>(maxn, lazy_identity);
        init(1, 0, n-1);

    }

    T Query(int left, int right){
        return query(1, 0, n-1, left, right);
    }

    void Range_update(int left, int right, S val){
        range_update(1, 0, n-1, left, right, val);
    }
    
    void Update_diff(int index, S val){
        // a[index] += val
        Range_update(index, index, val);
    }

private:
    int n;
    T f_identity;
    S lazy_identity;
    vector<T> a;
    vector<S> lazy;
    vector<T> tree;

    int getMax(int n){
        return 4*n;
    }

    void init(int node, int start, int end){
        if (start == end) tree[node] = a[start];
        else{
            init(node*2, start, (start+end)/2);
            init(node*2+1, (start+end)/2+1, end);
            tree[node] = T_merge(tree[node*2], tree[node*2+1]);
        }
    }

    // change from here to 
    inline T T_merge(T lval, T rval){
         // TODO
    }

    inline S S_merge(S lval, S rval){
        // rval acts on lval
        // TODO
    }

    inline void act(int node, int start, int end, S lazy){
        // TODO
    }
    // here

    void lazy_update(int node, int start, int end){
        if (lazy[node] != lazy_identity){
            act(node, start, end, lazy[node]);

            if (start != end){
                lazy[node*2] = S_merge(lazy[node*2], lazy[node]);
                lazy[node*2+1] = S_merge(lazy[node*2+1], lazy[node]);
            }
            
            lazy[node] = lazy_identity;
        }
    }

    T query(int node, int start, int end, int left, int right){
        lazy_update(node, start, end);

        if (left > end || right < start) return f_identity;
        if (left <= start && end <= right) return tree[node];

        T lsum = query(node*2, start, (start+end)/2, left, right);
        T rsum = query(node*2+1, (start+end)/2+1, end, left, right);
        return T_merge(lsum, rsum);
    }
    
    void range_update(int node, int start, int end, int left, int right, S val){
        lazy_update(node, start, end);

        if (left > end || right < start) return;
        if (left <= start && end <= right){
            act(node, start, end, val);
            if (start != end) {
                lazy[node*2] = S_merge(lazy[node*2], val);
                lazy[node*2+1] = S_merge(lazy[node*2+1], val);
            }
            return;
        }

        range_update(node*2, start, (start+end)/2, left, right, val);
        range_update(node*2+1, (start+end)/2+1, end, left, right, val);
        tree[node] = T_merge(tree[node*2], tree[node*2+1]);
    }
    
};
