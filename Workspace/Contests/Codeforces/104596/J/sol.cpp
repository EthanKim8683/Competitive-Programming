#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXL = 1e14;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vc<pii> books(N);
  for (auto &[d, l] : books) {
    cin >> l >> d;
  }
  sort(all(books));

  auto check = [&](int x) -> bool {
    multiset<int> S;
    int sum = 0, cost = 0;
    for (auto [d, l] : books) {
      if (sum + l <= d * x) {
        sum += l;
        S.insert(l);
      } else {
        cost++;
        if (S.size() > 0) {
          auto it = prev(S.end());
          if (l < *it) {
            sum -= *it;
            S.erase(it);
            sum += l;
            S.insert(l);
          }
        }
      }
    }
    return cost <= M;
  };
  int l = 0, r = MAXL;
  while (l < r) {
    int m = l + (r - l) / 2;
    check(m) ? r = m : l = m + 1;
  }
  cout << l;
}