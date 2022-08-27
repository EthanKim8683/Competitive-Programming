using I = int;
using B = bool;

const I N = 2000;

pair<I, I> ppls[N];

class Solution {
public:
  I inds[N];
  vector<vector<I>> ress;
  I n;
  
  static B cmp(I a, I b) {
    const auto [a_hgt, a_pos] = ppls[a];
    const auto [b_hgt, b_pos] = ppls[b];
    if (a_hgt == b_hgt)
      return a_pos < b_pos;
    return a_hgt > b_hgt;
  }

  vector<vector<I>> reconstructQueue(vector<vector<I>>& people) {
    ress.clear();
    n = people.size();
    for (I i = 0; i < n; i++) {
      const auto& ppl = people[i];
      ppls[i] = {ppl[0], ppl[1]};
    }
    iota(inds, inds + n, 0);
    sort(inds, inds + n, cmp);
    for (I i = 0; i < n; i++) {
      const auto ind = inds[i];
      ress.insert(ress.begin() + ppls[ind].second, people[ind]);
    }
    return ress;
  }
};