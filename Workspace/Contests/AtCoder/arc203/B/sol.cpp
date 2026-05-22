#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<int> B(N);
    for (auto &e : B) cin >> e;

    int n = count(A.begin(), A.end(), 1);
    if (n != count(B.begin(), B.end(), 1)) {
      cout << "No\n";
      continue;
    }

    if (n == 1) {
      A.erase(unique(A.begin(), A.end()), A.end());
      B.erase(unique(B.begin(), B.end()), B.end());
      cout << (A == B ? "Yes" : "No") << '\n';
      continue;
    }

    cout << "Yes\n";
  }
}