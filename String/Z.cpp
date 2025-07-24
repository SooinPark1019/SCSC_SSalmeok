int main() {
    string S;
    cin >> S;
    int N=S.length();
    vector<int> Z;
    Z.push_back(S.length());
    int L=0, R=0;
    for(int i=1; i<S.length(); i++){
        if(i>R){
            L=i;
            R=i;
            while(R<N&&S[R]==S[R-L]) R++;
            Z.push_back(R-L);
            R--;
        }
        else{
            if(Z[i-L]<=R-i){
                Z.push_back(Z[i-L]);
            }
            else{
                L=i;
                while(R<N&&S[R]==S[R-L]) R++;
                Z.push_back(R-L);
                R--;
            }
        }
    }
    return 0;
}