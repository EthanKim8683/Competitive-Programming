#include <iostream>
#include <cstdio>
#include <tuple>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MAX_LLI = 1e18;
const I MAX_I = 1e9;
const I MOD = 1e9 + 7;
const I N = 1e5;
const I M = 2e5;

Lli dsts[N];
Lli cnts[N];
I shts[N];
I lngs[N];
priority_queue<tuple<Lli, Lli, I, I, I>, vector<tuple<Lli, Lli, I, I, I>>, greater<tuple<Lli, Lli, I, I, I>>> que;
vector<pair<I, Lli>> adjs[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("investigation.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  fill_n(dsts, n, MAX_LLI);
  fill_n(cnts, n, 0);
  fill_n(shts, n, MAX_I);
  fill_n(lngs, n, 0);
  for (I i = 0; i < m; i++) {
    I a, b, c;
    cin >> a >> b >> c;
    adjs[a - 1].push_back({b - 1, c});
  }
  que.push({dsts[0] = 0, cnts[0] = 1, shts[0] = 0, lngs[0] = 0, 0});
  while (!que.empty()) {
    const auto [dst, cnt, sht, lng, a] = que.top();
    que.pop();
    if (dst == dsts[a] && cnt == cnts[a]) {
      for (const auto [b, c] : adjs[a]) {
        if (dst + c <= dsts[b]) {
          if (dst + c == dsts[b]) {
            cnts[b] = (cnts[b] + cnt) % MOD;
            shts[b] = min(shts[b], sht + 1);
            lngs[b] = max(lngs[b], lng + 1);
          } else {
            dsts[b] = dst + c;
            cnts[b] = cnt;
            shts[b] = sht + 1;
            lngs[b] = lng + 1;
          }
          que.push({dsts[b], cnts[b], shts[b], lngs[b], b});
        }
      }
    }
  }
  printf("%lli %lli %i %i\n", dsts[n - 1], cnts[n - 1], shts[n - 1], lngs[n - 1]);
  return 0;
}