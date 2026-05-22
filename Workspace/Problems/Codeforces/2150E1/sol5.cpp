#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng(time(nullptr)), rng2;
  if (argc > 1) {
    rng2 = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 400000 / (300 * 300);
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    if (argc > 1) {
      N = 300;
    } else {
      cin >> N;
      if (N == -1) exit(0);
    }

    vector<int> A;
    if (argc > 1) {
      for (int i = 1; i <= N; i++) {
        A.push_back(i);
        A.push_back(i);
      }
      shuffle(A.begin(), A.end(), rng2);
      A.pop_back();
    }

    int Q = 0;
    auto ask = [&](vector<int> S, int x) -> bool {
      if (argc > 1) {
        Q++;
        // assert(Q <= 925);

        for (auto e : S) {
          if (A[e] == x) return true;
        }
        return false;
      } else {
        cout << "? " << x << ' ' << S.size();
        for (auto e : S) {
          cout << ' ' << e + 1;
        }
        cout << endl;
        int res;
        cin >> res;
        if (res == -1) exit(0);
        return res == 1;
      }
    };

    auto answer = [&](int y) -> void {
      if (argc > 1) {
        cerr << Q << '\n';
        // assert(count(A.begin(), A.end(), y) == 1);
      } else {
        cout << "! " << y << endl;
      }
    };

    vector<int> X(N);
    iota(X.begin(), X.end(), 1);
    shuffle(X.begin(), X.end(), rng);
    for (auto e : X) {
      vector<int> S(2 * N - 1);
      iota(S.begin(), S.end(), 0);

      bool found = false;
      while (S.size() > 1) {
        shuffle(S.begin(), S.end(), rng);
        auto it = S.begin() + S.size() / 2;
        vector<int> S1(S.begin(), it), S2(it, S.end());

        if (!ask(S1, e)) {
          S = S2;
        } else if (!ask(S2, e)) {
          S = S1;
        } else {
          found = true;
          break;
        }
      }
      if (!found) {
        answer(e);
        break;
      }
    }
  }
}
