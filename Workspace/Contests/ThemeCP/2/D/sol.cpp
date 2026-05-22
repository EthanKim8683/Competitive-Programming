#include <bits/stdc++.h>

#include "ethankim8683/algebra.hpp"

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> B(M);
  for (auto &e : B) cin >> e;

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  auto check = [&](int x) -> bool {

  };

  int l = 0, r = 1e9;
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    check(m) ? l = m : r = m - 1;
  }
  cout << l << '\n';
}
/*
Binary search for when Alice can be forced to forfeit
*/
