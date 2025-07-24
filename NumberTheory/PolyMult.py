def mult(X, Y, dtype): # dtype = 0: unsigned char, 1: unsigned short, 2: unsigned int, 3: unsigned long long
    size = 1<<dtype
    return list(memoryview(int.__mul__(*[int.from_bytes(bytes([z for x in P for z in [x]+[0]*(size-1)]), 'little') for P in (X, Y)]).to_bytes((len(X)+len(Y))*size, 'little')).cast(['B', 'H', 'I', 'Q'][dtype]))
