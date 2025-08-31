#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  fenwick_tree<int> ft(N + 1);
  vector<int> U(N, -1);
  for (int i = 0; i < N; i++) {
    // <=: +
    // >: -
    ft.add(0, -1);
    ft.add(A[i], 2);
    int l = 0, r = N;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      ft.sum(0, m) == -1 ? l = m : r = m - 1;
    }
    ft.add(0, 1);
    ft.add(l, -1);
    U[i] += ft.sum(0, A[i] + 1);
  }
  ft = fenwick_tree<int>(N + 1);
  for (int i = N - 1; i >= 0; i--) {
    // <=: +
    // >: -
    U[i] += ft.sum(0, A[i] + 1);
    ft.add(0, -1);
    ft.add(A[i], 2);
    int l = 0, r = N;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      ft.sum(0, m) == -1 ? l = m : r = m - 1;
    }
    ft.add(0, 1);
    ft.add(l, -1);
  }

  ft = fenwick_tree<int>(N + 1);
  vector<int> L(N, 0);
  for (int i = 0; i < N; i++) {
    // <: -
    // >=: +
    ft.add(N, -1);
    ft.add(A[i], 2);
    int l = 0, r = N + 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      ft.sum(m, N + 1) == -1 ? r = m : l = m + 1;
    }
    ft.add(N, 1);
    if (l >= 0) {
      ft.add(l - 1, -1);
    }
    L[i] += ft.sum(A[i], N + 1);
  }
  ft = fenwick_tree<int>(N + 1);
  for (int i = N - 1; i >= 0; i--) {
    // <: -
    // >=: +
    L[i] += ft.sum(A[i], N + 1);
    ft.add(N, -1);
    ft.add(A[i], 2);
    int l = 0, r = N + 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      ft.sum(m, N + 1) == -1 ? r = m : l = m + 1;
    }
    ft.add(N, 1);
    if (l >= 0) {
      ft.add(l - 1, -1);
    }
  }

  for (int i = 0; i < N; i++) {
    cout << max(U[i], L[i]) / 2 << ' ';
  }
}
