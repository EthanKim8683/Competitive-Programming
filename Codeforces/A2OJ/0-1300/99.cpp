#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using U = unsigned;
using B = bool;

pair<U, U> bottles[100];
vector<U> brands[1000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("99.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  for (U i = n; i--;) {
    auto& [a, b] = bottles[i];
    cin >> a >> b;
    a--;
    b--;
    brands[b].push_back(i);
  }
  U result = 0;
  while (n--) {
    const auto [a, b] = bottles[n];
    B closed = true;
    for (const auto i : brands[a]) {
      if (i != n) {
        closed = false;
        break;
      }
    }
    result += closed;
  }
  printf("%u\n", result);
  return 0;
}