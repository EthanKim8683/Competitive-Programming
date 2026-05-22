#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // each bit has rows and columns that need updating
  // pair xor's between rows and columns
  // number of 1's, 2's and 3's in rows and columns

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<string> matrix(N);
    for (auto &e : matrix) {
      cin >> e;
    }

    vector<int> row_sums(N, 0), col_sums(M, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int e = matrix[i][j] - '0';
        row_sums[i] ^= e;
        col_sums[j] ^= e;
      }
    }

    vector<int> row_counts(4, 0), col_counts(4, 0);
    for (int i = 0; i < N; i++) {
      row_counts[row_sums[i] % 4]++;
    }
    for (int i = 0; i < M; i++) {
      col_counts[col_sums[i] % 4]++;
    }

    cerr << '(';
    for (int i = 1; i < 4; i++) {
      if (i > 1) {
        cerr << ", ";
      }
      cerr << row_counts[i];
    }
    cerr << ") ";

    cerr << '(';
    for (int i = 1; i < 4; i++) {
      if (i > 1) {
        cerr << ", ";
      }
      cerr << col_counts[i];
    }
    cerr << ") ";

    int ans = 0;
    for (int i = 1; i < 4; i++) {
      if (row_counts[i] % 2 == 1 and col_counts[i] % 2 == 1) {
        ans++;
        row_counts[i]--;
        col_counts[i]--;
      }
    }

    cerr << ans << ' ';

    bool is_all_row_counts_even = true, is_all_col_counts_even = true;
    for (int i = 1; i < 4; i++) {
      is_all_row_counts_even =
          is_all_row_counts_even and row_counts[i] % 2 == 0;
      is_all_col_counts_even =
          is_all_col_counts_even and col_counts[i] % 2 == 0;
    }
    if (is_all_row_counts_even and is_all_col_counts_even) {
      ans += 0;
    } else if (is_all_row_counts_even or is_all_col_counts_even) {
      ans += 3;
    } else {
      ans += 2;
    }

    cerr << ans << ' ';

    int row_total = 0, col_total = 0;
    for (int i = 1; i < 4; i++) {
      row_total += (row_counts[i] + 1) / 2 * 2;
      col_total += (col_counts[i] + 1) / 2 * 2;
    }

    cerr << '(' << row_total << ", " << col_total << ") ";

    ans += max(row_total, col_total);

    cerr << ans << '\n';

    cout << ans << '\n';
  }
}
