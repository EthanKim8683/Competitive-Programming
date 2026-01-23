#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N, Q;
    if (argc > 1) {
      N = 1e3;
      Q = 1e3;
    } else {
      cin >> N >> Q;
    }

    vector<int> P;
    if (argc > 1) {
      P.resize(N);
      iota(P.begin(), P.end(), 0);
      shuffle(P.begin(), P.end(), rng);
    }

    vector<pair<int, int>> ranges(Q);
    if (argc > 1) {
      for (auto &[l, r] : ranges) {
        l = rng() % N;
        r = rng() % N;
        if (l > r) {
          swap(l, r);
        }
        r++;
      }
    } else {
      for (auto &[l, r] : ranges) {
        cin >> l >> r;
        l--;
      }
    }

    auto key = [&](pair<int, int> x) -> pair<int, int> {
      auto [l, r] = x;
      return {l, -r};
    };
    sort(ranges.begin(), ranges.end(),
         [&](pair<int, int> a, pair<int, int> b) -> bool {
           return key(a) < key(b);
         });
    vector<pair<int, int>> ranges2;
    int r2 = 0;
    for (auto [l, r] : ranges) {
      if (r > r2) {
        ranges2.push_back({l, r});
        r2 = r;
      }
    }

    auto mex = [&](int l, int r) -> int {
      assert(argc > 1);
      set<int> S;
      for (int i = l; i < r; i++) {
        S.insert(P[i]);
      }
      for (int i = 0; i < N; i++) {
        if (!S.contains(i)) return i;
      }
      return N;
    };

    int q = 0;
    auto query = [&](int l, int r) -> int {
      if (argc > 1) {
        q++;
        assert(q <= 30);
        return mex(l, r);
      } else {
        cout << "? " << l + 1 << ' ' << r << endl;
        int rv;
        cin >> rv;
        return rv;
      }
    };

    auto answer = [&](int x) -> void {
      if (argc > 1) {
        int ans = 0;
        for (auto [l, r] : ranges) {
          ans = max(ans, mex(l, r));
        }
        assert(x == ans);
      } else {
        cout << "! " << x << endl;
      }
    };

    auto check = [&](int i) -> bool {
      auto [l, r] = ranges2[i];
      return query(l, N) < query(0, r);
    };

    auto solve = [&](int i) -> int {
      auto [l, r] = ranges2[i];
      return query(l, r);
    };

    int l = 0, r = ranges2.size() - 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    int ans = solve(l);
    if (l >= 1) {
      ans = max(ans, solve(l - 1));
    }
    answer(ans);
  }
}
