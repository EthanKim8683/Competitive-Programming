#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using S = string;
using Lli = long long int;

I main(void) {
#ifdef ETHANKIM8683
  freopen("infinite.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> q;
  while (q--) {
    S s;
    cin >> s;
    S t;
    cin >> t;
    if (t.find('a') == S::npos)
      printf("%lli\n", (Lli) 1 << s.size());
    else
      printf("%i\n", t.size() == 1 ? 1 : -1);
  }
  return 0;
}