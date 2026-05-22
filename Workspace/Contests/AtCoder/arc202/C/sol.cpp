#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

using mint = modint998244353;

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

const int MAXA = 2e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // read editorial
  //
  // i got the gcd(R(a), R(b)) = R(gcd(a, b)) part but i didn't know how to use
  // that
  //
  // how do i improve from this?
  //
  // i think what they did was they used a trick i'm calling the "inverse prefix
  // sum trick":
  //
  // basically we treat what we know as a prefix sum array of some auxiliary
  // array, and we can do this if what we know is partially ordered. more
  // specifically, the relation between any two elements yields a "delta", which
  // becomes an element in the auxiliary array
  //
  // this now relates by value everything related by the partial ordering
  //
  // so lcm is now just the union of elements of the auxiliary array here
  //
  // another problem that kind of uses this is:
  // https://atcoder.jp/contests/arc214/tasks/arc214_d
  //
  // basically they use this trick to ensure the bound i think. basically a neat
  // way of solving this problem is to assign ranges of scores the elements of
  // each diagonal and pick lower bounds for the scores of each of the ranges.
  // obviously the best lower bound is binomial apart and perfectly enumerates
  // the paths. since each adjacent pair of elements along a diagonal is
  // downstream from exactly one element in the previous diagonal, we can derive
  // the value of one element from the other using the value of the upstream
  // element and this auxiliary array.

  auto R = [&](int x) -> mint { return (mint(10).pow(x) - 1) / 9; };

  vc<vi> divisors(MAXA + 1);
  rep(i, 1, MAXA + 1) {
    for (int j = i; j <= MAXA; j += i) {
      divisors[j].pb(i);
    }
  }

  vc<mint> F(MAXA + 1);
  F[1] = 1;
  rep(i, 1, MAXA + 1) {
    F[i] = R(i);
    for (auto e : divisors[i]) {
      if (e == i) continue;
      F[i] /= F[e];
    }
  }

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  set<int> S;
  mint ans = 1;
  for (auto e : A) {
    for (auto e2 : divisors[e]) {
      if (S.contains(e2)) continue;
      S.insert(e2);
      ans *= F[e2];
    }
    cout << ans.val() << '\n';
  }
}
