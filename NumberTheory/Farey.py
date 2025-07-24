def nextTerm(n, a, b):
    # next term of (a/b) in farey sequence F_n
    d = pow(a, phi(b) - 1, b)
    d *= b - 1
    d %= b

    d += b * ((n - d) // b)
    c = (a * d + 1) // b
    return [c, d]
def farey(n, K):
    # return K-th term of farey sequence
    # -1 if doesn't exist
    a, b, c, d = 0, 1, 1, n

    cnt = 0
    if K == 1: return (a, b)
    while c <= n:
        k = (n + b) // d
        a, b, c, d = c, d, k*c-a, k*d-b

        cnt += 1
        if cnt == K:
            return (a, b)
    return -1
