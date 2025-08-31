#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> counts(M, 0);
  vector<i64> before(M, 0), after(M, 0);
  for (int i = 0; i < N; i++) {
    before[A[i]] += i - counts[A[i]];
    counts[A[i]]++;
  }
  fill(counts.begin(), counts.end(), 0);
  for (int i = N - 1; i >= 0; i--) {
    after[A[i]] += N - 1 - i - counts[A[i]];
    counts[A[i]]++;
  }

  i64 ans = 0;
  fenwick_tree<int> ft(M);
  for (auto e : A) {
    ans += ft.sum(e + 1, M);
    ft.add(e, 1);
  }
  cout << ans << '\n';
  for (int i = 0; i < M - 1; i++) {
    ans += before[M - 1 - i] - after[M - 1 - i];
    cout << ans << '\n';
  }
}
