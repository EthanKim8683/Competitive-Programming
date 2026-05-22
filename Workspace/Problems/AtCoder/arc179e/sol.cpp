#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

struct rect {
  int h, w;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<rect> rects(N);
  for (auto &[h, w] : rects) {
    cin >> h >> w;
  }

  vector<i64> ps(N + 1);
  ps[0] = 0;
  for (int i = 0; i < N; i++) {
    auto [h, w] = rects[i];
    ps[i + 1] = ps[i] + (i64) h * w;
  }

  dsu dw(N), dh(N);
  for (int i = 0; i + 1 < N; i++) {
    if (rects[i].w == rects[i + 1].w) dw.merge(i, i + 1);
    if (rects[i].h == rects[i + 1].h) dh.merge(i, i + 1);
  }

  vector<int> R(N), T(N);
  for (int i = 0; i < N; i++) {
    R[dh.leader(i)] = i;
    T[dw.leader(i)] = i;
  }

  vector<map<i64, int>> using_w(N), using_h(N);
  vector<int> ends(N);
  for (int i = 0; i < N; i++) {
    int l = -1, r = R[dh.leader(i)];
    if (i - 1 >= 0 and rects[i - 1].h < rects[i].h) {
      i64 A = (i64) rects[i - 1].w * (rects[i].h - rects[i - 1].h);
      if (using_w[dw.leader(i - 1)].contains(ps[i - 1] - A)) {
        l = using_w[dw.leader(i - 1)][ps[i - 1] - A];
      }
    }

    int b = -1, t = T[dw.leader(i)];
    if (i - 1 >= 0 and rects[i - 1].w < rects[i].w) {
      i64 A = (i64) rects[i - 1].h * (rects[i].w - rects[i - 1].w);
      if (using_h[dh.leader(i - 1)].contains(ps[i - 1] - A)) {
        b = using_h[dh.leader(i - 1)][ps[i - 1] - A];
      }
    }

    ends[i] = max(ends[i], max(r, t));
    if (l == b) {
      if (l != -1) ends[l] = max(ends[l], max(r, t));
    } else {
      if (l != -1) ends[l] = max(ends[l], r);
      if (b != -1) ends[b] = max(ends[b], t);
    }

    using_w[dw.leader(i)].insert({ps[i], i});
    if (b != -1) using_w[dw.leader(i)].insert({ps[b], b});
    using_h[dh.leader(i)].insert({ps[i], i});
    if (l != -1) using_h[dh.leader(i)].insert({ps[l], l});
  }

  i64 ans = 0;
  for (int i = 0; i < N; i++) {
    ans += ends[i] - i + 1;
  }
  cout << ans;
}
