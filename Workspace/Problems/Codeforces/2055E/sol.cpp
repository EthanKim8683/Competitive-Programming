#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<pair<int, int>> hbs(N);
    for (auto &[a, b] : hbs) {
      cin >> a >> b;
    }

    vector<pair<int, int>> inc, dec;
    for (auto [a, b] : hbs) {
      if (b > a) {
        inc.push_back({a, b});
      } else {
        dec.push_back({a, b});
      }
    }
    sort(inc.begin(), inc.end(),
         [&](auto a, auto b) { return a.first < b.first; });
    sort(dec.begin(), dec.end(),
         [&](auto a, auto b) { return a.second > b.second; });

    vector<pair<int, int>> ideal;
    ideal.insert(ideal.end(), inc.begin(), inc.end());
    ideal.insert(ideal.end(), dec.begin(), dec.end());

    vector<i64> ps(N), min_ps(N);
    i64 cur_ps = 0, cur_min_ps = 0;
    for (int i = 0; i < N; i++) {
      ps[i] = cur_ps;
      min_ps[i] = cur_min_ps;

      auto [a, b] = ideal[i];
      cur_min_ps = min(cur_min_ps, cur_ps - a);
      cur_ps += -a + b;
    }

    i64 min_after = 0, ans = INF;
    for (int i = N - 1; i >= 0; i--) {
      auto [a, b] = ideal[i];
      if (cur_ps - b >= 0) {
        ans = min(ans, -min(min_ps[i], ps[i] + min_after));
      }
      min_after = min(-a + b + min_after, (i64) -a);
    }

    if (ans == INF) {
      cout << -1 << '\n';
      continue;
    }

    for (auto [a, b] : hbs) {
      ans += a;
    }
    cout << ans << '\n';
  }
}
