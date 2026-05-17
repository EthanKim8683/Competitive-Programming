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

  // prefix sums. left and right parts. max of left
  //
  // pair max of left with first less in right
  //
  // index of the left
  //
  // get nth greatest
  //
  // number of them in right with enough greater than it before it to move to
  // left
  // - enough is min(# of greater before, M) > index in right
  // - enough is # of greater before > index in right and index in right < M
  //
  // # of greater before - index in right is non-increasing
  // first try querying top k elements in left and bottom k in right and
  // also query bottom k elements in entire range. Answer will be original
  // something ish(sum(left) - top k left + bottom k right, bottom(k) all)
  //
  // bottom k in right seems sus to me cuz its not the bottom k that move its
  // the leftmost k that move
  //
  // ok but the leftmost k that move is independent of the left (assuming k do
  // actually move) counterexample? im saying that if k elements move from the
  // right to the left, we don't care what the left looks like. Only that k
  // moved
  //
  // oh yeah sureso th
  //
  // do u actually type esc+o every time u want new line? no i just press enter
  //
  //
  //
  //
  //
  //
  //	Q log^3 n is to binary search on the length of the prefix of right that
  // gets replaced 	wait was this your og log^3? using persistent seg tree
  // makes this Q log^2? right
  //
  // tbh ive only ever used persistent segtree like twice ok but am i wrong
  // buddy
  //
  // idk how to use persistent segtree
  // add elements in order to a boolean seg tree (1 or 0 at each point if
  // added), to query number of elements in some range <= X, we take the seg
  // tree at time X, and do a range query to see number of elements added
  //
  //
  //
  //
  // why do u need persistent segtree thsts just like fenwick or sum shit,
  // because we're going back and forth in time a lot when doing the binary
  // search.
  //
  // dumfuck thats just parallel binary search its piss easy
  //
  // i think like 99% of the time when ppl say persistent segtree theres just
  // like many ways to avoid it with shorter/better/faster code
  //
  // i said 99% bruh
  //
  // plus this problem is just shit
  //
  // can u also not just merge sort tree???
  //
  // each element is added and removed at most once, yes?
  //
  // imagine the contribution of each element to all times e.g. an element that
  // appears at time 2 and leaves at time 5 is like
  //
  // 00111000...
  //
  // if we look at the prefix sums
  //
  // 00100000...
  // 00000-100...
  //
  // basically just have two merge sort trees: one for when it gets added and
  // one for when it gets removed
  //
  // u can even extend this to any amount of insertions and deletions
  // range insertions? do u really want to implement a lazy persistent segtree
  //
  // lazy persis seg tree is not bad right? It's just probably an additional log
  // space complexity.
  //
  // if we ever see lazy persistent segtree ill make manu implement it
  // i lowkey would be pretty ghood cause last year i only used the kactl fat
  // fuck lazy seg tree which is basicallly identical to persistent seg tree
  // except for saving so we're good
  //
  // persistent seg tree is log factor no? it is but like bad constant
  // merge sort tree log^2 is no way faster than well written persistent seg
  // tree index based instead of pointer based
  //
  // i feel like merge sort tree is faster in practice
  //
  // like map vs. hash map
  //
  // much much shorter code
  //
  // it's not that bad imo, ok but it's not like persistent seg tree is 100000
  // lines
  //
  //
  // but like persistent seg tree is way easier its so natural here it's so
  // fucking obvious here and plus if you changed how S works, it would
  // definitely be the only way
  //
  // but S works this way so get fugged
  //
  // also theres almost always a way. persistent segtree just sucks. its slow,
  // its long, its memory inefficient, etc.
  //
  // way shorter code
  //
  //	Q is a little smaller than N actually (5e5)
  //
  //
  // so strong
  //
  // lfg :)
  //
  // tf why its working now :skull:
  //
  // vim different modes, so right now we're in insert mode so we can insert
  // stuff
  //
  // but that was normal mode where u can do like shortcuts?? kind of
  //
  //
  // but that was normal mode where u can do like shortcuts?? kind of
  //
  // but that was normal mode where u can do like shortcuts?? kind of
  //
  // 5 6 | 3 4 1 2
  // ... after 2 ops ...
  // 3 4 | 1 2 5 6

  int N, Q;
  cin >> N >> Q;
  cout << N + Q << endl;

  return 0;  // Now we have an ~170 lines A+B problem solve :)
}
