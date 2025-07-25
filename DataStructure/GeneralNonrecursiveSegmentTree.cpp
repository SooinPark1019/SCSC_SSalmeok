template <class T>
struct segTree{
    // 0-BASED
    vector<T> t;
    T id;
    int n;

    segTree(int n_, T id_){
        n = n_;
        id = id_;
        t = vector<T>(n*2, id);
    }

    inline T merge(T n1, T n2){
        if (n1.isidentity) return n2;
        if (n2.isidentity) return n1;

        return Node(
            max(n1.lsum, n1.sum + n2.lsum),
            max(n2.rsum, n1.rsum + n2.sum),
            max(n1.q, max(n1.rsum + n2.lsum, n2.q)),
            n1.sum + n2.sum
        );
    }
    inline T add(T n1, T n2){
        if (n1.isidentity) return n2;
        if (n2.isidentity) return n1;

        Node res(n1.sum + n2.sum, false);
        return res;
    }

    void update(int idx, T val){
        for (t[idx+=n] = val; idx >>= 1; ){
            t[idx] = merge(t[idx<<1], t[idx<<1|1]);
        }
    }
    void update_diff(int idx, T val){
        idx += n;
        t[idx] = add(t[idx], val);
        for (; idx >>= 1; ){
            t[idx] = merge(t[idx<<1], t[idx<<1|1]);
        }
    }

    T query(int l, int r){
        // [l, r)        
        T resl = id;
        T resr = id;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) resl = merge(resl, t[l++]);
            if (r&1) resr = merge(t[--r], resr); 
        }
        return merge(resl, resr);
    }

};
