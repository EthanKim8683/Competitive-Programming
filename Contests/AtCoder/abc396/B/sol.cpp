#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int Q;
  cin >> Q;

  vector<int> stack(100, 0);
  while (Q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int x;
      cin >> x;

      stack.push_back(x);
    } else {
      cout << stack.back() << '\n';
      stack.pop_back();
    }
  }
}
