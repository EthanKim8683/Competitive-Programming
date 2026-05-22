#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  auto query = [&](int i, int j) -> int {
    cout << "? " << i + 1 << ' ' << j + 1 << endl;
    int rv;
    cin >> rv;
    return rv;
  };

  auto answer = [&](vi A) -> void {
    cout << '!';
    for (auto e : A) {
      cout << ' ' << e;
    }
    cout << endl;
  };

  vi A(N);
  int x = query(0, 1), y = query(1, 2), z = query(2, 0);
  A[1] = (x + y - z) / 2;
  A[0] = x - A[1];
  A[2] = y - A[1];
  rep(i, 3, N) { A[i] = query(0, i) - A[0]; }
  answer(A);
}
