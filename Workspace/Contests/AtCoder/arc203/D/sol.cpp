#include <bits/stdc++.h>

#include "atcoder/segtree"

using namespace std;
using namespace atcoder;

struct segment {
  bool has_one, has_zero;
  int start_zeros, end_zeros, zeros_ge_2_count;
};

segment op(segment a, segment b) {
  bool has_one = a.has_one or b.has_one, has_zero = a.has_zero or b.has_zero;
  int start_zeros = a.start_zeros, end_zeros = b.end_zeros,
      zeros_ge_2_count = a.zeros_ge_2_count + b.zeros_ge_2_count;
  if (!a.has_one) {
    start_zeros += b.start_zeros;
  }
  if (!b.has_one) {
    end_zeros += a.end_zeros;
  }
  if (a.has_one and b.has_one) {
    if (a.end_zeros + b.start_zeros >= 2) {
      zeros_ge_2_count += 1;
    }
  }
  return {has_one, has_zero, start_zeros, end_zeros, zeros_ge_2_count};
}

segment e() { return {false, false, 0, 0, 0}; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  segtree<segment, op, e> st(N);
  auto update = [&](int i) -> void {
    if (A[i] == 1) {
      st.set(i, {true, false, 0, 0, 0});
    } else {
      st.set(i, {false, true, 1, 1, 0});
    }
  };
  for (int i = 0; i < N; i++) {
    update(i);
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int I;
    cin >> I;
    I--;
    A[I] ^= 1;
    update(I);

    auto s = st.all_prod();
    if (!s.has_zero) {
      cout << N << '\n';
      continue;
    }

    if (s.zeros_ge_2_count == 0 and s.start_zeros == 0 and s.end_zeros == 0) {
      cout << 2 << '\n';
      continue;
    }

    int ans = 2 * s.zeros_ge_2_count;
    if (s.has_one) {
      ans += 1 + s.zeros_ge_2_count;
      ans += min(s.start_zeros, 2);
    }
    ans += min(s.end_zeros, 2);
    cout << ans << '\n';
  }
}