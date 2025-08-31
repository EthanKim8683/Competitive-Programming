#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  bool ans = false;
  for (int i = 0; i + 2 < N; i++) {
    ans = ans or (A[i] == A[i + 1] and A[i] == A[i + 2]);
  }
  cout << (ans ? "Yes" : "No");
}
