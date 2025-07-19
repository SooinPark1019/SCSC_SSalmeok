#include <ext/rope> // GNU C++ 확장 헤더

using namespace __gnu_cxx; // rope가 속한 namespace

///insert(pos, str): 특정 위치에 문자열 삽입
///erase(pos, len): 특정 위치에서 len만큼 삭제
///substr(pos, len): 부분 문자열 반환
///operator+: 로프 합치기
///at(pos): 특정 위치의 문자 접근