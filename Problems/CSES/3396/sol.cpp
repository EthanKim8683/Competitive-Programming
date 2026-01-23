#include <bits/stdc++.h>

#include "ethankim8683/algebra.hpp"

using namespace std;

using u64 = unsigned long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    u64 N;
    cin >> N;

    do {
      N++;
    } while (!is_prime(N));
    cout << N << '\n';
  }
}
