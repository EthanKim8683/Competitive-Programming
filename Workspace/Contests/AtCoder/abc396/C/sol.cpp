#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> B(N);
  for (auto &e : B) cin >> e;

  vector<int> W(M);
  for (auto &e : W) cin >> e;

  sort(B.rbegin(), B.rend());
  sort(W.rbegin(), W.rend());

  int i = 0;
  i64 ans = 0;
  for (; i < N; i++) {
    if (B[i] < 0) break;
    ans += B[i];
  }
  for (int j = 0; j < min(i, M); j++) {
    if (W[j] < 0) break;
    ans += W[j];
  }
  for (int j = i; j < min(N, M); j++) {
    if (B[j] + W[j] < 0) break;
    ans += B[j] + W[j];
  }
  cout << ans;
}
