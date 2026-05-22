#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  cout << "YES\n";
  for (int i = 0; i < N; i++) {
    cout << i + 1 << ' ' << i + 1 << '\n';
  }
  for (int i = 0; i < N; i++) {
    int j = A[i] / 2;
    if (j + j > i + i) {
      cout << i + j + 1 << '\n';
    } else {
      cout << i - j + 1 << '\n';
    }
  }
}
