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

const float LARGE = 1e4;
const float INF = 1e300;
const float EPSILON = 1e-7;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  auto dot = [&](vec dA, vec dB) -> float {
    auto [dx1, dy1] = dA;
    auto [dx2, dy2] = dB;
    return dx1 * dx2 + dy1 * dy2;
  };

  auto add = [&](vec dA, vec dB) -> vec {
    auto [dx1, dy1] = dA;
    auto [dx2, dy2] = dB;
    return {dx1 + dx2, dy1 + dy2};
  };

  auto delta = [&](vec A, vec B) -> vec {
    auto [x1, y1] = A;
    auto [x2, y2] = B;
    return {x2 - x1, y2 - y1};
  };

  auto mul = [&](float c, vec dA) -> vec {
    auto [dx, dy] = dA;
    return {c * dx, c * dy};
  };

  auto proj = [&](vec dA, vec dB) -> vec {
    float c = dot(dA, dB) / dot(dB, dB);
    auto [dx, dy] = dB;
    return {dx * c, dy * c};
  };

  auto perp = [&](vec dA) -> vec {
    auto [dx, dy] = dA;
    return {dy, -dx};
  };

  auto flip = [&](vec dA) -> vec {
    auto [dx, dy] = dA;
    return {-dx, -dy};
  };

  auto len = [&](vec dA) -> float { return sqrt(dot(dA, dA)); };

  auto dist = [&](vec A, vec B) -> float { return len(delta(A, B)); };

  auto norm = [&](vec dA) -> vec {
    float f = 1 / len(dA);
    auto [dx, dy] = dA;
    return {dx * f, dy * f};
  };

  auto str = [&](vec A) -> string {
    auto [x, y] = A;
    return "(" + to_string(x) + ", " + to_string(y) + ")";
  };

  auto isect = [&](vec A, vec dA, vec B, vec dB) -> vec {
    auto coef = [&](vec A, vec dA) -> tuple<float, float, float> {
      auto [x0, y0] = A;
      auto [dx, dy] = dA;
      return {dy, -dx, dy * x0 - dx * y0};
    };
    auto [a, b, e] = coef(A, dA);
    auto [c, d, f] = coef(B, dB);
    return {(e * d - b * f) / (a * d - b * c),
            (c * e - a * f) / (b * c - a * d)};
  };

  auto weight = [&](vec dA, vec dB) -> float {
    auto [dx1, dy1] = dA;
    auto [dx2, dy2] = dB;
    return abs(dx2) > abs(dy2) ? dx1 / dx2 : dy1 / dy2;
  };

  auto hit = [&](vec A, vec dA, vec B, vec C) -> pair<bool, vec> {
    vec D = isect(A, dA, B, delta(B, C));
    float w = weight(delta(B, D), delta(B, C));
    if (w < 0 or 1 < w) return {false, {}};
    return {true, D};
  };

  auto reflect = [&](vec dA, vec dB) -> vec {
    return add(proj(dA, dB), flip(proj(dA, perp(dB))));
  };

  int W, H, N, M;
  float L;
  int R, S;
  cin >> W >> H >> N >> M >> L >> R >> S;

  vc<tuple<vec, vec, int>> lines;
  lines.pb({{0, 0}, {0, H}, -1});
  lines.pb({{W, 0}, {W, H}, -1});
  lines.pb({{0, H}, {W, H}, -1});

  vc<int> values(M);
  rep(i, 0, M) {
    int P;
    cin >> P;

    vc<vec> points(P);
    for (auto &[x, y] : points) {
      cin >> x >> y;
    }

    cin >> values[i];

    rep(j, 0, P) { lines.pb({points[j], points[(j + 1) % P], i}); }
  }

  priority_queue<tuple<float, vec, vec, int>> pq1;
  priority_queue<pair<float, int>> pq2;
  auto shoot = [&](float t, vec A, vec dA) -> void {
    dA = norm(dA);

    pair<float, int> nearest = {INF, -1};
    rep(i, 0, sz(lines)) {
      auto [B, C, j] = lines[i];
      if (j != -1 and values[j] == 0) continue;
      auto [ok, D] = hit(A, dA, B, C);
      if (!ok) continue;
      if (dist(A, D) <= EPSILON) continue;
      if (dot(dA, delta(A, D)) <= 0) continue;
      nearest = min(nearest, {dist(A, D), i});
    }
    auto [d, i] = nearest;
    if (i == -1) return;

    auto [B, C, j] = lines[i];
    auto [ok, D] = hit(A, dA, B, C);
    assert(ok);
    pq1.push({-(t + d), D, dA, i});
    if (j != -1) {
      pq2.push({-(t + d), j});
    }
  };

  auto dec = [&](float t1) -> void {
    while (pq2.size() > 0) {
      auto [t2, j] = pq2.top();
      t2 = -t2;
      if (t2 > t1) break;
      pq2.pop();
      if (values[j] > 0) {
        values[j]--;
      }
    }
  };

  rep(t, 0, N) { shoot(t, {L, 0}, {R, S}); }
  while (pq1.size() > 0) {
    auto [t, A, dA, i] = pq1.top();
    pq1.pop();
    t = -t;

    dec(t);
    auto [B, C, j] = lines[i];
    if (j == -1 or values[j] > 0) {
      dA = reflect(dA, delta(B, C));
    }
    shoot(t, A, dA);
  }
  dec(INF);

  for (auto e : values) {
    cout << e << ' ';
  }
}