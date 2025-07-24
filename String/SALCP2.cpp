const int MAX = 4010010, LOGMAX = 22;
int SA[MAX], POS[MAX], LCP[MAX], TMP[MAX], CNT[MAX], RMQ[LOGMAX][MAX];
void salcp(const string &s) { // SA, POS, LCP 구하기 / O(nlogn)
    int n = s.size(), m = max(n, 256); // 알파벳 개수 많다면 수정
    auto csort = [&]() {
        fill(CNT, CNT+m, 0);
        for(int i=0; i<n; i++) CNT[POS[i]]++;
        partial_sum(CNT, CNT+m, CNT);
        for(int i=n-1; i>=0; i--) SA[--CNT[POS[TMP[i]]]] = TMP[i];
    };

    for(int i=0; i<n; i++) SA[i] = i, POS[i] = s[i], TMP[i] = i;
    csort();
    for(int k=1;; k<<=1) {
        int p = 0;
        for(int i=n-k; i<n; i++) TMP[p++] = i;
        for(int i=0; i<n; i++) if(SA[i] >= k) TMP[p++] = SA[i]-k;
        csort();
        TMP[SA[0]] = 0;
        for(int i=1; i<n; i++) {
            TMP[SA[i]] = TMP[SA[i-1]];
            if(!(SA[i-1]+k < n && SA[i]+k < n && POS[SA[i-1]] == POS[SA[i]] && POS[SA[i-1]+k] == POS[SA[i]+k])) TMP[SA[i]]++;
        }
        copy(TMP, TMP+n, POS);
        if(POS[SA[n-1]]+1 == n) break;
    }

    for(int i=0, j=0; i<n; i++, j=max(j-1, 0)) {
        if(POS[i] == 0) continue;
        while(SA[POS[i]-1]+j < n && SA[POS[i]]+j < n && s[SA[POS[i]-1]+j] == s[SA[POS[i]]+j]) j++;
        LCP[POS[i]] = j;
    }
    
    // lcp()나 safind() 사용할거면 아래 코드 사용
    // for(int i=0; i<n; i++) RMQ[0][i] = LCP[i];
    // for(int k=0, t=1; k<LOGMAX; k++, t<<=1) for(int i=0; i<n-(t<<1)+1; i++) RMQ[k+1][i] = min(RMQ[k][i], RMQ[k][i+t]);
}
int lcp(int i, int j) { // S[i...]와 S[j...]의 LCP / O(1)
    int x = POS[i]+1, y = POS[j]+1;
    if(x > y) swap(x, y);
    int k = 31-__builtin_clz(y-x);
    return min(RMQ[k][x], RMQ[k][y-(1<<k)]);
}
int safind(string& s, string& t) { // s의 SA에서 t가 등장하는 위치 / O(m+logn)
    int n = s.size(), m = t.size();
    int p1 = -1, p2 = n, p = n/2, q = p, l = 0;
    if(s.substr(SA[p], m) < t) p1 = p;
    else p2 = p;
    while(l < t.size() && t[l] == s[SA[q]+l]) l++;

    while(p1 < p2-1) {
        p = (p1+p2)/2;
        if(lcp(SA[p], SA[q]) < l) {
            if(p < q) p1 = p;
            else p2 = p;
        }
        else {
            q = p;
            while(l < t.size() && t[l] == s[SA[q]+l]) l++;
            if(t[l] < s[SA[q]+l]) p2 = p;
            else p1 = p;
        }
    }
    return p2;
}

int main() { // 찾기(1786) 코드
    string s; getline(cin, s);
    string t; getline(cin, t);

    s.push_back('#');
    t.push_back(1);

    salcp(s);
    int x = safind(s, t);
    t.back() = 127;
    int y = safind(s, t);

    vector<int> A;
    for(int i=0; i<s.size(); i++) if(x <= POS[i] && POS[i] < y) A.push_back(i+1);
    
    cout << A.size() << endl;
    for(int a : A) cout << a << ' ';
}
