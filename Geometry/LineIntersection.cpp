ll ccw(const PT &p1, const PT &p2, const PT &p3){
    ll op = (p2-p1)^(p3-p1);
    return (op>0)-(op<0);
}
bool isIntersect(PT A, PT B, PT C, PT D){
  // check segment AB and segment CD intersects

    ll ab = ccw(A, B, C) * ccw(A, B, D);
    ll cd = ccw(C, D, A) * ccw(C, D, B);
    if (ab == 0 && cd == 0){
	if (A > B) swap(A, B);
	if (C > D) swap(C, D);
	return C <= B && A <= D;
    }
    return ab <= 0 && cd <= 0;
}
