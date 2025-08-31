#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K, S, T;
  cin >> N >> K >> S >> T;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<i64> norm;
  for (int i = 0; i < N; i++) {
    if ((A[i] & S) != S or (T & A[i]) != A[i]) continue;
    norm.push_back((i64) (A[i] & ~S) << 18 | (T & ~A[i]));
  }
}
