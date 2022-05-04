#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

const int N = 1e5;

map<int, int> x_map;
int x_arr[N];
int pars[N];
int res[N];
int dp[N];

int main(void) {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    x_arr[i] = x;
    x_map[x] = i;
  }
  fill_n(dp, n, 1);
  for (int i = 0; i < n; i++) {
    const auto x = x_arr[i];
    x_map.erase(x);
    const auto it = x_map.upper_bound(x);
    if (it != x_map.end()) {
      const auto j = it->second;
      if (dp[i] + 1 > dp[j]) {
        dp[j] = dp[i] + 1;
        pars[j] = i;
      }
    }
    const int j = i + 1;
    if (j < n && x_arr[j] > x) {
      if (dp[i] + 1 > dp[j]) {
        dp[j] = dp[i] + 1;
        pars[j] = i;
      }
    }
  }
  int cnt = 0;
  int cur;
  for (int i = 0; i < n; i++) {
    if (dp[i] > cnt) {
      cnt = dp[i];
      cur = i;
    }
  }
  for (int i = cnt - 1; i >= 0; i--) {
    res[i] = x_arr[cur];
    cur = pars[cur];
  }
  cout << cnt << '\n';
  for (int i = 0; i < cnt; i++)
    cout << res[i] << ' ';
  cout << '\n';
  return 0;
}