#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, K;
  cin >> N >> M >> K;

  vector<vector<int>> workers(N);
  for (auto &r : workers) {
    int T;
    cin >> T;

    r.resize(T);
    for (auto &e : r) {
      string Day;
      cin >> Day;
      string days[] = {"Monday", "Tuesday",  "Wednesday", "Thursday",
                       "Friday", "Saturday", "Sunday"};
      e = find(begin(days), end(days), Day) - begin(days);
    }
  }

  vector<int> H(M);
  for (auto &e : H) {
    cin >> e;
    e--;
  }

  vector<vector<int>> projects(K);
  for (auto &r : projects) {
    int P;
    cin >> P;

    r.resize(P);
    for (auto &e : r) {
      cin >> e;
      e--;
    }
  }
}