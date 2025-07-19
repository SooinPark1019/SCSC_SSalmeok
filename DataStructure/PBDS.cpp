#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>//이걸 코드의 윗 부분에 추가
//ordered_set OS;->이런 식으로 사용가능
//insert와 erase는 통상적인 set와 동일
//OS.order_of_key(i)->i보다 작은 원소의 개수를 반환
//OS.find_by_order(i)->i-1번째 원소를 반환(0-based 배열과 동일)

///아래는 멀티셋일 경우의 특이사항
using namespace __gnu_pbds;
using namespace __gnu_cxx;
#define ordered_set tree<ll, null_type, less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update>//이걸 코드의 윗부분에 추가
void m_erase(ordered_set &OS, ll val){
    ll index = OS.order_of_key(val);
    ordered_set::iterator it = OS.find_by_order(index);
    if(*it == val) OS.erase(it);
}
//다른 건 통상적인 PBDS처럼 사용하면 되지만 erase는 반드시!!! 이 함수를 통해서만 해야 함
//m_erase(OS, 지울 원소)처럼 사용하면 된다. 꼭 주의하자.