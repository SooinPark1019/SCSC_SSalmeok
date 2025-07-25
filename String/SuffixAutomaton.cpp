const int MAX = 1000000;
int sz = 0;
map<int, int> T[2*MAX];
int L[2*MAX], SL[2*MAX];
void suffixautomaton(const string &s) {
    int n = s.size();
    SL[sz++] = -1;
    int x0 = 0;
    for(char c : s) {
        int x = sz++;
        L[x] = L[x0]+1;
        int p = x0;
        while(p != -1 && T[p][c] == 0) {
            T[p][c] = x;
            p = SL[p];
        }
        if(p == -1) SL[x] = 0;
        else {
            int q = T[p][c];
            if(L[p]+1 == L[q]) SL[x] = q;
            else {
                int r = sz++;
                T[r] = T[q];
                SL[r] = SL[q];
                L[r] = L[p]+1;
                SL[x] = SL[q] = r;
                while(p != -1 && T[p][c] == q) {
                    T[p][c] = r;
                    p = SL[p];
                }
            }
        }
        x0 = x;
    }
}

const int MAX = 1000000;
int sz = 0;
int T[2*MAX][26];
int L[2*MAX], SL[2*MAX];
void suffixautomaton_fast(const string &s) {
    int n = s.size();
    SL[sz++] = -1;
    int x0 = 0;
    for(char c_ : s) {
        int c = c_-'a';
        int x = sz++;
        L[x] = L[x0]+1;
        int p = x0;
        while(p != -1 && T[p][c] == 0) {
            T[p][c] = x;
            p = SL[p];
        }
        if(p == -1) SL[x] = 0;
        else {
            int q = T[p][c];
            if(L[p]+1 == L[q]) SL[x] = q;
            else {
                int r = sz++;
                copy(T[q], T[q]+26, T[r]);
                SL[r] = SL[q];
                L[r] = L[p]+1;
                SL[x] = SL[q] = r;
                while(p != -1 && T[p][c] == q) {
                    T[p][c] = r;
                    p = SL[p];
                }
            }
        }
        x0 = x;
    }
}