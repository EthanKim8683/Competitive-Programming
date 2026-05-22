#include <bits/stdc++.h>

#include "ethankim8683/combinatorics.hpp"

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, P;
  cin >> N >> P;

  vector A(N, vector<int>(N));
  for (auto &r : A) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  auto mat_mul = [&](vector<vector<int>> A, vector<vector<int>> B,
                     int mod) -> vector<vector<int>> {
    vector rv(A.size(), vector<int>(B[0].size(), 0));
    for (int i = 0; i < A.size(); i++) {
      for (int j = 0; j < B[0].size(); j++) {
        for (int k = 0; k < A[0].size(); k++) {
          (rv[i][j] += A[i][k] * B[k][j]) %= mod;
        }
      }
    }
    return rv;
  };

  auto mat_pow = [&](vector<vector<int>> X, int y,
                     int mod) -> vector<vector<int>> {
    vector rv(X.size(), vector<int>(X.size(), 0));
    for (int i = 0; i < X.size(); i++) {
      rv[i][i] = 1;
    }
    for (; y; y >>= 1, X = mat_mul(X, X, mod)) {
      if (y & 1) {
        rv = mat_mul(rv, X, mod);
      }
    }
    return rv;
  };

  auto print_mat = [&](vector<vector<int>> A) -> void {
    for (auto r : A) {
      for (auto e : r) {
        cout << e << ' ';
      }
      cout << '\n';
    }
  };

  for (auto &r : A) {
    for (auto &e : r) {
      if (e == 0) {
        e = (i64) (P - 1) / 2 * P % P;
      }
    }
  }
  print_mat(mat_pow(A, P, P));
}
