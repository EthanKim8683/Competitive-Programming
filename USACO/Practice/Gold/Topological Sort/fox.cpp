#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using S = string;
using B = bool;

const I N = 100;

vector<I> adjs[26];
vector<I> tops;
S nams[N];
I inds[26];
B viss[26];

void dfs(I a) {
  if (!viss[a]) {
    viss[a] = true;
    for (const auto b : adjs[a])
      dfs(b);
    tops.push_back(a);
  }
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("fox.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> nams[i];
  for (I i = 0; i + 1 < n; i++) {
    const auto cur = nams[i];
    const auto nxt = nams[i + 1];
    I cur_ind = 0;
    I nxt_ind = 0;
    B dif = false;
    while (cur_ind < cur.size() && nxt_ind < nxt.size()) {
      const auto cur_chr = cur[cur_ind];
      const auto nxt_chr = nxt[nxt_ind];
      if (cur_chr != nxt_chr) {
        adjs[cur_chr - 'a'].push_back(nxt_chr - 'a');
        dif = true;
        break;
      }
      cur_ind++;
      nxt_ind++;
    }
    if (!dif && cur.size() > nxt.size()) {
      printf("Impossible\n");
      return 0;
    }
  }
  for (I i = 26 - 1; i >= 0; i--)
    dfs(i);
  reverse(tops.begin(), tops.end());
  for (I i = 0; i < 26; i++)
    inds[tops[i]] = i;
  for (I i = 0; i < 26; i++) {
    for (const auto b : adjs[i]) {
      if (inds[b] <= inds[i]) {
        printf("Impossible\n");
        return 0;
      }
    }
  }
  for (I i = 0; i < 26; i++)
    printf("%c", tops[i] + 'a');
  return 0;
}