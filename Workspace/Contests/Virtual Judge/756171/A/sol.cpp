#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<bool> V(N);
  for (int i = 0; i < N; i++) {
    string val;
    cin >> val;
    V[i] = val == "T";
  }

  vector<bool> stack;
  string exp;
  while (cin >> exp) {
    char exp0 = exp[0];
    if ('A' <= exp0 and exp0 <= 'Z') {
      stack.push_back(V[exp0 - 'A']);
    } else if (exp0 == '*') {
      bool back1 = stack.back();
      stack.pop_back();
      bool back2 = stack.back();
      stack.pop_back();
      stack.push_back(back1 and back2);
    } else if (exp0 == '+') {
      bool back1 = stack.back();
      stack.pop_back();
      bool back2 = stack.back();
      stack.pop_back();
      stack.push_back(back1 or back2);
    } else if (exp0 == '-') {
      bool back = stack.back();
      stack.pop_back();
      stack.push_back(!back);
    }
  }
  cout << "FT"[stack.back()];
}