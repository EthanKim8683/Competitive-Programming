#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

const ll mod = (119 << 23) + 1;

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}

const ll root = 62;
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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc<vi> adj(N);
  rep(i, 0, N - 1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  vi size(N), parent(N);
  auto dfs = [&](auto self, int a, int p) -> void {
    size[a] = 1;
    parent[a] = p;
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a);
      size[a] += size[b];
    }
  };
  dfs(dfs, 0, -1);
  auto get_subtree_size = [&](int a, int b) -> int {
    if (a == parent[b]) {
      return size[b];
    } else {
      return N - size[a];
    }
  };

  vc<bool> is_cut(N, false);
  vi size2(N);
  auto dfs2 = [&](auto self, int a, int p) -> void {
    size2[a] = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      if (is_cut[b]) continue;
      self(self, b, a);
      size2[a] += size2[b];
    }
  };

  auto dfs3 = [&](auto self, int a, int n, int p) -> int {
    for (auto b : adj[a]) {
      if (b == p) continue;
      if (is_cut[b]) continue;
      if (2 * size2[b] > n) return self(self, b, n, a);
    }
    return a;
  };

  vi ans(N, 0), depth(N);
  auto dfs4 = [&](auto self, int a) -> void {
    dfs2(dfs2, a, -1);
    a = dfs3(dfs3, a, size2[a], -1);

    auto dfs5 = [&](auto self, int a, int d, int p) -> void {
      if (is_cut[a]) {
        depth[a] = 0;
        return;
      }

      depth[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, d + 1, a);
        chmax(depth[a], depth[b]);
      }
    };
    dfs5(dfs5, a, 0, -1);
    sort(all(adj[a]),
         [&](int a, int b) -> bool { return depth[a] < depth[b]; });

    int sum = 0;
    for (auto b : adj[a]) {
      int count = get_subtree_size(a, b);
      sum += count * count;
    }

    vi accum;
    for (auto b : adj[a]) {
      vi counts(depth[b] + 1, 0);
      auto dfs6 = [&](auto self, int a, int d, int p) -> void {
        if (is_cut[a]) return;

        (counts[d] += 1) %= MOD;
        int accum = 1;
        for (auto b : adj[a]) {
          if (b == p) continue;
          self(self, b, d + 1, a);
          int count = get_subtree_size(a, b);
          (counts[d] += 2 * accum * count) %= MOD;
          accum += count;
        }
      };
      dfs6(dfs6, b, 1, a);

      auto convolution = conv(accum, counts);
      rep(i, 1, sz(convolution)) { (ans[i] += convolution[i]) %= MOD; }

      int count = get_subtree_size(a, b),
          zero = ((N - count) * (N - count) - (sum - count * count)) % MOD;
      rep(i, 1, sz(counts)) { (ans[i] += zero * counts[i]) %= MOD; }

      accum.resize(sz(counts), 0);
      rep(i, 1, sz(counts)) { (accum[i] += counts[i]) %= MOD; }
    }

    is_cut[a] = true;
    for (auto b : adj[a]) {
      if (is_cut[b]) continue;
      self(self, b);
    }
  };
  dfs4(dfs4, 0);

  rep(i, 1, N) { cout << ans[i] << ' '; }
  cout << '\n';
}
