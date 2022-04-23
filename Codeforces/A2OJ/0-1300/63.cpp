#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

using U = unsigned;
using C = char;
using B = bool;

C s[1001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("63.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  const U length = strlen(s);
  U l = 0;
  U r = length - 1;
  B turn = 0;
  while (l < r) {
    const C l_c = s[l];
    const C r_c = s[r];
    if (l_c == r_c) {
      l++;
      r--;
    } else {
      
      turn ^= 1;
    }
  }
  if (turn)
    printf("Second");
  else
    printf("First");
  return 0;
}