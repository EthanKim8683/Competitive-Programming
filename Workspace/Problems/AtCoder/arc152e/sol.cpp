#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> W((1 << N) - 1);
  for (auto &e : W) cin >> e;

  // After merging, the smaller xor of both balls remain on opposite ends, and
  // the combined ball goes away from the smallest xor. If we imagine one L and
  // one R some distance away, if there's an L' or R' between them smaller than
  // both of them, this L' or R' will inevitably push them apart. Thus, we want
  // all prefix and suffix xors to be no less than Z.

  vector<array<int, 2>> trie(1 << (N + 1), {-1, -1});
  int t = 1;
  auto insert = [&](int x) -> void {
    int a = 0;
    for (int i = N - 1; i >= 0; i--) {
      int &b = trie[a][x >> i & 1];
      if (b == -1) {
        b = t++;
      }
      a = b;
    }
  };
  auto query = [&](int x) -> bool {
    int a = 0;
    for (int i = N - 1; i >= 0; i--) {
      if (x >> i & 1 and trie[a][1] != -1) {
        return false;
      }
      a = trie[a][0];
    }
    return true;
  };
  int ps = 0;
  for (int i = 0; i < (1 << N) - 1; i++) {
    insert(ps);
    ps ^= W[i];
  }
  insert(ps);
  ps = 0;
  for (int i = (1 << N) - 2; i >= 0; i--) {
    insert(ps);
    ps ^= W[i];
  }
  insert(ps);

  int ans = 0;
  for (int i = 0; i < (1 << N); i++) {
    if (query(i)) {
      ans++;
    }
  }
  cout << ans;
}
