#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    // if it's all alternating, there's nothing we can do
    //
    // otherwise, even-length contiguous subarrays can be merged with their
    // neighbors, so we're only looking at the odd-length ones
    //
    // odd-length subarrays can't be merged away, so there will always be a
    // single bracket maintaining the original direction
    //
    // this might be enough to solve the problem already?

    vector<pair<char, int>> stack;
    for (auto e : S) {
      if (stack.empty() or stack.back().first != e) {
        stack.push_back({e, 0});
      }
      stack.back().second++;
      while (stack.back().second % 2 == 0 and stack.size() > 1) {
        int length = stack.back().second;
        stack.pop_back();
        stack.back().second += length;
      }
    }
    vector<char> singles;
    int doubles = 0;
    for (auto [c, length] : stack) {
      if (length % 2 == 1) {
        singles.push_back(c);
      }
      doubles += length / 2;
    }

    if (singles.size() % 2 == 1 or doubles % 2 == 1) {
      cout << -1 << '\n';
      continue;
    }

    if (doubles == 0) {
      if (singles[0] == ')') {
        cout << -1 << '\n';
        continue;
      }

      for (auto e : singles) {
        cout << e;
      }
      cout << '\n';
    } else {
      for (int i = 0; i < doubles / 2; i++) {
        cout << "((";
      }
      for (auto e : singles) {
        cout << e;
      }
      for (int i = 0; i < doubles / 2; i++) {
        cout << "))";
      }
      cout << '\n';
    }
  }
}