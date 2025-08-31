#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;
const i64 BASE = 6969;
const i64 MOD = (1ll << 31) - 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  auto cc = A;
  sort(cc.begin(), cc.end());
  cc.erase(unique(cc.begin(), cc.end()), cc.end());
  for (auto &e : A) {
    e = lower_bound(cc.begin(), cc.end(), e) - cc.begin();
  }

  vector<i64> pows(cc.size());
  pows[0] = 1;
  for (int i = 1; i < cc.size(); i++) {
    pows[i] = pows[i - 1] * BASE % MOD;
  }

  vector<vector<pair<int, i64>>> segs(2 * N);
  vector<int> parity(cc.size(), 1);
  for (int i = 0; i < N; i++) {
    segs[i + N].push_back({A[i], (pows[A[i]] * parity[A[i]] + MOD) % MOD});
    parity[A[i]] *= -1;
  }
  for (int i = N - 1; i >= 1; i--) {
    merge(segs[i << 1].begin(), segs[i << 1].end(), segs[i << 1 | 1].begin(),
          segs[i << 1 | 1].end(), back_inserter(segs[i]));
  }
  for (int i = 1; i < 2 * N; i++) {
    i64 ps = 0;
    for (auto &e : segs[i]) {
      i64 &hash = e.second;
      swap(ps, hash);
      ps += hash;
    }
    segs[i].push_back({INF, ps});
  }
  auto query = [&](int l, int r, int x) -> i64 {
    i64 rv = 0;
    auto use = [&](int i) -> void {
      (rv += lower_bound(segs[i].begin(), segs[i].end(), make_pair(x + 1, -1))
                 ->second) %= MOD;
    };
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        use(l);
        l++;
      }
      if (r & 1) {
        r--;
        use(r);
      }
    }
    return rv;
  };

  int Q;
  cin >> Q;

  int ans = 0;
  while (Q--) {
    int a, b;
    cin >> a >> b;
    int l = a ^ ans, r = b ^ ans;
    l--;

    int s = 0, t = cc.size();
    while (s < t) {
      int m = s + (t - s) / 2;
      query(l, r, m) != 0 ? t = m : s = m + 1;
    }
    ans = s < cc.size() ? cc[s] : 0;

    cout << ans << '\n';
  }
}
