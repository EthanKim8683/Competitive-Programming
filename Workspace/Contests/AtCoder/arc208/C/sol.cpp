#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int C, X;
    cin >> C >> X;

    if (__lg(X) < __lg(C)) {
      cout << (X ^ C) << '\n';
    } else if (__lg(X) > __lg(C)) {
      if (~X >> __lg(C) & 1) {
        cout << (X ^ C) << '\n';
      } else {
        cout << -1 << '\n';
      }
    } else {
      if (X <= C) {
        int n = 1 << 30 | (C - X) >> 1;
        if ((n ^ C) % n == X) {
          cout << n << '\n';
        } else {
          cout << -1 << '\n';
        }
      } else {
        cout << -1 << '\n';
      }
    }
  }
}