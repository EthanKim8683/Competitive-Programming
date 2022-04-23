#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

#define N 200000

using namespace std;

using I = int;

vector<I> adjs[N];
I parities[N];
I a_dists[N];
I b_dists[N];
queue<I> a_states;
queue<I> b_states;

void bfs(queue<I>& states, I* dists, I parity) {
  while (!states.empty()) {
    const I a = states.front();
    states.pop();
    const I dist = dists[a] + 1;
    for (const auto b : adjs[a]) {
      if (dists[b] == 1e9) {
        dists[b] = dist;
        states.push(b);
      }
    }
  }
}

int main(void) {
#ifdef ETHANKIM8683
  freopen("1272e.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(a_dists, n, 1e9);
  fill_n(b_dists, n, 1e9);
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    const I parity = a & 1;
    if (parity) {
      a_states.push(i);
      a_dists[i] = 0;
    } else {
      b_states.push(i);
      b_dists[i] = 0;
    }
    parities[i] = parity;
    if (i - a >= 0)
      adjs[i - a].push_back(i);
    if (i + a < n)
      adjs[i + a].push_back(i);
  }
  bfs(a_states, a_dists, 1);
  bfs(b_states, b_dists, 0);
  for (I i = 0; i < n; i++) {
    I dist;
    if (parities[i])
      dist = b_dists[i];
    else
      dist = a_dists[i];
    if (dist == 1e9)
      printf("-1 ");
    else
      printf("%i ", dist);
  }
  return 0;
}