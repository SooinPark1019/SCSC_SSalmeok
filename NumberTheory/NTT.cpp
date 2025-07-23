void ntt(vector<ll> &P, bool inverse, ll g){
    int n = P.size();
    if (n == 1) return;

    for (int i = 0; i < n; i++){
        int shift = 0, size = n, idx = i;
        while (size > 1){
            if (idx & 1) shift += size >> 1;
            size >>= 1;
            idx >>= 1;
        }
        if (shift < i) swap(P[shift], P[i]);
    }

    for (int i = 1; i < n; i <<= 1){
        // n = 2*i에서 ntt

        ll unit = power(g, n/(2*i));
        if (inverse) unit = power(unit, MOD-2);

        for (int j = 0; j < n; j += i << 1){

            ll w = 1;
            for (int k = 0; k < i; k++){
                ll tmp = (P[i+j+k] * w) % MOD;
                P[i+j+k] = P[j+k] + MOD - tmp;
                P[j+k] += tmp;
                w *= unit;
                P[i+j+k] %= MOD;
                P[j+k] %= MOD;
                w %= MOD;
            }
        }
    }


    if (inverse){
        ll invn = power(n, MOD-2);
        for (int i = 0; i < n; i++){
            P[i] *= invn;
            P[i] %= MOD;
        }
    }
}
ll f(ll v){
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    // v |= v >> 32;
    v++;
    return v;
}
vector<ll> polymul(vector<ll> v1, vector<ll> v2){
    // NTT mod 998244353

    ll n1 = v1.size();
    ll n2 = v2.size();

    ll N = f(n1 + n2 - 1);

    v1.resize(N);
    v2.resize(N);

    ll g = power(3, 998244353 / N);
    ntt(v1, false, g);
    ntt(v2, false, g);

    vector<ll> res(N);
    for (int i = 0; i < N; i++){
        res[i] = v1[i] * v2[i];
    }

    ntt(res, true, g);

    return res;
}
