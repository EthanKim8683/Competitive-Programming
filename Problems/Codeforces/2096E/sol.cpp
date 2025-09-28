#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  auto to_mask = [&](string s) -> int {
    int mask = 0;
    for (int i = 0; i < s.size(); i++) {
      mask |= (s[i] == 'B') << i;
    }
    return mask;
  };

  auto solve = [&](int B, int P) -> vector<int> {
    int N = B + P;

    auto from_mask = [&](int mask) -> string {
      string s = "";
      for (int i = 0; i < N; i++) {
        s += mask >> i & 1 ? 'B' : 'P';
      }
      return s;
    };

    vector<int> dist(1 << N, INF);
    queue<int> q;
    auto push = [&](int mask, int d) -> void {
      if (d >= dist[mask]) return;
      dist[mask] = d;
      q.push(mask);
    };
    push(to_mask(string(B, 'B') + string(P, 'P')), 0);
    while (q.size() > 0) {
      int mask = q.front();
      q.pop();
      string s = from_mask(mask);

      for (int i = 0; i + 3 <= N; i++) {
        string t = s.substr(i, 3);
        if (!is_sorted(t.begin(), t.end())) continue;

        do {
          push(to_mask(s.substr(0, i) + t + s.substr(i + 3)), dist[mask] + 1);
        } while (next_permutation(t.begin(), t.end()));
      }
    }
    return dist;
  };

  auto solve_and_print = [&](int B, int P, vector<string> queries) -> void {
    auto dist = solve(B, P);

    cout << B << " B's, " << P << " P's" << '\n';
    for (auto q : queries) {
      if (count(q.begin(), q.end(), 'B') != B or
          count(q.begin(), q.end(), 'P') != P)
        continue;

      cout << "  " << q << ": " << dist[to_mask(q)] << '\n';
    }
  };

  solve_and_print(4, 4, {"PPBBBBPP", "BBPPPPBB"});

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    // it takes ceil(P * B / 2) instructions to sort string(P, 'P') + string(B,
    // 'B')
    //
    // what matters is parities of subsegment lengths
    //
    // looked at solution
    // I just need to try things
  }
}