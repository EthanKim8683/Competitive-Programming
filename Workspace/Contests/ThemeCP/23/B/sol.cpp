#include <bits/stdc++.h>

using namespace std;

const int MAXX = 1e6;
const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<vector<int>> divisors(MAXX + 1);
  for (int i = 1; i <= MAXX; i++) {
    for (int j = i; j <= MAXX; j += i) {
      divisors[j].push_back(i);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int X, Y, K;
    cin >> X >> Y >> K;

    int g = gcd(X, Y);

    auto chmin = [&](int &a, int b) -> void { a = min(a, b); };

    vector<int> divisors1, divisors2;
    for (auto d : divisors[X / g]) {
      divisors1.push_back(d * g);
    }
    for (auto d : divisors[Y / g]) {
      divisors2.push_back(d * g);
    }

    vector<int> dp1(X + 1, INF);
    dp1[X] = 0;
    for (int i = divisors1.size() - 1; i >= 0; i--) {
      int d = divisors1[i];
      for (auto j : divisors[d]) {
        if (j > K) break;
        chmin(dp1[d / j], dp1[d] + 1);
      }
    }
    vector<int> dp2(Y + 1, INF);
    dp2[g] = dp1[g];
    for (int i = 0; i < divisors2.size(); i++) {
      int d = divisors2[i];
      for (auto j : divisors[Y / d]) {
        if (j > K) break;
        chmin(dp2[d * j], dp2[d] + 1);
      }
    }
    cout << (dp2[Y] == INF ? -1 : dp2[Y]) << '\n';
  }
}