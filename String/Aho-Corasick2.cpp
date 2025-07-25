// 알파벳 따라서, 구하려는 값 따라서 수정 필요 (수정 필요한 곳은 //로 표시)
vector<vector<int>> T;
vector<int> F;
void aho_pre(vector<string>& S) { // 전처리, O(26*N)
    T = {vector<int>(27)}; //
    T[0][26] = -1; //
    for(int j=0; j<S.size(); j++) {
        int i = 0;
        for(char c : S[j]) {
            int x = c-'a'; //
            if(T[i][x] == 0) {
                T[i][x] = T.size();
                T.push_back(vector<int>(27)); //
                T[T.size()-1][26] = -1; //
            }
            i = T[i][x];
        }
        T[i][26] = j; //
    }

    int m = T.size();
    F = vector<int>(m);
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()) {
        int s = Q.front(); Q.pop();
        for(int x=0; x<26; x++) { //
            int e = T[s][x];
            if(e == 0) continue;
            Q.push(e);

            int p = F[s];
            while(p && T[p][x] == 0) p = F[p];
            if(p == s) F[e] = 0;
            else {
                F[e] = T[p][x];
                T[e][26] = max(T[e][26], T[F[e]][26]); //
            }
        }
    }
}
vector<int> aho_match(string& s) { // 매칭, O(M)
    int p = 0;
    vector<int> R(s.size());
    for(int i=0; i<s.size(); i++) {
        int x = s[i]-'a'; //
        while(p && T[p][x] == 0) p = F[p];
        p = T[p][x];
        R[i] = T[p][26]; //
    }
    return R;
}


int main() { // 문자열 집합 판별 : S에 t의 부분문자열이 나오는지 판별
    cin.tie(0)->sync_with_stdio(0);


    int n; cin >> n;
    vector<string> S(n); for(int i=0; i<n; i++) cin >> S[i];
    aho_pre(S);

    int m; cin >> m;
    for(int i=0; i<m; i++) {
        string t; cin >> t;
        vector<int> L = aho_match(t);
        cout << (*max_element(L.begin(), L.end()) != -1 ? "YES" : "NO") << '\n';
    }
    


}
