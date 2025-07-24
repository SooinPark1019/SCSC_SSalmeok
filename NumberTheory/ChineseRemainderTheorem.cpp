// gcd(a,b), s,t where a*s + b*t = gcd(a,b)
pair<ll,pair<ll,ll>> xGCD(ll a, ll b) {
    if(b == 0) return {a,{1,0}};
    pair<ll,pair<ll,ll>> ret = xGCD(b, a%b);
    ll g, x, y;
    g = ret.first;
    tie(x,y) = ret.second;
    return {g,{y,x-(a/b)*y}};   
}
// A = [a_1, a_2, ... , a_N]
// M = [m_1, m_2, ... , m_N]
// each equation is x = a_i (mod m_i)
// it returns {-1,-1} if there's no solution satisfying N linear congruence equations.
pair<ll,ll> CRT(vector<ll> &A, vector<ll> &M) {
    if(A.size() != M.size()) return {-1,-1};
    int N = A.size();
    ll a1 = A[0];
    ll m1 = M[0];
    a1 %= m1;
    for(int i=1;i<N;++i) {
        ll a2 = A[i];
        ll m2 = M[i];
        ll g = __gcd(m1, m2);
        if(a1 % g != a2 % g) return {-1,-1};
        ll p, q;
        auto res = xGCD(m1/g, m2/g);
        tie(p,q) = res.second;
        i128 mod = (i128)m1 / g * m2;
        a1 = ((i128)a1 * (m2/g) % mod) * q % mod + ((i128)a2*(m1/g)%mod)*p % mod;
        a1 = (a1 + mod) % mod;
        m1 = mod;
    }
    return {a1, m1};
}