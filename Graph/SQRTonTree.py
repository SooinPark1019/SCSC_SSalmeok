# 트리와 쿼리 1
# 1 i c : i번 간선 비용 c로 변경
# 2 u v : u-v경로에서 간선 비용 최댓값 출력


n, = Inp()
G = [[] for _ in range(n)]
E = [Inp() for _ in range(n-1)]
for a, b, c in E:
    G[a-1].append((b-1, c))
    G[b-1].append((a-1, c))
k = int(n**.5)

T = [[-1, 0] for _ in range(n)]
D = [0]*n
S = [{} for _ in range(n)]
def dfs(s):
    for e, c in G[s]:
        if e != 0 and T[e][0] == -1:
            D[e] = D[s]+1
            S[s][e] = c
            T[e] = [s, c]
            dfs(e)
dfs(0)


R = [0]*n
M = [0]*n
Q = deque([0])
while Q:
    r = Q.popleft()
    t = k
    M[r] = 0
    P = deque([r])
    while t and P:
        s = P.popleft()
        R[s] = r
        for e, c in S[s].items():
            P.append(e)
            M[e] = max(M[s], c)
        t -= 1
    for x in P:
        Q.append(x)


for _ in range(int(inp())):
    q = Inp()
    if q[0] == 1:
        i, c = q[1:]
        a, b = E[i-1][:2]
        a -= 1
        b -= 1
        if D[a] > D[b]:
            a, b = b, a
        T[b][1] = c
        S[a][b] = c
        if R[a] == R[b]:
            M[b] = max(M[a], c)
            P = deque([b])
            while P:
                s = P.popleft()
                for e, c in S[s].items():
                    if R[e] == R[s]:
                        P.append(e)
                        M[e] = max(M[s], c)
    else:
        a, b = q[1:]
        a -= 1
        b -= 1
        m = 0
        while R[a] != R[b]:
            if D[R[a]] < D[R[b]]:
                a, b = b, a
            if R[a] == a:
                m = max(m, T[a][1])
                a = T[a][0]
            else:
                m = max(m, M[a])
                a = R[a]
        while a != b:
            if D[a] < D[b]:
                a, b = b, a
            m = max(m, T[a][1])
            a = T[a][0]
        
        print(m)