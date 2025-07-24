vector<int> manacher(string& A) {
    int n = A.size();
    vector<int> B(2*n-1);
    for(int i=0; i<n; i++) B[2*i] = A[i];

    vector<int> P(2*n-1, 1);
    int p = 0;
    for(int i=1; i<2*n-1; i++) {
        if(2*p-i >= 0 && i <= p+P[p]-1) P[i] = min(P[2*p-i], p+P[p]-i);
        while(i-P[i] >= 0 && i+P[i] < 2*n-1 && B[i-P[i]] == B[i+P[i]]) P[i]++;
        if(i+P[i] > p+P[p]) p = i;
    }
    return P;
}