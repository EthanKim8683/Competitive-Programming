#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> intervals1(M);
    for (auto &[l, r] : intervals1) {
      cin >> l >> r;
      l--;
    }

    vector<bool> is_in(N, false);
    for (auto [l, r] : intervals1) {
      for (int i = l; i < r; i++) {
        is_in[i] = true;
      }
    }

    vector<bool> is_left(N, false), is_right(N, false);
    vector<pair<int, int>> intervals2;
    bool ok = true;
    for (auto [l1, r1] : intervals1) {
      int l2max = l1, r2min = r1;
      for (auto [l2, r2] : intervals1) {
        if (l2 < r1) {
          l2max = max(l2max, l2);
        }
        if (r2 > l1) {
          r2min = min(r2min, r2);
        }
      }

      for (int i = l1; i < l2max; i++) {
        is_left[i] = true;
      }
      for (int i = r2min; i < r1; i++) {
        is_right[i] = true;
      }
      intervals2.emplace_back(l2max, r2min);
    }
    sort(intervals2.begin(), intervals2.end());
    intervals2.erase(unique(intervals2.begin(), intervals2.end()),
                     intervals2.end());
    for (int i = 0; i < N; i++) {
      ok = ok and !(is_left[i] and is_right[i]);
    }
    for (auto [l, r] : intervals2) {
      ok = ok and r - l >= 2;
      for (int i = l; i < r; i++) {
        ok = ok and !(is_left[i] or is_right[i]);
      }
    }
    if (!ok) {
      cout << "-1\n";
      continue;
    }

    vector<int> deltas;
    reverse(intervals2.begin(), intervals2.end());
    for (auto [l, r] : intervals2) {
      is_left[l] = true;
      is_right[r - 1] = true;
      for (int i = l + 1; i < r - 1; i++) {
        is_right[i] = true;
        deltas.push_back(i);
      }
    }

    auto count = [&]() -> int {
      vector<int> ps1(N + 1), ps2(N + 1), ps3(N + 1), ps4(N + 1);
      int l = 0, r = 0;
      for (int i = 0; i < N; i++) {
        if (is_left[i]) {
          ps1[i + 1] = i;
        } else {
          ps1[i + 1] = l;
          l++;
        }

        if (is_right[i]) {
          ps2[i + 1] = r;
          r++;
          ps3[i + 1] = 1;
        } else {
          ps2[i + 1] = i;
        }

        if (!is_in[i]) {
          ps4[i + 1] = 1;
        }

        ps1[i + 1] += ps1[i];
        ps2[i + 1] += ps2[i];
        ps3[i + 1] += ps3[i];
        ps4[i + 1] += ps4[i];
      }

      int rv = 0;
      for (int i = 0; i <= N; i++) {
        rv = max(rv, ps1[i] - ps1[0] + ps2[N] - ps2[i] +
                         (ps4[i] - ps4[0]) * (ps3[N] - ps3[i]));
      }
      return rv;
    };
    int ans = count();
    for (auto e : deltas) {
      is_right[e] = false;
      is_left[e] = true;
      ans = max(ans, count());
    }
    cout << ans << '\n';
  }
}
