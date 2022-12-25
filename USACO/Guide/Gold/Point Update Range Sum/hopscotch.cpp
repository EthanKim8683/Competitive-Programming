#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;
const I R = 750;
const I C = 750;
const I K = R * C;

I sqrs[R][C];
Lli rng_rows[R + 1];
Lli rng_cols[C + 1];
vector<I> unq_rows[K];
vector<I> unq_cols[K];
vector<Lli> pnt_rows[K];
vector<Lli> pnt_cols[K];
I r, c;

void unq(vector<I>& unq) {
  sort(unq.begin(), unq.end());
}

I cps(vector<I>& unq, I i) {
  return upper_bound(unq.begin(), unq.end(), i) - unq.begin() - 1;
}

Lli mod(I i) {
  return i % MOD + (i < 0) * MOD;
}

void rng_row_upd(I i, Lli val) {
  for (; i <= r; i += i & -i)
    rng_rows[i] = mod(rng_rows[i] + val);
}

Lli rng_row_qry(I i) {
  Lli res = 0;
  for (; i > 0; i -= i & -i)
    res = mod(res + rng_rows[i]);
  return res;
}

void rng_col_upd(I i, Lli val) {
  for (; i > 0; i -= i & -i)
    rng_cols[i] = mod(rng_cols[i] + val);
}

Lli rng_col_qry(I i) {
  Lli res = 0;
  for (; i <= c; i += i & -i)
    res = mod(res + rng_cols[i]);
  return res;
}

void pnt_row_upd(vector<Lli>& row, I i, Lli val) {
  for (; i < row.size(); i += i & -i)
    row[i] = mod(row[i] + val);
}

Lli pnt_row_qry(vector<Lli>& row, I i) {
  Lli res = 0;
  for (; i > 0; i -= i & -i)
    res = mod(res + row[i]);
  return res;
}

void pnt_col_upd(vector<Lli>& col, I i, Lli val) {
  for (; i > 0; i -= i & -i)
    col[i] = mod(col[i] + val);
}

Lli pnt_col_qry(vector<Lli>& col, I i) {
  Lli res = 0;
  for (; i < col.size(); i += i & -i)
    res = mod(res + col[i]);
  return res;
}

void all_upd(I i, I j, Lli val) {
  const auto sqr = sqrs[i][j];
  rng_row_upd(i + 2, val);
  rng_col_upd(j + 1, -val);
  pnt_row_upd(pnt_rows[sqr], cps(unq_rows[sqr], i) + 2, -val);
  pnt_col_upd(pnt_cols[sqr], cps(unq_cols[sqr], j) + 1, val);
}

Lli all_qry(I i, I j) {
  const auto sqr = sqrs[i][j];
  Lli res = i == 0 && j == 0;
  res = mod(res + rng_row_qry(i + 1));
  res = mod(res + rng_col_qry(j + 1));
  res = mod(res + pnt_row_qry(pnt_rows[sqr], cps(unq_rows[sqr], i) + 1));
  res = mod(res + pnt_col_qry(pnt_cols[sqr], cps(unq_cols[sqr], j) + 1));
  return res;
}

I main(void) {
  freopen("hopscotch.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("hopscotch.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I k;
  cin >> r >> c >> k;
  for (I i = 0; i < r; i++) {
    for (I j = 0; j < c; j++) {
      I sqr;
      cin >> sqr;
      sqr--;
      sqrs[i][j] = sqr;
      unq_rows[sqr].push_back(i);
      unq_cols[sqr].push_back(j);
    }
  }
  for (I i = 0; i < k; i++) {
    unq(unq_rows[i]);
    unq(unq_cols[i]);
    pnt_rows[i].resize(unq_rows[i].size() + 1);
    pnt_cols[i].resize(unq_cols[i].size() + 1);
  }
  for (I i = 0; i < r; i++)
    for (I j = 0; j < c; j++)
      all_upd(i, j, all_qry(i, j));
  printf("%lli\n", all_qry(r - 1, c - 1));
  return 0;
}