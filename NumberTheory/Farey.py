def nextTerm(n, a, b):
    # TODO : check correctness
  
    # next term of (a/b) in farey sequence
    # error if doesn't exists
    d = pow(a, phi(b) - 1, b)

    d *= b - 1
    d %= b

    d += b * ((n - d) // b)
    c = (a * d + 1) // b
    return [c, d]
def farey(n, K):
    # return K-th term of farey sequence
    # -1 if doesn't exist
    a, b = map(int, input().split())
    c, d = nextTerm(n, a, b)

    cnt = 0

    while c <= n:
        k = (n + b) // d
        a, b, c, d = c, d, k*c-a, k*d-b

        cnt += 1
        if cnt == K:
            print(f"{a} {b}")
            exit(0)
    print(-1)
