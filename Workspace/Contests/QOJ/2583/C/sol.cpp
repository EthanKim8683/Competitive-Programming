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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) {
    cin >> e;
    e--;
  }

  int ans = 0, cover = 0, sum = 0, k = N;
  vc<pii> stack;
  vi next(N, -1);
  for (int i = N - 1; i >= 0; i--) {
    int j = next[A[i]];
    if (j != -1 and j < k) {
      k = j;

      int d = j - i;
      while (sz(stack) > 0 and stack.back().fs > d) {
        auto [d2, c] = stack.back();
        sum -= d2 * c;
        cover -= c;
        stack.pop_back();
      }
      int c = N - j - cover;
      sum += d * c;
      cover += c;
      stack.eb(d, c);
    }
    next[A[i]] = i;

    ans += sum;
  }
  cout << ans;
}
