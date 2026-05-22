#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // Diopantine equations?
  // n = m^2 - k^2
  // n = (m + k) * (m - k)
  // just kidding; factorize n

  int N;
  cin >> N;

  for (int i = 1; i * i <= N; i++) {
    if (N % i != 0) continue;
    int j = N / i;
    if (abs(i - j) % 2 == 0) {
      int m = (i + j) / 2, k = abs(i - j) / 2;
      cout << m << ' ' << k << '\n';
      exit(0);
    }
  }
  cout << "impossible";
}