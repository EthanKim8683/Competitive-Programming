#include <bits/stdc++.h>

#include "ethankim8683/geometry.hpp"
#include "ethankim8683/int.hpp"

using namespace std;

using i128 = __int128;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<complex<i128>> vecs;
  for (int i = 0; i < N; i++) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a != b or c != d) {
      vecs.push_back({a - b, c - d});
    }
  }
  sort(vecs.begin(), vecs.end(), radial_cmp<i128>);

  // It's not hard, I just can't do math today...

  complex<i128> total = 0;
  for (auto e : vecs) {
    total += e;
  }

  i128 ans = 0;
  complex<i128> sum;
  for (int l = 0, r = 0; l < vecs.size(); l++) {
    auto good = [&](auto x) -> bool {
      if (i128 rv = cross(vecs[l], x)) return rv > 0;
      return dot(vecs[l], x) > 0;
    };
    while (r - l < vecs.size() and good(vecs[r % vecs.size()])) {
      sum += vecs[r % vecs.size()];
      r++;
    }
    ans = max(ans, dot(sum, sum));
    ans = max(ans, dot(total - sum, total - sum));
    sum -= vecs[l];
  }
  sum = {0, 0};
  for (int l = 0, r = 0; l < vecs.size(); l++) {
    auto good = [&](auto x) -> bool {
      if (i128 rv = cross(vecs[l], x)) return rv < 0;
      return dot(vecs[l], x) > 0;
    };
    while (r - l < vecs.size() and good(vecs[r % vecs.size()])) {
      sum += vecs[r % vecs.size()];
      r++;
    }
    ans = max(ans, dot(sum, sum));
    ans = max(ans, dot(total - sum, total - sum));
    sum -= vecs[l];
  }
  cout << ans;
}
