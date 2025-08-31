#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    // all people need avg candies (if avg is not an integer, there is no
    // solution)
    //
    // each person's difference must be a range of 1's in a sea of 0's
    // this represents a "giving" and "getting", and so as long as the givings
    // and gettings match up, we have a rough solution
    //
    // to check if every person will have enough to give, we can make
    // components, merging giving and gettings, and check if each component has
    // a person capable of giving first to "jumpstart" the rest of the component

    i64 sum = accumulate(A.begin(), A.end(), 0ll);
    if (sum % N != 0) {
      cout << "No\n";
      continue;
    }
    int avg = sum / N;

    vector<bool> good(32, false);
    dsu d(32);
    bool ok = true;
    for (int i = 0; i < N; i++) {
      int diff = abs(avg - A[i]);
      if (diff == 0) continue;

      int u = __lg(diff) + 1, v = __lg((1 << u) - diff);
      if ((1 << u) - (1 << v) != diff) {
        ok = false;
        break;
      }

      cout << u << ' ' << v << '\n';

      bool good_ = good[d.leader(u)] or good[d.leader(v)];
      if (A[i] > avg) {
        good_ = good_ or A[i] - (1 << u) >= 0;
      } else {
        good_ = good_ or A[i] - (1 << v) >= 0;
      }
      good[d.merge(u, v)] = good_;
    }
    if (!ok) {
      cout << "No\n";
      continue;
    }

    bool ans = true;
    for (int i = 0; i < 32; i++) {
      if (d.leader(i) != i) continue;
      ans = ans and (d.size(i) == 1 or good[i]);
    }
    cout << (ans ? "Yes" : "No") << '\n';
  }
}
