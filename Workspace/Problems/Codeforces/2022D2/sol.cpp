#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // I wonder if the first testcase's solution would've been shown in-contest.

#ifdef ETHANKIM8683
  mt19937 rng(time(nullptr));

  int T = 100;
  while (T--) {
    int N = 7;

    vector<int> A(N);
    for (auto &e : A) {
      e = rng() % 2;
    }
    A[rng() % N] = 2;

    int Q = 0;
    auto query = [&](int i, int j) -> bool {
      Q++;
      return (int[3][3]) {{1, 0, 1}, {0, 1, 0}, {0, 1}}[A[i]][A[j]];
    };

    auto answer = [&](int i) -> void {
      cerr << (A[i] == 2 ? "ok" : "wa") << " (" << Q << ")\n";
    };
#else
  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;
    if (N == -1) exit(0);

    auto query = [&](int i, int j) -> bool {
      cout << "? " << i + 1 << ' ' << j + 1 << endl;
      int rv;
      cin >> rv;
      if (rv == -1) exit(0);
      return rv;
    };

    auto answer = [&](int i) -> void { cout << "! " << i + 1 << endl; };
#endif

    auto solve = [&](auto self, int n) -> void {
      if (n == 5) {
        int q01 = query(0, 1), q12 = query(1, 2), q20 = query(2, 0),
            q20_ = !(q01 ^ q12);
        if (q20 != q20_) {
          answer(q01 == query(1, 0) ? 2 : q12 == query(2, 1) ? 0 : 1);
        } else {
          answer(query(3, 0) != query(0, 3) ? 3 : 4);
        }
        return;
      }
      if (n == 3) {
        answer(query(0, 1) == query(1, 0)   ? 2
               : query(2, 1) == query(1, 2) ? 0
                                            : 1);
        return;
      }
      if (n == 2) {
        answer(query(0, 2) != query(2, 0) ? 0 : 1);
        return;
      }

      if (query(n - 2, n - 1) != query(n - 1, n - 2)) {
        answer(query(n - 1, 0) != query(0, n - 1) ? n - 1 : n - 2);
        return;
      }
      self(self, n - 2);
    };
    solve(solve, N);
  }
}
