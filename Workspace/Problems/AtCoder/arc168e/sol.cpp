#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  i64 S;
  cin >> N >> K >> S;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  // The constraint comes from when we can't make K subsequences with sum at
  // least S. Some subsequences would need to be split to meet the K subsequence
  // quota.
  //
  // Update: I looked at the editorial. It uses something called Alien DP. I'll
  // have to learn that first before re-attempting this problem.
}
