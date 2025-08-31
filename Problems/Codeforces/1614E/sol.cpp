#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using i64 = long long;

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // I had it; I really just needed to get it all on paper first before
  // trial-and-erroring my way to a solution

  int N;
  cin >> N;

  ordered_set<pair<int, int>> os;
  int t = 0, t_ = 0;
  while (N--) {
    int T;
    cin >> T;

    auto f = [&](int x) -> int { return x - os.order_of_key({x, INF}) + t; };

    int l = T - t, r = T + t;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      f(m) <= T ? l = m : r = m - 1;
    }
    int x1 = l;
    l = T - t;
    r = T + t;
    while (l < r) {
      int m = l + (r - l) / 2;
      f(m) >= T ? r = m : l = m + 1;
    }
    int x2 = l;
    os.insert({x1 + 1, t_++});
    os.insert({x2, t_++});
    t++;

    int K;
    cin >> K;

    while (K--) {
      int X;
      cin >> X;

      static int ans = 0;
      X = (X + ans) % (int) (1e9 + 1);
      ans = f(X);
      cout << ans << '\n';
    }
  }
}
