int reduce(vector<int>& b, int x){
    for(int i=K-1; i>=0; i--){
        if(x&(1<<i)){
            x=x^b[i];
        }
    }
    return x;
}

bool add(vector<int>& b, int x){
    int x=reduce(b, x);
    if(x!=0){
        for(int i=K-1; i>=0; i--){
            if(x&(1<<i)){
                b[i]=x;
                return true;
            }
        }
    }
    return false;
}