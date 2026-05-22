#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define double long double
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

const string BYR = "BYR";
const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

const ll mod = (119 << 23) + 1, root = 62;

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}

typedef vi vl;
void ntt(vl &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vl rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    ll z[] = {1, modpow(root, mod >> s)};
    rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? mod : 0);
        ai += (ai + z >= mod ? z - mod : z);
      }
}
vl conv(const vl &a, const vl &b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
  int inv = modpow(n, mod - 2);
  vl L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  rep(i, 0, n) out[-i & (n - 1)] = (ll) L[i] * R[i] % mod * inv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  string S;
  if (argc > 1) {
    S.resize(2e5);
    for (auto &e : S) {
      e = BYR[rng() % 3];
    }
  } else {
    cin >> S;
  }

  int N = sz(S);

  auto compress = [&](char c) -> int {
    return find(all(BYR), c) - BYR.begin();
  };

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
      if (y & 1) {
        (rv *= x) %= MOD;
      }
    }
    return rv;
  };

  auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

  // number of ways to reach this state * (needs more ops ? 1 : 0)

  vi facts(N + 1);
  facts[0] = 1;
  rep(i, 1, N + 1) { facts[i] = facts[i - 1] * i % MOD; }

  auto binom = [&](int n, int k) -> int {
    if (n < 0 or k < 0 or n - k < 0) return 0;
    return facts[n] * mod_inv(facts[k] * facts[n - k]);
  };

  // vc dp(N + 1, vc(N + 1, vi(3 + 1, 0)));
  // rep(i, 0, N) {
  //   int d = compress(S[i]);
  //   dp[i + 1][1][d] += 1;
  //   rep(j, 1, i + 1) {
  //     rep(k, 0, 3 + 1) {
  //       (dp[i + 1][j + 1][d < k ? 3 : k] += dp[i][j][k]) %= MOD;
  //       (dp[i + 1][j][k] += dp[i][j][k]) %= MOD;
  //     }
  //   }
  // }
  // int ans = 0;
  // rep(i, 0, N + 1) {
  //   (ans += facts[i] * facts[N - i] % MOD * dp[N][i][3]) %= MOD;
  // }
  // (ans *= mod_inv(facts[N])) %= MOD;
  // cout << ans << '\n';

  // divide and conquer?

  pii order[6] = {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {1, 2}, {2, 2}};
  int index[3][3] = {{0, 1, 2}, {-1, 3, 4}, {-1, -1, 5}};

  auto dfs = [&](auto self, int l, int r) -> vc<vi> {
    vc rv(6, vi(r - l + 1, 0));
    if (r - l == 1) {
      int d = compress(S[l]), c = index[d][d];
      rv[c][1] = 1;
      return rv;
    }
    int m = l + (r - l) / 2;
    auto A = self(self, l, m), B = self(self, m, r);
    rep(i, 0, 6) {
      rep(j, 0, 6) {
        if (order[i].sd > order[j].fs) continue;
        auto C = conv(A[i], B[j]);
        int c = index[order[i].fs][order[j].sd];
        rep(k, 0, sz(C)) { (rv[c][k] += C[k]) %= MOD; }
      }
      rep(j, 0, sz(A[i])) { (rv[i][j] += A[i][j]) %= MOD; }
      rep(j, 0, sz(B[i])) { (rv[i][j] += B[i][j]) %= MOD; }
    }
    return rv;
  };
  auto dp = dfs(dfs, 0, N);
  int ans = 0;
  rep(i, 1, N + 1) {
    int sum = binom(N, i);
    rep(j, 0, 6) { (sum += MOD - dp[j][i]) %= MOD; }
    (ans += facts[i] * facts[N - i] % MOD * sum) %= MOD;
  }
  (ans *= mod_inv(facts[N])) %= MOD;
  cout << ans << '\n';
}
