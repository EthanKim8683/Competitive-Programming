#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
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

  // see first and last K (2*K)
  //
  // which ones differ? if none, no ans
  //
  // else binary search for change (log2(N/K))
  //
  // split must be no later (K)

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    auto query = [&](int i) -> int {
      cout << "? " << i + 1 << endl;
      int rv;
      cin >> rv;
      return rv;
    };

    auto answer = [&](int a, int b) -> void {
      cout << "! " << a << ' ' << b << endl;
    };

    auto impossible = [&]() -> void { cout << "! -1" << endl; };

    if (K == 1) {
      if (N == 2) {
        answer(1, 1);
      } else {
        impossible();
      }
      continue;
    }

    if (N == 2 * K) {
      answer(K, K);
      continue;
    }

    vi head(K), tail(K);
    rep(i, 0, K) {
      head[i] = query(i);
      tail[(N - K + i) % K] = query(N - K + i);
    }
    vc<bool> eqs(K);
    rep(i, 0, K) { eqs[i] = head[i] == tail[i]; }
    bool ok = true;
    rep(i, 0, K - 1) { ok = ok and !(eqs[i] and eqs[i + 1]); }
    if (!ok) {
      impossible();
      continue;
    }
    int idiff = -1;
    rep(i, 0, K) {
      if (eqs[i]) continue;
      idiff = i;
    }

    // idiff + rK <= N - 1
    // r <= (N - 1 - idiff) / K
    int l = 1, r = (N - 1 - idiff) / K;
    while (l < r) {
      int m = l + (r - l) / 2;
      query(idiff + m * K) == tail[idiff] ? r = m : l = m + 1;
    }
    int a = idiff + l * K;
    for (int i = a - 1; i > idiff + (l - 1) * K; i--) {
      if (query(i) != head[i % K]) {
        a = i;
      }
    }
    chmin(a, N - K);
    answer(a, N - a);
  }
}
