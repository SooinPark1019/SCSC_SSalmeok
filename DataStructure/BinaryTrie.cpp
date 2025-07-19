#include <bits/stdc++.h>
using namespace std;
/// @brief 수열과 쿼리 20
/// 1번 쿼리가 주어지면 수를 추가
/// 2번 쿼리가 주어지면 수를 제거
/// 3번 쿼리가 주어지면 현재 있는 수들 중 쿼러로 주어진 수와 XOR 했을 때의 최댓값이 얼마인지 구함
struct Node{
    int l, r; //child : 0 1
    int cnt, ter;
    Node() : l(-1), r(-1), cnt(0), ter(-1) {}
};

Node node[6060606];
queue<int> q; //node pool

int newNode(){
    int ret = q.front(); q.pop();
    return ret;
}

int root;
int arr[30];

void insert(int x){
    int now = root, v = x;
    for(int i=29; i>=0; i--){
        arr[i] = x & 1; x >>= 1;
    }
    for(int i=0; i<30; i++){
        if(!arr[i]){
            if(node[now].l == -1) node[now].l = newNode();
            now = node[now].l;
            node[now].cnt++; if(i == 29) node[now].ter = v;
        }else{
            if(node[now].r == -1) node[now].r = newNode();
            now = node[now].r;
            node[now].cnt++; if(i == 29) node[now].ter = v;
        }
    }
}

void erase(int x){
    int now = root, v = x;
    for(int i=29; i>=0; i--){
        arr[i] = x & 1; x >>= 1;
    }
    for(int i=0; i<30; i++){
        if(!arr[i]){
            int nxt = node[now].l;
            if(--node[nxt].cnt == 0){
                node[now].l = -1; node[nxt].ter = -1; q.push(nxt);
            }
            now = nxt;
        }else{
            int nxt = node[now].r;
            if(--node[nxt].cnt == 0){
                node[now].r = -1; node[nxt].ter = -1; q.push(nxt);
            }
            now = nxt;
        }
    }
}

int query(int x){
    int now = root, v = x;
    for(int i=29; i>=0; i--){
        arr[i] = x & 1; x >>= 1;
    }
    for(int i=0; i<=30; i++){
        if(node[now].ter != -1) return v ^ node[now].ter;
        if(arr[i]){
            if(node[now].l != -1) now = node[now].l;
            else now = node[now].r;
        }else{
            if(node[now].r != -1) now = node[now].r;
            else now = node[now].l;
        }
        if(node[now].ter != -1) return v ^ node[now].ter;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    for(int i=1; i<6060606; i++) q.push(i);
    root = newNode();
    insert(0);
    int q; cin >> q;
    while(q--){
        int op, x; cin >> op >> x;
        if(op == 1){
            insert(x);
        }else if(op == 2){
            erase(x);
        }else{
            cout << query(x) << "\n";
        }
    }
}