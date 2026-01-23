#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> C(M);
  for (auto &e : C) cin >> e;

  vector<int> C_;
  for (auto e : C) {
    if (e == N) continue;
    C_.push_back(e);
  }
  sort(C_.rbegin(), C_.rend());

  auto check = [&](int x) -> bool {
    i64 w = 1;
    for (int i = 0; i < x - 1; i++) {
      w += N - C_[i] + 1;
    }
    return w <= C_.back();
  };
  int l = 1, r = C_.size();
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    check(m) ? l = m : r = m - 1;
  }
  cout << l;
}