#include <bits/stdc++.h>

#include "atcoder/modint"

using namespace std;
using namespace atcoder;
using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) {
    cin >> e;
    e--;
  }

  vector<bool> left(N), right(N);
  bool ok = true;
  for (int i = 0; i < N; i++) {
    left[i] = ok;
    ok = ok and (A[i] < 0 or A[i] == i + 1);
  }
  ok = true;
  for (int i = N - 1; i >= 0; i--) {
    right[i] = ok;
    ok = ok and (A[i] < 0 or A[i] == i - 1);
  }

  mint ans = 0;
  for (int i = 0; i < N; i++) {
    if (left[i] and right[i]) {
      ans += A[i] < 0 ? N : 1;
    }
  }
  for (int i = 0; i + 1 < N; i++) {
    if (left[i + 1] and right[i]) {
      ans -= 1;
    }
  }
  cout << ans.val();
}