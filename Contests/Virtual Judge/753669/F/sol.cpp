#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<string> S(N);
  for (auto &e : S) cin >> e;

  string T;
  cin >> T;

  vector<string> layers(T.size());
  for (auto r : S) {
    int i = 0;
    string r_ = "";
    for (auto e : r) {
      if (i < T.size() and e == T[i]) {
        layers[i] += r_;
        r_ = "";
        i++;
      } else {
        r_ += e;
      }
    }
    if (i == T.size()) {
      cout << "NO";
      exit(0);
    }
    layers[i] += r_;
  }
  cout << "YES\n";
  for (int i = 0; i < T.size(); i++) {
    cout << layers[i];
    if (i < T.size() - 1) {
      cout << T[i];
    }
  }
}