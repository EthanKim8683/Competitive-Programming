#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string S;
  cin >> S;

  vector<char> st;
  for (auto e : S) {
    auto check = [&](char c) -> void {
      if (st.empty() or st.back() != c) {
        cout << "No";
        exit(0);
      }
      st.pop_back();
    };

    if (e == ')') {
      check('(');
    } else if (e == ']') {
      check('[');
    } else if (e == '>') {
      check('<');
    } else {
      st.push_back(e);
    }
  }
  cout << (st.empty() ? "Yes" : "No");
}
