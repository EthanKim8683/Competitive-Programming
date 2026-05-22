#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // (v1 + v2) * T[0] = 100
  // T[i] * v1 = T[i] * v2 + 100
  // (v1 - v2) * T[i] = 100

  int C;
  cin >> C;

  while (C--) {
    int N;
    cin >> N;

    vector<int> T(N);
    for (auto &e : T) cin >> e;

    int dt1 = T[0], dt2 = dt1;
    for (auto e : T) {
      if (e % dt1 == 0) continue;
      dt2 = e;
      break;
    }

    int t1 = dt1, t2 = dt2;
    vector<int> T2;
    while (T2.size() < N) {
      int t = min(t1, t2);
      T2.push_back(t);
      if (t1 == t) {
        t1 += dt1;
      }
      if (t2 == t) {
        t2 += dt2;
      }
    }
    cout << (T == T2 ? "VALID" : "INVALID") << '\n';
  }
}
