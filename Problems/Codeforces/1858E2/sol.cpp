#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

const int MAXQ = 1e6;
const int MAXX = 1e6;
const int INF = 1e9;

struct Change {
  vector<pair<int, int>> first, inv_first, ft;
  int n;
};

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  // keep track of the first occurrence of each integer
  // decrease n upon rollback
  // n may reach first occurrence, so replace it with infinity lazily

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  vector<int> first(MAXX + 1, INF), inv_first(MAXQ, -1);
  fenwick_tree<int> ft(MAXQ);
  int n = 0;
  vector<Change> history(MAXQ);

  vector<vector<int>> saves;
  if (argc > 1) {
    saves.emplace_back();
  }

  int Q;
  if (argc > 1) {
    Q = 1e3;
  } else {
    cin >> Q;
  }

  while (Q--) {
    char t;
    if (argc > 1) {
      do {
        t = "+-!?"[rng() % 4];
      } while ((t == '-' and saves.back().size() == 0) or
               (t == '!' and saves.size() == 1));
    } else {
      cin >> t;
    }

    if (t == '+') {
      int X;
      if (argc > 1) {
        X = rng() % MAXX + 1;
      } else {
        cin >> X;
      }

      Change change;

      int x = inv_first[n];
      if (x != -1) {
        change.first.emplace_back(x, first[x]);
        first[x] = INF;

        change.inv_first.emplace_back(n, inv_first[n]);
        inv_first[n] = -1;

        change.ft.emplace_back(n, -1);
        ft.add(n, -1);
      }

      int i = first[X];
      if (i >= n) {
        if (i != INF) {
          change.first.emplace_back(X, first[X]);
          first[X] = INF;

          change.inv_first.emplace_back(i, inv_first[i]);
          inv_first[i] = -1;

          change.ft.emplace_back(i, -1);
          ft.add(i, -1);
        }

        change.first.emplace_back(X, first[X]);
        first[X] = n;

        change.inv_first.emplace_back(n, inv_first[n]);
        inv_first[n] = X;

        change.ft.emplace_back(n, 1);
        ft.add(n, 1);
      }

      change.n = n;
      n += 1;

      history.push_back(change);

      if (argc > 1) {
        auto save = saves.back();
        save.push_back(X);

        saves.emplace_back(save);
      }
    } else if (t == '-') {
      int K;
      if (argc > 1) {
        K = rng() % saves.back().size() + 1;
      } else {
        cin >> K;
      }

      Change change;

      change.n = n;
      n -= K;

      history.push_back(change);

      if (argc > 1) {
        auto save = saves.back();
        save.erase(save.end() - K, save.end());

        saves.emplace_back(save);
      }
    } else if (t == '!') {
      auto change = history.back();
      history.pop_back();

      reverse(change.first.begin(), change.first.end());
      for (auto [x, i] : change.first) {
        first[x] = i;
      }

      reverse(change.inv_first.begin(), change.inv_first.end());
      for (auto [i, x] : change.inv_first) {
        inv_first[i] = x;
      }

      reverse(change.ft.begin(), change.ft.end());
      for (auto [i, x] : change.ft) {
        ft.add(i, -x);
      }

      n = change.n;

      if (argc > 1) {
        saves.pop_back();
      }
    } else {
      int ans = ft.sum(0, n);
      cout << ans << endl;

      if (argc > 1) {
        set<int> S;
        for (auto e : saves.back()) {
          S.insert(e);
        }
        assert(ans == S.size());
      }
    }
  }
}
