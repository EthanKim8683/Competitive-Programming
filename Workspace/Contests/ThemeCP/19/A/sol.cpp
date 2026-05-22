#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    string S;
    cin >> S;

    // twos and threes

    fenwick_tree<i64> ft(N + 1);
    auto get = [&](int i) -> char {
      return (S[i] - 'a' + ft.sum(0, i + 1)) % 26 + 'a';
    };
    auto add = [&](int l, int r, int x) -> void {
      ft.add(l, x);
      ft.add(r, -x);
    };

    set<int> S2, S3;
    auto check2 = [&](int i) -> void {
      if (i < 0 or i + 1 >= N) return;
      if (S2.contains(i)) {
        S2.erase(i);
      }
      if (get(i) == get(i + 1)) {
        S2.insert(i);
      }
    };
    auto check3 = [&](int i) -> void {
      if (i < 0 or i + 2 >= N) return;
      if (S3.contains(i)) {
        S3.erase(i);
      }
      if (get(i) == get(i + 2)) {
        S3.insert(i);
      }
    };
    for (int i = 0; i < N; i++) {
      check2(i);
      check3(i);
    }

    while (M--) {
      int t, l, r;
      cin >> t >> l >> r;
      l--;

      if (t == 1) {
        int x;
        cin >> x;
        add(l, r, x);

        check2(l - 1);
        check3(l - 2);
        check3(l - 1);
        check2(r - 1);
        check3(r - 2);
        check3(r - 1);
      } else {
        bool ans = true;
        if (r - l >= 2) {
          ans = ans and S2.lower_bound(l) == S2.lower_bound(r - 1);
        }
        if (r - l >= 3) {
          ans = ans and S3.lower_bound(l) == S3.lower_bound(r - 2);
        }
        cout << (ans ? "YES" : "NO") << '\n';
      }
    }
  }
}
