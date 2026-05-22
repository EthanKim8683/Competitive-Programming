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
typedef pair<float, float> vec;
typedef pair<float, float> pff;

const float PI = 2 * acos(0.L);

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc<pair<vec, float>> trees(N);
  for (auto &[v, r] : trees) {
    auto &[x, y] = v;
    cin >> x >> y >> r;
  }

  float B, D;
  cin >> B >> D;

  auto delta = [&](vec a, vec b) -> vec {
    auto [x1, y1] = a;
    auto [x2, y2] = b;
    return {x2 - x1, y2 - y1};
  };

  auto dot = [&](vec a, vec b) -> float {
    auto [x1, y1] = a;
    auto [x2, y2] = b;
    return x1 * x2 + y1 * y2;
  };

  auto len = [&](vec a) -> float { return sqrt(dot(a, a)); };

  vc<pff> ranges;
  for (auto [v, r] : trees) {
    float d = len(v);

    // atan2(y, x) = t

    auto [x, y] = v;
    float t = atan2(y, x);

    // c^2 = a^2 + b^2 - 2abcos(dt)
    // cos(dt) = (a^2 + b^2 - c^2) / (2ab)
    // dt = acos((a^2 + b^2 - c^2) / (2ab))

    float h = d, o = B + r;
    float A2 = h * h - o * o;
    if (A2 < 0) continue;
    float A = sqrt(A2);

    float a = d, b = min(D, A), c = B + r;
    float cosdt = (a * a + b * b - c * c) / (2 * a * b);
    if (cosdt > 1) continue;
    float dt = acos(cosdt);

    auto mod = [&](float x) -> float {
      while (x < 0) {
        x += 2 * PI;
      }
      while (x >= 2 * PI) {
        x -= 2 * PI;
      }
      return x;
    };
    float l = mod(t - dt), u = mod(t + dt);

    if (l <= u) {
      ranges.eb(l, u);
    } else {
      ranges.eb(l, 2 * PI);
      ranges.eb(0, u);
    }
  }

  if (ranges.empty()) {
    cout << 1;
    exit(0);
  }

  vc<float> cc;
  for (auto [l, r] : ranges) {
    cc.pb(l);
    cc.pb(r);
  }
  sort(all(cc));
  cc.erase(unique(all(cc)), cc.end());

  // for (auto [l, r] : ranges) {
  //   cerr << l << ' ' << r << '\n';
  // }
  // cerr << '\n';

  // for (auto e : cc) {
  //   cerr << e << ' ';
  // }
  // cerr << '\n';
  // cerr << '\n';

  vi ps(cc.size() + 1, 0);
  for (auto &[l, r] : ranges) {
    ps[lower_bound(all(cc), l) - cc.begin()]++;
    ps[lower_bound(all(cc), r) - cc.begin()]--;
  }
  rep(i, 0, cc.size()) { ps[i + 1] += ps[i]; }

  // for (auto e : ps) {
  //   cerr << e << ' ';
  // }
  // cerr << '\n';
  // cerr << '\n';
  // rep(i, 0, cc.size() - 1) { cerr << cc[i + 1] - cc[i] << ' '; }
  // cerr << '\n';
  // cerr << '\n';

  float ans = 2 * PI;
  rep(i, 0, cc.size() - 1) {
    if (ps[i] == 0) continue;
    // cerr << cc[i + 1] - cc[i] << ' ';
    ans -= cc[i + 1] - cc[i];
  }
  ans /= 2 * PI;
  cout << setprecision(14) << fixed << ans;
}