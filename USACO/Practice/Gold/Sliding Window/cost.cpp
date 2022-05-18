#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

using I = int;
using Lli = long long;
using B = bool;

const I N = 2e5;

multiset<I> pos;
multiset<I> neg;
I x_arr[N];
I pos_cnt = 0;
I neg_cnt = 0;
Lli pos_sum = 0;
Lli neg_sum = 0;
I k;

void pos_ins(I i) {
  pos.insert(i);
  pos_cnt++;
  pos_sum += i;
}

void neg_ins(I i) {
  neg.insert(i);
  neg_cnt++;
  neg_sum += i;
}

void pos_ers(I i) {
  pos.erase(pos.find(i));
  pos_cnt--;
  pos_sum -= i;
}

void neg_ers(I i) {
  neg.erase(neg.find(i));
  neg_cnt--;
  neg_sum -= i;
}

I med() {
  return *neg.rbegin();
}

void add(I i) {
  if (i > med()) {
    pos_ins(i);
    if (pos.size() > k / 2) {
      neg_ins(*pos.begin());
      pos_ers(*pos.begin());
    }
  } else {
    neg_ins(i);
    if (neg.size() > (k + 1) / 2) {
      pos_ins(*neg.rbegin());
      neg_ers(*neg.rbegin());
    }
  }
}

void rmv(I i) {
  if (pos.find(i) != pos.end())
    pos_ers(i);
  else
    neg_ers(i);
  if (neg.empty()) {
    neg_ins(*pos.begin());
    pos_ers(*pos.begin());
  }
}

Lli neg_cst() {
  return neg_cnt * med() - neg_sum;
}

Lli pos_cst() {
  return pos_sum - pos_cnt * med();
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("cost.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n >> k;
  if (k != 1) {
    for (I i = 0; i < n; i++)
      cin >> x_arr[i];
    neg_ins(x_arr[0]);
    for (I i = 1; i < k; i++)
      add(x_arr[i]);
    printf("%lli ", neg_cst() + pos_cst());
    for (I i = 0; i + k < n; i++) {
      rmv(x_arr[i]);
      add(x_arr[i + k]);
      printf("%lli ", neg_cst() + pos_cst());
    }
  } else
    for (I i = 0; i + k <= n; i++)
      printf("0 ");
  return 0;
}