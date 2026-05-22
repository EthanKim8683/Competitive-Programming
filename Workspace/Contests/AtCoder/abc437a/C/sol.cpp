#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<pair<int, int>> reindeer(N);
    for (auto &[W, P] : reindeer) {
      cin >> W >> P;
    }

    i64 total = 0;
    vector<int> cost;
    for (auto [W, P] : reindeer) {
      total += P;
      cost.push_back({-W - P});
    }
    sort(cost.rbegin(), cost.rend());
    int ans = 0;
    for (auto e : cost) {
      if (total + e < 0) break;
      total += e;
      ans++;
    }
    cout << ans << '\n';
  }
}
