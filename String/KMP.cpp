vector<int> failure(string& s){
    vector<int> f(s.length());
    int j=0;
    for(int i=1; i<s.length(); i++){
        while(j>0&&s[i]!=s[j]) j=f[j-1];
        if(s[i]==s[j]) f[i]=++j;
    }
    return f;
}//실패함수 반환
int main(){
    string T, P;
    getline(cin, T);
    getline(cin, P);
    vector<int> f=failure(P);
    int j=0;
    int ans=0;
    vector<int> pos;
    for(int i=0; i<T.length(); i++){
        while(j>0&&T[i]!=P[j]) j=f[j-1];
        if(T[i]==P[j]) j++;
        if(j==P.length()){
            ans++;
            pos.push_back(i-P.length()+2);
            j=f[j-1];
        }
    }//패턴 매칭의 횟수와 위치를 계산
    //ans는 횟수, pos는 위치
    return 0;
}