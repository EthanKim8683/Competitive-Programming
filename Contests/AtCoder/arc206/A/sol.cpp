#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<vector<int>> occurences(N + 1);
  for (int i = 0; i < N; i++) {
    occurences[A[i]].push_back(i);
  }

  i64 ans = 1;
  for (int i = 0; i + 1 < N; i++) {
    if (A[i + 1] != A[i]) {
      ans += (N - (i + 1)) - (occurences[A[i]].end() -
                              lower_bound(occurences[A[i]].begin(),
                                          occurences[A[i]].end(), i + 1));
    }
  }
  cout << ans;
}