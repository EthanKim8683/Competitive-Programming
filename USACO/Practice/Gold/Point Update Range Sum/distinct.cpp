#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;
const I Q = 2e5;

vector<I> vals;
I x_arr[N];
pair<I, I> q_arr[Q];
I fens[N + 1];
I inds[N];
I swps[Q];
I ress[Q];
I n;

I cps(I i) {
  return upper_bound(vals.begin(), vals.end(), i) - vals.begin() - 1;
}

void upd(I i, I val) {
  for (; i <= n; i += i & -i)
    fens[i] += val;
}

I qry(I i) {
  I res = 0;
  for (; i > 0; i -= i & -i)
    res += fens[i];
  return res;
}

B cmp(I a, I b) {
  return q_arr[a].second < q_arr[b].second;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("distinct.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = 0; i < n; i++) {
    I x;
    cin >> x;
    x_arr[i] = x;
    vals.push_back(x);
  }
  for (I i = 0; i < q; i++) {
    I a, b;
    cin >> a >> b;
    q_arr[i] = {a, b};
  }
  for (I i = 0; i < q; i++)
    swps[i] = i;
  sort(swps, swps + q, cmp);
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  I ind = 0;
  for (I i = 1; i <= n; i++) {
    auto& j = inds[cps(x_arr[i - 1])];
    if (j)
      upd(j, -1);
    upd(i, 1);
    j = i;
    while (ind < q && i == q_arr[swps[ind]].second) {
      const auto j = swps[ind++];
      ress[j] = qry(i) - qry(q_arr[j].first - 1);
    }
  }
  for (I i = 0; i < q; i++)
    printf("%i\n", ress[i]);
  return 0;
}