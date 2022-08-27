using I = int;
using Lli = long long int;

const I N = 1e5;
const Lli MIN = -1e18;
const Lli MAX = 1e18;

class Solution {
public:
  I segs[2 * (N + 1)];
  Lli pfxs[N + 1];
  vector<Lli> cpss;
  I n;

  I low(Lli i) {
    return lower_bound(cpss.begin(), cpss.end(), i) - cpss.begin();
  }

  I upp(Lli i) {
    return upper_bound(cpss.begin(), cpss.end(), i) - cpss.begin();
  }

  void upd(I i, I val) {
    for (segs[i += n] += val; i > 1; i >>= 1)
      segs[i >> 1] = segs[i] + segs[i ^ 1];
  }

  I qry(I l, I r) {
    I res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        res += segs[l++];
      if (r & 1)
        res += segs[--r];
    }
    return res;
  }

  I countRangeSum(vector<I>& nums, I lower, I upper) {
    n = nums.size();
    Lli acc = 0;
    for (I i = 0; i < n; i++)
      pfxs[i + 1] = pfxs[i] + nums[i];
    cpss.push_back(MAX);
    cpss.push_back(MIN);
    for (I i = 0; i <= n; i++)
      cpss.push_back(pfxs[i]);
    sort(cpss.begin(), cpss.end());
    cpss.erase(unique(cpss.begin(), cpss.end()), cpss.end());
    I res = 0;
    for (I i = 0; i <= n; i++) {
      const auto pfx = pfxs[i];
      res += qry(low(pfx - upper), upp(pfx - lower));
      upd(low(pfx), 1);
    }
    return res;
  }
};