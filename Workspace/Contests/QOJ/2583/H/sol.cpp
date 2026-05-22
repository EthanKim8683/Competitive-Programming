#pragma GCC optimize("Ofast,unroll-loops")
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
typedef vc<int> vi;

struct FT {
  vi s;
  FT(int n) : s(n) {}
  void update(int pos, int dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  int query(int pos) {
    int res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
  int lower_bound(int sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    }
    return pos;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  sort(all(A));
  reverse(all(A));

  vi order(N);
  iota(all(order), 0);
  sort(all(order),
       [&](int a, int b) -> bool { return tie(A[a], a) < tie(A[b], b); });

  vi index(N);
  rep(i, 0, N) { index[order[i]] = i; }

  FT f1(N), f2(N);
  vi ans(N, 0);
  for (int i = N - 1; i >= 0; i--) {
    f1.update(index[i], 1);
    f2.update(index[i], A[i]);

    int m1 = (N - i) / 2, j = f1.lower_bound(m1 + 1),
        m2 = f2.query(j + 1) - f2.query(j);
    ans[i] = (f2.query(N) - f2.query(j) - (N - i - m1) * m2) +
             (m1 * m2 - f2.query(j));
  }

  for (auto e : ans) {
    cout << e << '\n';
  }
}
