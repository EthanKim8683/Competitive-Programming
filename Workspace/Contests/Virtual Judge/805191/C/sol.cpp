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

  // 5 elements in a row dec or inc
  //
  // left or right are not equal
  //
  // if inc and prev > min, choose min
  //
  // if dec and prev < max, choose max
  //
  // if inc and prev < min, choose max
  //
  // if dec and prev > max, choose min

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi P(N);
    for (auto &e : P) cin >> e;

    bool inc = false;
    int prev = -1, l = 0, r = N - 1;
    vi A;
    rep(i, 0, N) {
      pii optmin = min(pii{P[l], 0}, pii{P[r], 1}),
          optmax = max(pii{P[l], 0}, pii{P[r], 1});
      int choice;
      if (inc) {
        if (prev > optmin.fs) {
          choice = optmin.sd;
        } else {
          choice = optmax.sd;
        }
      } else {
        if (prev < optmax.fs) {
          choice = optmax.sd;
        } else {
          choice = optmin.sd;
        }
      }
      cout << "LR"[choice];
      if (choice == 0) {
        inc = prev < P[l];
        prev = P[l];
        l++;
      } else {
        inc = prev < P[r];
        prev = P[r];
        r--;
      }
      A.pb(prev);
    }
    cout << '\n';
    // rep(i, 0, N - 4) {
    //   bool inc = true;
    //   rep(j, i, i + 4) { inc = inc and A[j] < A[j + 1]; }
    //   bool dec = true;
    //   rep(j, i, i + 4) { dec = dec and A[j] > A[j + 1]; }
    //   assert(!(inc or dec));
    // }
  }
}
