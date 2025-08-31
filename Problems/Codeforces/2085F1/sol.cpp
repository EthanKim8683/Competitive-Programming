#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e, e--;

    vector<set<int>> indices(K);
    for (int i = 0; i < N; i++) {
      indices[A[i]].insert(i);
    }

    auto chmin = [&](int &a, int b) -> void { a = min(a, b); };
    int ans = INF;
    for (int i = 0; i + K <= N; i++) {
      vector<queue<int>> occs(K);
      for (int j = i; j < i + K; j++) {
        occs[A[j]].push(j);
      }
      int left = 0, cost = 0;
      for (int j = i; j < i + K; j++) {
        if (j != occs[A[j]].front()) {
          cost += i + K - j;
        }
      }
      vector<int> costs(K + 1, INF);
      for (int j = i; j <= i + K; j++) {
        chmin(costs[left], cost);
        if (j < i + K) {
          if (occs[A[j]].size() > 1) {
            occs[A[j]].pop();
            cost -= i + K - occs[A[j]].front();
            cost += j - (i - 1);
            left++;
          }
        }
      }

      vector<int> deltas;
      left = 0;
      cost = 0;
      for (int j = 0; j < K; j++) {
        if (occs[j].size() > 0) continue;
        auto it = indices[j].lower_bound(i);
        int l = it == indices[j].begin() ? -1 : *prev(it),
            r = it == indices[j].end() ? -1 : *it;
        if (r == -1) {
          cost += i - 1 - l;
          left++;
        } else if (l == -1) {
          cost += r - (i + K);
        } else {
          cost += r - (i + K);
          deltas.push_back({i - 1 - l - (r - (i + K))});
        }
      }
      sort(deltas.begin(), deltas.end());
      for (int j = 0; j <= deltas.size(); j++) {
        chmin(ans, cost + costs[left]);
        if (j < deltas.size()) {
          cost += deltas[j];
          left++;
        }
      }
    }
    cout << ans << '\n';
  }
}
