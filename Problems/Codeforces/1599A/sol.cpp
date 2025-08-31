#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if defined(ETHANKIM8683) and true
  mt19937 rng(time(nullptr));

  int N = 2e5;

  vector<int> A(N);
  set<int> _seen;
  for (auto &e : A) {
    do {
      e = rng() % (int) 1e9 + 1;
    } while (_seen.contains(e));
    _seen.insert(e);
  }

  string S = "";
  for (int i = 0; i < N; i++) {
    S += "LR"[rng() % 2];
  }
#else
  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  string S;
  cin >> S;
#endif

  auto answer = [&](vector<pair<int, char>> ans) -> void {
#if defined(ETHANKIM8683) and true
    vector<int> A_ = A, B_;
    int x = 0;
    bool ok = true;
    for (int i = 0; i < N; i++) {
      auto [dx, d] = ans[i];
      x += dx * (d == 'L' ? -1 : 1);
      B_.push_back(dx);
      ok = ok and "LR"[x > 0] == S[i];
    }
    sort(A_.begin(), A_.end());
    sort(B_.begin(), B_.end());
    ok = ok and equal(A_.begin(), A_.end(), B_.begin());
    cerr << (ok ? "ok" : "wa") << '\n';
#else
    for (auto [dx, d] : ans) {
      cout << dx << ' ' << d << '\n';
    }
#endif
  };

  vector<int> S_;
  for (auto e : S) {
    S_.push_back(e == 'L' ? -1 : 1);
  }

  int l = 0, r = 0;
  vector<pair<int, int>> ans;
  for (int i = 0; i < N;) {
    if (i + 2 <= N) {
      if ((i - 1 >= 0 ? S_[i - 1] : 0) == S_[i]) {
        if (S_[i] == S_[i + 1]) {
          ans.push_back({r + 1, S_[i]});
          ans.push_back({r, -S_[i]});
          r += 2;
        } else {
          ans.push_back({l - 1, S_[i]});
          ans.push_back({r, -S_[i]});
          l -= 1, r += 1;
        }
      } else {
        if (S_[i] == S_[i + 1]) {
          ans.push_back({r, S_[i]});
          ans.push_back({l - 1, -S_[i]});
          r += 1, l -= 1;
        } else {
          ans.push_back({r, S_[i]});
          ans.push_back({r + 1, -S_[i]});
          r += 2;
        }
      }
      i += 2;
    } else {
      ans.push_back({r, S_[i]});
      r += 1, i += 1;
    }
  }

  sort(A.begin(), A.end());
  vector<pair<int, char>> ans_;
  for (auto [i, s] : ans) {
    ans_.push_back({A[i - l], "LR"[s > 0]});
  }

  answer(ans_);
}
