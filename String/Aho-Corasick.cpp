struct Trie{
    Trie *go[30];
    Trie *fail;
    bool output;
    Trie(){
        fill(go, go+30, nullptr);
        output=false;
    }
    ~Trie(){
        for(int i=0; i<26; i++)
            if(go[i]) delete go[i];
    }
    void insert(const string& S, int a){
        if(a==S.length()) output=true;
        else{
            int nxt=S[a]-'a';
            if(!go[nxt]) go[nxt]=new Trie;
            go[nxt]->insert(S, a+1);
        }
    }
};//트라이 구조체
int main() {
    int N;
    cin >> N;
    Trie* root=new Trie;
    root->fail=root;
    for(int i=0; i<N; i++){
        string S;
        cin >> S;
        root->insert(S, 0);
    }//트라이에 문자열 삽입
    queue<Trie*> Q;
    Q.push(root);
    while(!Q.empty()){
        Trie* cur=Q.front();
        Q.pop();
        for(int i=0; i<26; i++){
            if(!cur->go[i]) continue;
            Trie* nxt=cur->go[i];
            if(cur==root) nxt->fail=root;
            else{
                Trie* x=cur->fail;
                while(x!=root&&!x->go[i]) x=x->fail;
                if(x->go[i]) x=x->go[i];
                nxt->fail=x;
            }
            if(nxt->fail->output) nxt->output=true;
            Q.push(nxt);
        }
    }//실패함수 연결, output 함수 갱신
    int M;
    cin >> M;
    for(int i=0; i<M; i++){
        string S;
        cin >> S;
        Trie* cur=root;
        int ans=0;
        for(auto c : S){
            int nxt=c-'a';
            while(cur!=root&&!cur->go[nxt]) cur=cur->fail;
            if(cur->go[nxt]) cur=cur->go[nxt];
            if(cur->output){
                ans=1;
                break;
            }
        }
        if(ans==1) cout << "YES\n";
        else cout << "NO\n";
    }//패턴 찾기
    delete root;
    return 0;
}