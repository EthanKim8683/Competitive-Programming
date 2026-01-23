#include <bits/stdc++.h>

using namespace std;

using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  f64 D, S;
  cin >> D >> S;

  // (S * K + x * (N - K)) / N = D
  // x = (N * D - S * K) / (N - K)

  f64 x = (N * D - S * K) / (N - K);
  if (0 <= x and x <= 100) {
    cout << setprecision(14) << fixed << x;
  } else {
    cout << "impossible";
  }
}