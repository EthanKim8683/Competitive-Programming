#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[1001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("8.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  auto& c = s[0];
  if (c >= 'a' && c <= 'z')
    c += 'A' - 'a';
  printf("%s\n", s);
  return 0;
}