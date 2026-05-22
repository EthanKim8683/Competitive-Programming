#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    vector<int> ps(N + 1);
    ps[0] = 1;
    for (int i = 0; i < N; i++) {
      ps[i + 1] = ps[i] + (S[i] == '+' ? -1 : 1);
    }

    ordered_set<pair<int, int>> by_mod[3];
    i64 ans = 0;
    for (int i = 0; i <= N; i++) {
      int k = (ps[i] % 3 + 3) % 3;
      ans += by_mod[k].order_of_key({ps[i], N});
      by_mod[k].insert({ps[i], i});
    }
    cout << ans << '\n';
  }
}
