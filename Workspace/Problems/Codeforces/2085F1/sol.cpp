#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vector<vector<int>> I(K);
    for (int i = 0; i < N; i++) {
      I[A[i]].push_back(i);
    }

    i64 ans = INF;
    for (int i = 0; i + K <= N; i++) {
      vector<i64> costs1;
      {
        vector<bool> seen(K, false);
        for (int j = i; j < i + K; j++) {
          seen[A[j]] = true;
        }

        i64 cost = 0;
        vector<int> deltas;
        for (int j = 0; j < K; j++) {
          if (seen[j]) continue;
          auto it1 = upper_bound(I[j].begin(), I[j].end(), i + K - 1),
               it2 = lower_bound(I[j].begin(), I[j].end(), i);
          int cost1 = it1 == I[j].end() ? INF : *it1 - (i + K - 1),
              cost2 = it2 == I[j].begin() ? INF : i - *prev(it2);
          cost += cost1;
          deltas.push_back(cost2 - cost1);
        }
        sort(deltas.begin(), deltas.end());

        for (auto e : deltas) {
          costs1.push_back(cost);
          cost += e;
        }
        costs1.push_back(cost);
      }

      vector<i64> costs2;
      {
        vector<vector<int>> I2(K);
        for (int j = i; j < i + K; j++) {
          I2[A[j]].push_back(j);
        }

        i64 cost = 0;
        vector<int> deltas;
        for (int j = 0; j < K; j++) {
          if (I2[j].empty()) continue;
          for (int k = 1; k < I2[j].size(); k++) {
            int cost1 = (i + K - 1) - I2[j][k], cost2 = I2[j][k - 1] - i;
            cost += cost1;
            deltas.push_back(cost2 - cost1);
          }
        }
        sort(deltas.begin(), deltas.end());

        for (auto e : deltas) {
          costs2.push_back(cost);
          cost += e;
        }
        costs2.push_back(cost);
      }

      assert(costs1.size() == costs2.size());
      for (int i = 0; i < costs1.size(); i++) {
        ans = min(ans, costs1[i] + costs2[i]);
      }
    }
    cout << ans << '\n';
  }
}
