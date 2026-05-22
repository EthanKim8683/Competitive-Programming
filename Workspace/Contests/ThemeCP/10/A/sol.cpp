#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<int> B(N);
    for (auto &e : B) cin >> e;

    vector<bool> ok(N, false);
    deque<int> dq;
    auto work = [&](int i) -> void {
      while (dq.size() > 0 and dq.back() <= A[i]) {
        dq.pop_back();
      }
      dq.push_back(A[i]);
      while (dq.size() > 0 and dq.front() > B[i]) {
        dq.pop_front();
      }
      if (dq.size() > 0 and dq.front() == B[i]) {
        ok[i] = true;
      }
    };
    for (int i = N - 1; i >= 0; i--) {
      work(i);
    }
    dq.clear();
    for (int i = 0; i < N; i++) {
      work(i);
    }
    bool ans = true;
    for (auto e : ok) {
      ans = ans and e;
    }
    cout << (ans ? "YES" : "NO") << '\n';
  }
}
