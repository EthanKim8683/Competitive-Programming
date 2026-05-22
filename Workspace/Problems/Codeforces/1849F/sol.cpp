#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int a, int b) { return A[a] < A[b]; });

  vector<int> index(N);
  for (int i = 0; i < N; i++) {
    index[order[i]] = i;
  }

  vector<array<int, 4>> crit(N, {N, N, -1, -1});
  for (int i = 0; i < N; i++) {
    crit[i][0] = i;
    crit[i][2] = i;
  }
  priority_queue<tuple<int, int, int>> pq;
  auto in = [&](int i) -> bool { return i >= 0 and i < N; };
  auto push = [&](int i, int j) -> void {
    if (!in(i) or !in(j)) return;
    pq.push({-(A[order[i]] ^ A[order[j]]), i, j});
  };
  for (int i = 0; i + 1 < N; i++) {
    push(i, i + 1);
  }
  dsu_with_potentials<int> d(
      N, 0, [](int a, int b) { return a ^ b; }, [](int x) { return x; });
  while (pq.size() > 0) {
    auto [w, a, b] = pq.top();
    pq.pop();
    w = -w;
    if (d.same(a, b)) {
      if (d.voltage(a, b) == 0) break;
      continue;
    }
    auto crita = crit[d.leader(a)], critb = crit[d.leader(b)];
    d.merge(a, b, 1);
    auto &critc = crit[d.leader(a)];
    for (auto i : crita) {
      if (!in(i)) continue;
      int j = d.potential(i);
      critc[j + 0] = min(critc[j + 0], i);
      critc[j + 2] = max(critc[j + 2], i);
    }
    for (auto i : critb) {
      if (!in(i)) continue;
      int j = d.potential(i);
      critc[j + 0] = min(critc[j + 0], i);
      critc[j + 2] = max(critc[j + 2], i);
    }
    int l = min(critc[0], critc[1]), r = max(critc[2], critc[3]);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (in(l - 1)) {
          auto &critd = crit[d.leader(l - 1)];
          push(critd[i + 2], critc[j + 0]);
        }
        if (in(r + 1)) {
          auto &critd = crit[d.leader(r + 1)];
          push(critc[i + 2], critd[j + 0]);
        }
      }
    }
  }
  for (auto i : index) {
    cout << d.potential(i);
  }
}
