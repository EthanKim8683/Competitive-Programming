#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;
const i64 BASE = 6969;
const i64 MOD = (1ll << 31) - 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<i64> pows(2e5 + 1);
  pows[0] = 1;
  for (int i = 1; i <= 2e5; i++) {
    pows[i] = pows[i - 1] * BASE % MOD;
  }

  int T;
  cin >> T;

  while (T--) {
    string S;
    cin >> S;

    int N = S.size();

    set<int> diff;
    for (int i = 0; i < N; i++) {
      if (S[i] != 'a') {
        diff.insert(i);
      }
    }

    if (diff.empty()) {
      cout << N - 1 << '\n';
      continue;
    }

    vector<i64> ps(N + 1);
    ps[0] = 0;
    for (int i = 0; i < N; i++) {
      ps[i + 1] = (ps[i] * BASE + S[i]) % MOD;
    }
    auto query = [&](int l, int r) -> i64 {
      if (r > N) return -1;
      return ((ps[r] - ps[l] * pows[r - l]) % MOD + MOD) % MOD;
    };

    int i0 = *diff.begin();
    i64 ans = 0;
    for (int l = 1; l <= N - i0; l++) {
      int i = i0, p = 0, mp = INF;
      bool ok = true;
      while (true) {
        ok = ok and query(i, i + l) == query(i0, i0 + l);
        mp = min(mp, i - p);
        p = i + l;
        auto it = diff.lower_bound(i + l);
        if (it == diff.end()) break;
        i = *it;
      }
      if (ok) {
        ans += mp + 1;
      }
    }
    cout << ans << '\n';
  }
}
