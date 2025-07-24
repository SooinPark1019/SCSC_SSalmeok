int main() {
    string S="@";
    char c;
    while(cin >> c){
        S+=c;
        S+="@";
    }//문자열 사이에 특수문자 삽입
    int p=-1;
    int r=-1;
    int res[250005]={};
    int ans=0;
    for(int i=0; i<S.length(); i++){
        if(i>r){
            r=i;
            p=i;
            while(r<S.length()&&r<=2*p&&S[r]==S[2*p-r]) r++;
            r--;
            res[i]=r-p;
        }
        else{
            int j=2*p-i;
            if(res[j]<r-i){
                res[i]=res[j];
            }
            else if(res[j]>r-i){
                res[i]=r-i;
            }
            else{
                p=i;
                while(r<S.length()&&r<=2*p&&S[r]==S[2*p-r]) r++;
                r--;
                res[i]=r-p;
            }
        }
    }//res 배열은 위치 i를 중심으로 하는 팰린드롬의 길이를 담음. 이때 대상이 되는 문자열은 사이에 특수문자를 삽입했음에 주의.
    return 0;
}