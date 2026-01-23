#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<i64> A(N);
    for (auto &e : A) cin >> e;

    auto rev = [&]() -> void { reverse(A.begin(), A.end()); };
    auto rep = [&]() -> void {
      vector<i64> A2;
      for (int i = 1; i < A.size(); i++) {
        A2.push_back(A[i] - A[i - 1]);
      }
      A = A2;
    };
    auto sum = [&]() -> i64 { return accumulate(A.begin(), A.end(), 0ll); };

    // auto A2 = A;
    // rev();
    // rep();
    // rep();
    // rev();
    // rep();
    // for (auto e : A) cout << e << ' ';
    // cout << '\n';

    // A = A2;
    // rep();
    // rep();
    // rep();
    // for (auto e : A) cout << e << ' ';
    // cout << '\n';

    i64 ans = sum();
    for (int i = 0; i < N - 1; i++) {
      rep();
      ans = max(ans, max(sum(), -sum()));
    }
    cout << ans << '\n';
  }
}
/*
sum dec by a[0]
*/
