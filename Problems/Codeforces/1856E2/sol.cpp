

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    int p;
    cin >> p;
    p--;
    adj[p].push_back(i);
  }
}
