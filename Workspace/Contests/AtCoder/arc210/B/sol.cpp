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

  // does order matter? no
  //
  // remove middle M

  int N, M, Q;
  cin >> N >> M >> Q;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi B(M);
  for (auto &e : B) cin >> e;

  vc<tuple<int, int, int>> queries(Q);
  for (auto &[t, i, x] : queries) {
    cin >> t >> i >> x;
    i--;
  }

  int sum = 0;
  multiset<int> lt, medians, gt;
  for (auto e : A) {
    sum += e;
    lt.insert(e);
  }
  for (auto e : B) {
    sum += e;
    lt.insert(e);
  }
  auto resolve = [&]() -> void {
    while (sz(lt) > N / 2) {
      auto it = prev(lt.end());
      sum -= *it;
      medians.insert(*it);
      lt.erase(it);
    }
    while (sz(medians) > M) {
      auto it = prev(medians.end());
      sum += *it;
      gt.insert(*it);
      medians.erase(it);
    }
    while (sz(gt) > N / 2) {
      auto it = gt.begin();
      sum -= *it;
      medians.insert(*it);
      gt.erase(it);
    }
    while (sz(medians) > M) {
      auto it = medians.begin();
      sum += *it;
      lt.insert(*it);
      medians.erase(it);
    }
  };
  resolve();
  for (auto [t, i, x] : queries) {
    medians.insert(x);
    resolve();
    int &e = t == 1 ? A[i] : B[i];
    if (lt.contains(e)) {
      sum -= e;
      lt.erase(lt.find(e));
    } else if (medians.contains(e)) {
      medians.erase(medians.find(e));
    } else {
      sum -= e;
      gt.erase(gt.find(e));
    }
    resolve();
    e = x;
    cout << sum << '\n';
  }
}
