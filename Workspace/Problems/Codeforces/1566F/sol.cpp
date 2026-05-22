#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<int> A(N);
    for (auto &e : A) cin >> e;
    sort(A.begin(), A.end());

    // Not hard, just annoying to implement

    vector<pair<int, int>> segs(M);
    for (auto &[l, r] : segs) {
      cin >> l >> r;
      r = -r;
    }
    sort(segs.begin(), segs.end());

    vector<pair<int, int>> segs2;
    int rmax = -2e9;
    for (auto [l, r] : segs) {
      r = -r;
      if (r > rmax and lower_bound(A.begin(), A.end(), l) ==
                           upper_bound(A.begin(), A.end(), r)) {
        segs2.push_back({l, r});
        rmax = r;
      }
    }
  }
}
