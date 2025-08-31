#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> B(N);
  for (auto &e : B) cin >> e;

  vector<int> C(N);
  for (auto &e : C) cin >> e;

  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) { return C[i] > C[j]; });

  // lazy
}
