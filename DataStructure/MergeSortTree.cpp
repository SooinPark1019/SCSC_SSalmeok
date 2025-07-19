int N;
vector<int> seg[400000];
int arr[400000];//원본 배열
void make_seg(int node, int start, int end){
    if(start==end) seg[node].push_back(arr[start]);
    else{
        int mid=((start+end)>>1);
        make_seg(node*2, start, mid);
        make_seg(node*2+1, mid+1, end);
        seg[node].resize(seg[node*2].size()+seg[node*2+1].size());
        merge(seg[node*2].begin(), seg[node*2].end(), seg[node*2+1].begin(), seg[node*2+1].end(), seg[node].begin());
        /*for(auto i : seg[node])
            cout << i << " ";
        cout << "\n";*/
    }
}
ll query(int node, int start, int end, int left, int right, ll K){
    if(right<start||end<left) return 0;
    else if(left<=start&&end<=right) return seg[node].end()-upper_bound(seg[node].begin(), seg[node].end(), K);
    else{
        int mid=((start+end)>>1);
        //cout << start << " " << mid << " " << query(node*2, start, mid, left, right, K) << "\n";
        //cout << mid+1 << " " << end << " " << query(node*2+1, mid+1, end, left, right, K) << "\n";
        return query(node*2, start, mid, left, right, K)+query(node*2+1, mid+1, end, left, right, K);
    }
}
/*
0-indexed
arr을 채워넣은 후 make_seg(1, 0, N-1)->머지소트트리 초기화
노트의 쿼리는 left부터 right까지의 수들 중 K보다 큰 것을 반환함
*/