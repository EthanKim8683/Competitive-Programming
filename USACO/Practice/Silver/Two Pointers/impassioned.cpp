#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using C = char;
using S = string;

vector<pair<I, I>> segs[26];

I tod(C chr) {
  return chr - 'a';
}

I len(pair<I, I> rng) {
  return rng.second - rng.first + 1;
}

I dis(pair<I, I> lft, pair<I, I> rgt) {
  return rgt.first - lft.second - 1;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  S s;
  cin >> s;
  I ind = 0;
  while (ind < n) {
    const I beg = ind++;
    while (ind < n && s[ind] == s[beg])
      ind++;
    segs[tod(s[beg])].push_back({beg, ind - 1});
  }
  I q;
  cin >> q;
  while (q--) {
    I m;
    C c;
    cin >> m >> c;
    const I dgt = tod(c);
    I res = m;
    if (!segs[dgt].empty()) {
      const I siz = segs[dgt].size();
      I l = 0;
      I r = 0;
      I tot = len(segs[dgt][l]);
      I fil = 0;
      res = max(res, tot + m);
      while (l < r || r < siz - 1) {
        if (r == siz - 1) {
          tot -= len(segs[dgt][l]);
          fil -= dis(segs[dgt][l], segs[dgt][l + 1]);
          l++;
        } else if (l == r) {
          tot += len(segs[dgt][r + 1]);
          fil += dis(segs[dgt][r], segs[dgt][r + 1]);
          r++;
        } else if (fil > m) {
          tot -= len(segs[dgt][l]);
          fil -= dis(segs[dgt][l], segs[dgt][l + 1]);
          l++;
        } else if (fil <= m) {
          tot += len(segs[dgt][r + 1]);
          fil += dis(segs[dgt][r], segs[dgt][r + 1]);
          r++;
        }
        if (fil <= m)
          res = max(res, tot + m);
      }
    }
    printf("%i\n", min(n, res));
  }
  return 0;
}