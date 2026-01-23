#pragma GCC optimize("trapv")
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

using ll = long long;

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

ll crt(ll a, ll m, ll b, ll n) {
  if (n > m) swap(a, b), swap(m, n);
  ll x, y, g = euclid(m, n, x, y);
  assert((a - b) % g == 0);
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m * n / g : x;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int a, b, c, d, e, f, g;
  cin >> a >> b >> c >> d >> e >> f >> g;

  vi volumes;
  for (int h = 1; h <= min(a, b) / 2; ++h) {
    int v = h * (a - 2 * h) * (b - 2 * h);
    volumes.push_back(v);
  }
  sort(all(volumes));

  int u = sz(volumes);
  int m1 = volumes[u - 1];
  int m2 = volumes[u - 2];
  int m3 = volumes[u - 3];

  // cerr << "m1 = " << m1 << endl;
  // cerr << "m2 = " << m2 << endl;
  // cerr << "m3 = " << m3 << endl;

  int r1 = c % m1;
  int r2 = d % m2;
  int r3 = e % m3;

  int lm1 = lcm(m1, m2);
  int rm1 = crt(r1, m1, r2, m2);
  // cerr << "doing second round " << rm1 << " mod " << lm1 << endl;
  int lm2 = lcm(lm1, m3);
  int rm2 = crt(rm1, lm1, r3, m3);
  assert(rm2 < lm2 && rm2 > 0);

  // move into the range
  int delt = (rm2 - (f % lm2) + lm2) % lm2;
  int targ = f + delt;

  assert(targ % m1 == r1);
  assert(targ % m2 == r2);
  assert(targ % m3 == r3);
  assert(targ >= f && targ <= g);
  cout << targ << endl;
}