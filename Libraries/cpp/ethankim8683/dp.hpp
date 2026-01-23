#ifndef ETHANKIM8683_DP
#define ETHANKIM8683_DP 1

#include <map>
#include <numeric>
#include <tr2/dynamic_bitset>
#include <vector>

// TODO: Implement https://codeforces.com/blog/entry/98663
// Subset sum speedup 1 verification:
// https://codeforces.com/problemset/problem/1856/E2

// https://codeforces.com/blog/entry/98663
// Finds all subset sums of w, where \sum_{i=1}^N w_i = C
// O(C\sqrt{C})
template <typename T>
std::tr2::dynamic_bitset<T> subset_sum_speedup_1(const std::vector<int> &w) {
  int n = std::accumulate(w.begin(), w.end(), 0);
  std::map<int, int> counts;
  for (auto e : w) {
    counts[e]++;
  }
  std::tr2::dynamic_bitset<T> rv(n + 1);
  rv.set(0);
  for (auto [d, count] : counts) {
    if (count == 0) continue;
    if (count % 2 == 1) {
      rv |= rv << d;
      if (count > 1) {
        counts[2 * d] += (count - 1) / 2;
      }
    } else {
      rv |= rv << d;
      rv |= rv << d;
      if (count > 2) {
        counts[2 * d] += (count - 2) / 2;
      }
    }
  }
  return rv;
}

// TODO: Implement https://atcoder.jp/contests/abc348/editorial/9775
// Monotone maxima

#endif  // ETHANKIM8683_DP
