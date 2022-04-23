#include <iostream>
#include <cstdio>
#include <unordered_set>

using namespace std;

using U = unsigned;
using C = char;

C s[101];
unordered_set<C> chars;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("23.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  U i = 0;
  while (true) {
    const auto c = s[i];
    if (!c)
      break;
    i++;
    chars.insert(c);
  }
  if (chars.size() & 1)
    printf("IGNORE HIM!\n");
  else
    printf("CHAT WITH HER!\n");
  return 0;
}