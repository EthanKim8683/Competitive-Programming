#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using C = char;

C s[200001];
I hists[100000][26];
I totals[100000];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1332c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, k;
    cin >> n >> k;
    cin >> s;
    const I h = 1 + (k - 1) / 2;
    fill_n(totals, h, 0);
    for (I i = h; i--;)
      fill_n(hists[i], 26, 0);
    for (I i = 0; i < n; i += k) {
      for (I j = k; j--;) {
        const I l = min(j, k - j - 1);
        hists[l][s[i + j] - 'a']++;
        totals[l]++;
      }
    }
    I result = 0;
    for (I i = h; i--;) {
      const auto& hist = hists[i];
      I d = 0;
      for (I j = 26; j--;)
        d = max(d, hist[j]);
      result += totals[i] - d;
    }
    printf("%i\n", result);
  }
  return 0;
}