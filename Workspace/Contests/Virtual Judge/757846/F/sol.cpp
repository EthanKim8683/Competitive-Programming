#pragma GCC optimize("trapv")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double
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

const int MAXN = 1000;
const float PI = 2 * acos(0);
const float INF = 1e300;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // hrs per yr = 2*pi*r/s
  // days per yr = 2*pi*r/s / h
  // d = floor(2*pi*r/s / h)
  // d + 1/n1 - 1/n2 + 1/n3 = days per yr

  int R, S, H;
  cin >> R >> S >> H;

  float d = 2 * PI * R / S / H, D, sign;
  if (d - (int) d < 0.5) {
    D = (int) d;
    sign = 1;
  } else {
    D = (int) d + 1;
    sign = -1;
  }
  tuple<float, int, int, int> best = {INF, -1, -1, -1};
  for (int n1 = 2; n1 <= MAXN; n1++) {
    for (int n2 = 2 * n1; n2 <= MAXN; n2 += n1) {
      for (int n3 = 2 * n2; n3 <= MAXN; n3 += n2) {
        best = min(best, {abs(D + sign * (1.L / n1 - 1.L / n2 + 1.L / n3) - d),
                          n1, n2, n3});
      }
    }
  }
  auto [error, n1, n2, n3] = best;
  cout << n1 << ' ' << n2 << ' ' << n3;
}