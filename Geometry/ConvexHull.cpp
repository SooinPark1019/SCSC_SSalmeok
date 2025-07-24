struct point{
    long long x,y;
};
long long ccw(point A, point B, point C){
    long long temp=A.x*B.y+B.x*C.y+C.x*A.y-A.y*B.x-B.y*C.x-C.y*A.x;
    return temp;
}
point S[100005];
int stackpointer=0;
vector<point> V;
bool compare1(point A, point B){
    if(A.y==B.y) return A.x<B.x;
    return A.y<B.y;
}
bool compare2(point A, point B){
    long long a=ccw(V[0], A, B);
    if(a==0){
        return (A.x-V[0].x)*(A.x-V[0].x)+(A.y-V[0].y)*(A.y-V[0].y)<(B.x-V[0].x)*(B.x-V[0].x)+(B.y-V[0].y)*(B.y-V[0].y);
    }
    return a>0;
}
int main(){
    int N;
    for(long long i=0, a, b; i<N; i++) { cin >> a >> b; V.push_back({a, b}); }
    sort(V.begin(), V.end(), compare1); sort(V.begin()+1, V.end(), compare2);
    S[stackpointer]=V[0];
    stackpointer++;
    S[stackpointer]=V[1];
    stackpointer++;
    for(int i=2; i<N; i++){
        while((stackpointer>=2)&&(ccw(S[stackpointer-2], S[stackpointer-1], V[i])<=0)){
            stackpointer--;
        }
        S[stackpointer]=V[i];
        stackpointer++;
    }
    return 0;
}