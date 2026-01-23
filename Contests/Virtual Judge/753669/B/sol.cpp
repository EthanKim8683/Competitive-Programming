#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int K, N;
  cin >> K >> N;

  // gaps of 1 and 2
  //
  // brute force left and right

  if (K == 1) {
    if (N <= 3) {
      for (int i = 0; i < N; i++) {
        cout << (i == N / 2 ? "X" : "-");
      }
    } else {
      cout << "*";
    }
    exit(0);
  }

  for (int l = 0; l <= 1; l++) {
    for (int r = 0; r <= 1; r++) {
      int g = N - l - r - K;
      if (K - 1 <= g and g <= 2 * (K - 1)) {
        int t = g - (K - 1);
        for (int i = 0; i < l; i++) {
          cout << "-";
        }
        for (int i = 0; i < K - 1; i++) {
          cout << "X";
          if (i < t) {
            cout << "--";
          } else {
            cout << "-";
          }
        }
        cout << "X";
        for (int i = 0; i < r; i++) {
          cout << "-";
        }
        exit(0);
      }
    }
  }
  cout << "*";
}