ll crt(int n, const vector<ll> &a, const vector<ll> &p){
    // n = a.size() = p.size()
    // p의 원소들은 pairwise 서로소
    // x = a[i] (mod pi), 0 <= i < n

    ll res = 0;
    ll N = 1;
    for (int i = 0; i < n; i++) N *= p[i];

    for (int i = 0; i < n; i++){
	ll Ni = N / p[i];
	ll Mi = invmod(Ni, p[i]);
	res += a[i] * Mi * Ni % N; // overflow 가능성 있음
	res %= N;
    }

    return res;
}
