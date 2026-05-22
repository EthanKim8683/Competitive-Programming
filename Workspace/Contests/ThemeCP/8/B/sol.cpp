#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // for (int N = 1; N <= 100; N++) {
  //   int X = 0;
  //   for (int i = 1; i <= N; i++) {
  //     X ^= i;
  //   }

  //   cerr << N << ", " << X << ": ";
  //   int g = 0;
  //   for (int i = 1; i <= N; i++) {
  //     if (i == X) {
  //       g++;
  //     } else if ((i ^ X) <= N) {
  //       if (i < (i ^ X)) {
  //         g++;
  //       }
  //     } else {
  //       cerr << ' ' << i;
  //     }
  //   }
  //   cerr << endl;
  // }
  // if N is even, it's always possible to make at most N/2 groups
  // if N is odd, the unpaired numbers are always too small so the maximum
  // number of groups is the number of pairs

  int T;
  cin >> T;

  while (T--) {
    int N, K, X;
    cin >> N >> K >> X;

    int sum = 0;
    for (int i = 1; i <= N; i++) {
      sum ^= i;
    }
    if ((K % 2) * X != sum) {
      cout << "NO\n";
      continue;
    }

    vector<vector<int>> groups;
    vector<int> unpaired;
    for (int i = 1; i <= N; i++) {
      if (i == X) {
        groups.push_back({i});
      } else if ((i ^ X) <= N) {
        if (i < (i ^ X)) {
          groups.push_back({i, i ^ X});
        }
      } else {
        unpaired.push_back(i);
      }
    }
    if (K > groups.size()) {
      cout << "NO\n";
      continue;
    }

    vector<vector<int>> ans(K);
    for (int i = 0; i < groups.size(); i++) {
      for (auto j : groups[i]) {
        ans[min(i, K - 1)].push_back(j);
      }
    }
    for (auto i : unpaired) {
      ans[K - 1].push_back(i);
    }
    cout << "YES\n";
    for (auto r : ans) {
      cout << r.size();
      for (auto e : r) {
        cout << ' ' << e;
      }
      cout << '\n';
    }
  }
}
