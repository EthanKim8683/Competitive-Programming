#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector A(2, vector<int>(N));
  for (auto &r : A) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vector counts(2, vector<int>(M, 0));
  vector<set<int>> S(2);
  for (int i = 0; i < 2; i++) {
    for (auto e : A[i]) {
      counts[i][e]++;
      S[i].insert(e);
    }
  }
  priority_queue<tuple<int, int, int, int>> pq;
  auto nudge = [&](int t, int a) -> void {
    if (S[1 - t].empty()) return;

    auto it = S[1 - t].upper_bound(M - 1 - a);
    int b;
    if (it == S[1 - t].begin()) {
      b = *S[1 - t].rbegin();
    } else {
      b = *prev(it);
    }
    if (t) {
      swap(a, b);
    }
    pq.push({(a + b) % M, a, b, t});
  };
  for (int i = 0; i < 2; i++) {
    for (auto a : S[i]) {
      nudge(i, a);
    }
  }
  while (pq.size() > 0) {
    auto [d, a, b, t] = pq.top();
    pq.pop();

    int count = min(counts[0][a], counts[1][b]);
    for (int i = 0; i < count; i++) {
      cout << d << ' ';
    }

    if ((counts[0][a] -= count) == 0) {
      S[0].erase(a);
    }
    if ((counts[1][b] -= count) == 0) {
      S[1].erase(b);
    }

    if (t == 0 and counts[0][a] > 0) {
      nudge(0, a);
    }
    if (t == 1 and counts[1][b] > 0) {
      nudge(1, b);
    }
  }
}
