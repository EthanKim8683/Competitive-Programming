#include <bits/stdc++.h>

using namespace std;

const int K = 317;
const int MAXN = 1e5;
const int MAXA = 1e9;
const int MAXW = 1e9;
const int INF = 2e9 + 1;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N, M;
  if (argc > 1) {
    N = 1e5;
    M = 5;
  } else {
    cin >> N >> M;
  }

  vector A(N, vector<int>(M));
  vector<int> W(N);
  if (argc > 1) {
    for (auto &r : A) {
      // for (auto &e : r) {
      //   e = rng() % MAXA + 1;
      // }
      iota(r.begin(), r.end(), 1);
    }
    for (auto &e : W) {
      e = rng() % MAXW + 1;
    }
  } else {
    for (int i = 0; i < N; i++) {
      for (auto &e : A[i]) cin >> e;
      cin >> W[i];
    }
  }

  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(),
       [&](int a, int b) -> bool { return W[a] < W[b]; });

  vector<int> index(N);
  for (int i = 0; i < N; i++) {
    index[order[i]] = i;
  }

  vector<int> cc;
  for (auto r : A) {
    cc.insert(cc.end(), r.begin(), r.end());
  }
  sort(cc.begin(), cc.end());
  for (auto &r : A) {
    for (auto &e : r) {
      e = lower_bound(cc.begin(), cc.end(), e) - cc.begin();
    }
  }

  vector<vector<int>> indices(cc.size());
  for (int i = 0; i < N; i++) {
    for (auto e : A[i]) {
      indices[e].push_back(index[i]);
    }
  }

  vector<bitset<MAXN>> excludes;
  vector<int> excluder(cc.size(), -1);
  for (int i = 0; i < cc.size(); i++) {
    if (indices[i].size() <= K) continue;
    bitset<MAXN> exclude;
    exclude.set();
    for (auto e : indices[i]) {
      exclude.reset(e);
    }
    excluder[i] = excludes.size();
    excludes.push_back(exclude);
  }

  int ans = INF;
  for (int i = 0; i < N; i++) {
    bitset<MAXN> exclude;
    exclude.set();
    for (auto e : A[i]) {
      if (excluder[e] != -1) {
        exclude &= excludes[excluder[e]];
      } else {
        for (auto j : indices[e]) {
          exclude.reset(j);
        }
      }
    }

    int j = exclude._Find_first();
    if (j < N) {
      ans = min(ans, W[i] + W[order[j]]);
    }
  }
  cout << (ans == INF ? -1 : ans) << '\n';
}
