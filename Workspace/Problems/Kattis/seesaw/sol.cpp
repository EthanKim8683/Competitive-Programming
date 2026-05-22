#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 6:33
  // thinking done: 6:40
  // target impl time: 20 min
  // initial impl done: 7:14

  int N;
  cin >> N;

  vc<pii> people(N);
  for (auto &[p, w] : people) {
    cin >> p >> w;
  }

  int t = 0;
  for (auto [p, w] : people) {
    t += p * w;
  }
  if (t < 0) {
    for (auto &[p, w] : people) {
      p = -p;
    }
    t = -t;
  }

  auto less = [&](pair<pii, int> a, pair<pii, int> b) -> bool {
    auto [w1, n1] = a.fs;
    auto [w2, n2] = b.fs;
    return w1 * n2 < w2 * n1;
  };
  priority_queue<pair<pii, int>, vc<pair<pii, int>>, decltype(less)> pq(less);
  map<int, pii> groups;
  auto nudge = [&](int p) -> void { pq.push({groups[p], p}); };

  int tnow = 0;
  double dnow = 0;
  for (auto [p, w] : people) {
    groups[p] = {w, 1};
    nudge(p);
  }
  while (pq.size() > 0) {
    auto [c, p] = pq.top();
    pq.pop();

    auto it = groups.find(p);
    if (it == groups.end()) continue;

    if (c != it->second) continue;
    auto [w, n] = c;

    if (next(it) == groups.end()) {
      dnow += (double) (t - tnow) * n / w;
      break;
    }

    int p2 = next(it)->first;
    groups.erase(it);

    if (t - tnow <= (p2 - p) * w) {
      dnow += (double) (t - tnow) * n / w;
      break;
    }

    tnow += (p2 - p) * w;
    dnow += (p2 - p) * n;

    auto &[w2, n2] = groups[p2];
    w2 += w;
    n2 += n;
    nudge(p2);
  }

  cout << setprecision(10) << fixed << dnow << '\n';
}
