#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  string S;
  cin >> S;

  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i; j < N; j++) {
      int diff = 4 * count(S.begin() + i, S.begin() + j + 1, '1') - (j + 1 - i);
      bool adj_equal = false;
      for (int k = i; k < j; k++) {
        if (S[k] == '1' and S[k + 1] == '1') {
          adj_equal = true;
          break;
        }
      }
      if (diff < -1 or (diff == 1 and !adj_equal)) {
        cerr << i << ' ' << j << endl;
        ans++;
      }
    }
  }
  cout << ans;
}