#include <bits/stdc++.h>

#include "decoder.h"
#include "encoder.h"
#include "grader.h"

using namespace std;

using i64 = long long;

const int INF = 1e9;
const int LOGN = 10;
const int LOGD = 58;

void encode(int N, int H, int P, int *A, int *B) {
  vector<vector<int>> adj(N);
  for (int i = 0; i < P; i++) {
    int a = A[i], b = B[i];
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector dist(H, vector<int>(N, INF));
  for (int i = 0; i < H; i++) {
    queue<int> q;
    auto push = [&](int a, int d) -> void {
      if (d >= dist[i][a]) return;
      dist[i][a] = d;
      q.push(a);
    };
    push(i, 0);
    while (q.size() > 0) {
      int a = q.front();
      q.pop();

      for (auto b : adj[a]) {
        push(b, dist[i][a] + 1);
      }
    }
  }

  vector<vector<int>> deltas;
  vector<int> order;
  vector<bool> seen(N, false);
  auto dfs = [&](auto self, int a) -> void {
    for (auto b : adj[a]) {
      if (seen[b]) continue;
      seen[b] = true;

      vector<int> delta(H);
      for (int i = 0; i < H; i++) {
        delta[i] = dist[i][b] - dist[i][a];
      }
      deltas.push_back(delta);

      order.push_back(b);

      self(self, b);

      deltas.push_back({});
    }
  };
  seen[0] = true;
  dfs(dfs, 0);

  for (auto e : order) {
    for (int i = 0; i < LOGN; i++) {
      encode_bit(e >> i & 1);
    }
  }

  for (auto r : deltas) {
    if (r.size() == H) {
      i64 d = 0;
      for (int i = H - 1; i >= 0; i--) {
        d = d * 3 + r[i] + 1;
      }

      encode_bit(0);
      for (int i = 0; i < LOGD; i++) {
        encode_bit(d >> i & 1);
      }
    } else {
      encode_bit(1);
    }
  }
}

void decode(int N, int H) {
  vector<int> order;
  order.push_back(0);
  for (int i = 1; i < N; i++) {
    int a = 0;
    for (int j = 0; j < LOGN; j++) {
      a |= decode_bit() << j;
    }
    order.push_back(a);
  }

  vector dist(H, vector<int>(N, 0));
  vector<int> stack;
  stack.push_back(order[0]);
  for (int i = 0, j = 1; i < 2 * (N - 1); i++) {
    if (decode_bit() == 0) {
      int b = order[j];
      j++;

      i64 d = 0;
      for (int k = 0; k < LOGD; k++) {
        d |= (i64) decode_bit() << k;
      }

      int a = stack.back();
      for (int k = 0; k < H; k++) {
        dist[k][b] = dist[k][a] + d % 3 - 1;
        d /= 3;
      }

      stack.push_back(b);
    } else {
      stack.pop_back();
    }
  }

  vector<int> offset(H);
  for (int i = 0; i < H; i++) {
    offset[i] = -dist[i][i];
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < H; j++) {
      dist[j][i] += offset[j];
    }
  }

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < N; j++) {
      hops(i, j, dist[i][j]);
    }
  }
}
