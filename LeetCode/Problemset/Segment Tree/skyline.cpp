using I = int;

const I N = 1e4;

class Solution {
public:
  vector<tuple<I, I, I>> blds;
  I segs[2 * 2 * N];
  vector<I> cpss;
  vector<pair<I, I>> ress;
  I len;
  
  I cps(I i) {
    return lower_bound(cpss.begin(), cpss.end(), i) - cpss.begin();
  }
  
  I exp(I i) {
    return cpss[i];
  }
  
  void upd(I l, I r, I val) {
    for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        segs[l] = max(segs[l], val);
        l++;
      }
      if (r & 1) {
        r--;
        segs[r] = max(segs[r], val);
      }
    }
  }
  
  I qry(I i) {
    I res = 0;
    for (i += len; i > 0; i >>= 1)
      res = max(res, segs[i]);
    return res;
  }
  
  vector<vector<I>> getSkyline(vector<vector<I>>& buildings) {
    for (const auto& bld : buildings) {
      cpss.push_back(bld[0]);
      cpss.push_back(bld[1]);
      blds.push_back({bld[0], bld[1], bld[2]});
    }
    sort(cpss.begin(), cpss.end());
    cpss.erase(unique(cpss.begin(), cpss.end()), cpss.end());
    len = cpss.size();
    for (const auto [l, r, h] : blds)
      upd(cps(l), cps(r), h);
    I lst = -1;
    vector<vector<I>> ress;
    for (I i = 0; i < len; i++) {
      I cur = qry(i);
      if (cur != lst) {
        ress.push_back({exp(i), cur});
        lst = cur;
      }
    }
    return ress;
  }
};