#include <bits/stdc++.h>

using namespace std;

const int MAXM = 1e6;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  vector<bool> is_prime(MAXM + 1, true);
  vector<int> primes, mu(MAXM + 1);
  mu[1] = 1;
  for (int i = 2; i <= MAXM; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      mu[i] = -1;
    }

    for (auto e : primes) {
      if (i * e > MAXM) break;
      is_prime[i * e] = false;
      if (i % e == 0) {
        mu[i * e] = 0;
        break;
      } else {
        mu[i * e] = mu[i] * mu[e];
      }
    }
  }

  vector<vector<int>> good_divisors(MAXM + 1);
  for (int i = 1; i <= MAXM; i++) {
    if (mu[i] == 0) continue;
    for (int j = i; j <= MAXM; j += i) {
      good_divisors[j].push_back(i);
    }
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N, M;
    if (argc > 1) {
      N = 2e5;
      M = 1e6;
    } else {
      cin >> N >> M;
    }

    vector<int> A(N);
    if (argc > 1) {
      for (int i = 0; i < N; i++) {
        if (i == N - 1) {
          A[i] = 1;
        } else {
          A[i] = 510510;
        }
      }
    } else {
      for (auto &e : A) cin >> e;
    }

    vector<bool> exclude(N, false);
    auto find = [&]() -> int {
      vector<int> counts(M + 1, 0);
      int pie = 0;
      for (int i = 0; i < N; i++) {
        if (exclude[i]) continue;
        for (auto e : good_divisors[A[i]]) {
          pie += mu[e] * counts[e];
          counts[e]++;
        }
        if (pie != 0) return i;
      }
      return -1;
    };
    auto brute = [&](int j) -> vector<int> {
      vector<int> rv;
      for (int i = 0; i < N; i++) {
        if (exclude[i]) continue;
        if (gcd(A[i], A[j]) == 1) {
          rv.push_back(i);
        }
      }
      return rv;
    };

    int i = find();
    if (i == -1) {
      cout << "0\n";
      continue;
    }

    auto I = brute(i);
    exclude[i] = exclude[I[0]] = true;

    int j = find(), p = -1, q, r, s;
    if (j == -1) {
      j = I[0];
      I = brute(i);
      auto J = brute(j);
      for (auto e1 : I) {
        for (auto e2 : J) {
          if (e1 == e2) continue;
          p = i;
          q = e1;
          r = j;
          s = e2;
          goto FOUND;
        }
      }
    FOUND:
    } else {
      auto J = brute(j);
      p = i;
      q = I[0];
      r = j;
      s = J[0];
    }
    if (p == -1) {
      cout << "0\n";
      continue;
    }

    cout << p + 1 << ' ' << q + 1 << ' ' << r + 1 << ' ' << s + 1 << '\n';
  }
}
