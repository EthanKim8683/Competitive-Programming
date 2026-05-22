#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<i64> D(N);
    for (auto &e : D) cin >> e;

    vector<int> L(M);
    for (auto &e : L) cin >> e;

    vector<i64> T(Q);
    for (auto &e : T) cin >> e;

    map<i64, pair<i64, i64>> by_deadline;
    for (int i = 0; i < N; i++) {
      if (!by_deadline.contains(D[i])) {
        by_deadline[D[i]] = {D[i], 0};
      }
      by_deadline[D[i]].second += A[i];
    }

    i64 latest = INF;
    for (auto it = by_deadline.rbegin(); it != by_deadline.rend(); it++) {
      auto &[deadline, size] = it->second;
      latest = min(latest, deadline) - size;
      deadline = latest;
    }
    by_deadline[INF] = {INF, 0};

    vector<int> order(Q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(),
         [&](int a, int b) -> bool { return T[a] < T[b]; });

    map<i64, i64> prefix;
    i64 sum = 0;
    for (auto [deadline, value] : by_deadline) {
      auto [latest, size] = value;
      prefix[deadline] = sum;
      sum += size;
    }

    vector<i64> ps(M + 1, 0);
    for (int i = 0; i < M; i++) {
      ps[i + 1] = ps[i] + L[i];
    }

    vector<int> ans(Q);
    for (auto i : order) {
      auto it1 = by_deadline.lower_bound(T[i]);
      auto it2 = prefix.lower_bound(T[i]);
      i64 space = min(it1->second.first, T[i]) - it2->second;
      ans[i] = upper_bound(ps.begin(), ps.end(), space) - ps.begin() - 1;
    }

    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}