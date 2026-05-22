#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<bool> prime(1e5 + 1, true);
  prime[0] = prime[1] = false;
  for (int i = 2; i * i < prime.size(); i++) {
    if (!prime[i]) continue;
    for (int j = i * i; j < prime.size(); j += i) {
      prime[j] = false;
    }
  }

  // vector<int> P(10);
  // iota(P.begin(), P.end(), 1);
  // int seen = 0;
  // do {
  //   int sum = 0, count = 0;
  //   bool ok = true;
  //   for (int i = 0; i < P.size(); i++) {
  //     sum += P[i];
  //     if (prime[(sum - 1) / (i + 1) + 1]) {
  //       count++;
  //     }
  //     ok = ok and count >= (i + 1) / 3 - 1;
  //   }
  //   if (ok) {
  //     for (auto e : P) {
  //       cerr << e << ' ';
  //     }
  //     cerr << '\n';
  //     seen++;
  //     if (seen == 100) break;
  //   }
  // } while (next_permutation(P.begin(), P.end()));

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    int p = -1;
    for (int i = 1; i <= N / 2; i++) {
      if (prime[N / 2 + i]) {
        p = N / 2 + i;
        break;
      }
      if (prime[N / 2 - i]) {
        p = N / 2 - i;
        break;
      }
    }
    vector<int> ans;
    ans.push_back(p);
    for (int i = 1; p - i >= 1 and p + i <= N; i++) {
      ans.push_back(p - i);
      ans.push_back(p + i);
    }
    vector<bool> seen(N + 1, false);
    for (auto e : ans) {
      seen[e] = true;
    }
    for (int i = 1; i <= N; i++) {
      if (!seen[i]) {
        ans.push_back(i);
      }
    }
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';

    // int sum = 0, count = 0;
    // bool ok = true;
    // for (int n = 1; n <= N; n++) {
    //   sum += ans[n - 1];
    //   if (prime[(sum - 1) / n + 1]) {
    //     count++;
    //   }
    //   ok = ok and count >= n / 3 - 1;
    // }
    // cerr << ok << '\n';
  }
}
