#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    auto ceil_div = [&](int x, int y) -> int { return (x + y - 1) / y; };

    priority_queue<pair<int, int>> pq;
    vector<int> B(N, 0);
    for (int i = 0; i < N; i++) {
      pq.push({B[i], i});
    }
    vector ans(K, vector<vector<int>>(M));
    for (int i = 0; i < K; i++) {
      for (int j = 0; j < M; j++) {
        for (int k = 0; k < (j < N % M ? ceil_div(N, M) : N / M); k++) {
          auto [b, a] = pq.top();
          pq.pop();
          ans[i][j].push_back(a);
        }
      }
      for (int j = 0; j < M; j++) {
        if (ans[i][j].size() == ceil_div(N, M)) {
          for (auto e : ans[i][j]) {
            B[e]++;
          }
        }
        for (auto e : ans[i][j]) {
          pq.push({-B[e], e});
        }
      }
      assert(*max_element(B.begin(), B.end()) -
                 *min_element(B.begin(), B.end()) <=
             1);
    }

    for (auto g : ans) {
      for (auto r : g) {
        cout << r.size() << ' ';
        for (auto e : r) {
          cout << e + 1 << ' ';
        }
        cout << '\n';
      }
    }
    cout << '\n';
  }
}
