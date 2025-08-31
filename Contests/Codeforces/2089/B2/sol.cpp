#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    i64 K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<int> B(N);
    for (auto &e : B) cin >> e;

    set<int> S, T;
    for (int i = 0; i < N; i++) {
      S.insert(i);
      T.insert(i);
    }

    priority_queue<pair<int, int>> pq;
    auto before = [&](auto &S, int i) -> int {
      auto it = S.upper_bound(i);
      if (it == S.begin()) {
        it = S.end();
      }
      return *prev(it);
    };
    auto after = [&](auto &S, int i) -> int {
      auto it = S.lower_bound(i);
      if (it == S.end()) {
        it = S.begin();
      }
      return *it;
    };
    vector<int> dist(N, INF);
    auto nudge = [&](int i) -> void {
      if (!S.contains(i)) return;
      int j = after(T, i), k = after(S, i + 1), di = (j - i + N) % N,
          dk = (j - k + N) % N;
      if (di <= dk and di < dist[i]) {
        dist[i] = di;
        pq.push({-di, i});
      }
    };
    for (int i = 0; i < N; i++) {
      nudge(i);
    }
    vector<i64> cost(N + 1, 0);
    while (pq.size() > 0) {
      auto [t, i] = pq.top();
      pq.pop();
      t = -t;
      int j = after(T, i), s = min(A[i], B[j]);
      cost[t] += A[i];
      if ((A[i] -= s) == 0) {
        S.erase(i);
      }
      if ((B[j] -= s) == 0) {
        T.erase(j);
      }
      cost[t] -= A[i];
      dist[i] = INF;
      nudge(i);
      if (S.empty()) break;
      nudge(before(S, i));
    }
    for (int i = N; i - 1 >= 0; i--) {
      cost[i - 1] += cost[i];
    }
    int ans = INF;
    for (int i = 0; i <= N; i++) {
      if (cost[i] <= K) {
        ans = min(ans, i);
      }
    }
    cout << ans << '\n';
  }
}
