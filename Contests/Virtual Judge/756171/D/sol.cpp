#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<pair<int, int>> ranges(N);
  for (auto &[L, R] : ranges) {
    cin >> L >> R;
    R++;
  }

  // if R - L >= K, then we can always get it
  //
  // else S is in a certain range

  vector<pair<int, int>> ranges_;
  int base = 0;
  for (auto [L, R] : ranges) {
    if (R - L >= K) {
      base++;
    } else {
      int l = L % K, r = R % K;
      if (r < l) {
        ranges_.push_back({l, K});
        ranges_.push_back({0, r});
      } else {
        ranges_.push_back({l, r});
      }
    }
  }

  vector<int> compress;
  for (auto [l, r] : ranges_) {
    compress.push_back(l);
    compress.push_back(r);
  }
  sort(compress.begin(), compress.end());
  compress.erase(unique(compress.begin(), compress.end()), compress.end());

  for (auto &[l, r] : ranges_) {
    l = lower_bound(compress.begin(), compress.end(), l) - compress.begin();
    r = lower_bound(compress.begin(), compress.end(), r) - compress.begin();
  }

  vector<int> ps(compress.size());
  for (auto [l, r] : ranges_) {
    ps[l]++;
    ps[r]--;
  }
  int ans = base;
  for (int i = 0; i + 1 < compress.size(); i++) {
    ps[i + 1] += ps[i];
    ans = max(ans, base + ps[i]);
  }
  cout << ans;
}