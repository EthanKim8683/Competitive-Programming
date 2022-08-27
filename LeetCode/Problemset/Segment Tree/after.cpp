using I = int;

const I N = 1e5;

class Solution {
public:
  I segs[2 * N];
  map<I, vector<I>, greater<I>> vals;
  I n;

  void asn(I i, I val) {
    segs[i + n] = val;
  }

  void bld() {
    for (I i = n - 1; i >= 0; i--)
      segs[i] = segs[i << 1] + segs[i << 1 | 1];
  }

  void upd(I i, I val) {
    for (segs[i += n] = val; i > 1; i >>= 1)
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

  vector<I> countSmaller(vector<I>& nums) {
    n = nums.size();
    for (I i = 0; i < n; i++) {
      vals[nums[i]].push_back(i);
      asn(i, 1);
    }
    bld();
    vector<I> ress(n);
    for (const auto& [val, inds] : vals) {
      for (const auto ind : inds)
        upd(ind, 0);
      for (const auto ind : inds)
        ress[ind] = qry(ind + 1, n);
    }
    return ress;
  }
};