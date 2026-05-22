#pragma GCC optimize("trapv")
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
typedef vector<int> vi;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vc<string> cards(4 * 13);
  for (auto &e : cards) {
    cin >> e;
  }

  vc<string> stack;
  auto resolve = [&]() -> void {
    RESOLVE:
      for (int i = sz(stack) - 1; i - 3 >= 0; i--) {
        if (stack[i][0] == stack[i - 3][0]) {
          rep(j, 0, 3 + 1) { stack.erase(stack.begin() + i - j); }
          goto RESOLVE;
        }
      }
      for (int i = sz(stack) - 1; i - 3 >= 0; i--) {
        if (stack[i][1] == stack[i - 3][1]) {
          stack.erase(stack.begin() + i);
          stack.erase(stack.begin() + i - 3);
          goto RESOLVE;
        }
      }
  };
  for (auto e : cards) {
    stack.push_back(e);
    resolve();
  }
  cout << sz(stack);
  for (auto e : stack) {
    cout << ' ' << e;
  }
}