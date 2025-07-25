vector<pii> graph[1005];
vector<int> check;
int id=0;

void sol(int cur_node){
    while(!graph[cur_node].empty()){
        if(check[graph[cur_node].back().second]!=0) graph[cur_node].pop_back();
        else{
            check[graph[cur_node].back().second]=1;
            sol(graph[cur_node].back().first);
        }
    }
    cout << cur_node << " ";
}

//홀수 차수 정점 두 개가 존재하는 그래프에서 경로를 찾으려면 
//두 정점을 잇고 이은 간선부터 시작해서 회로를 찾은 후에, 
//다시 그 간선을 빼주면 된다    