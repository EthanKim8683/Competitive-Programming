#include "grader.h"

#include <bits/stdc++.h>

#include "decoder.h"
#include "encoder.h"
using namespace std;

const int $INF = 1e9;

queue<int> $bits;

void encode_bit(int b) { $bits.push(b); }

int decode_bit() {
  int rv = $bits.front();
  $bits.pop();
  return rv;
}

vector<vector<int>> $dist;

void hops(int h, int c, int d) { assert($dist[h][c] == d); }

int main(int argc, char **argv) {
  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N, P, H;
  if (argc > 1) {
    N = N = 1000;
    P = (N - 1) + rng() % (N * (N - 1) / 2 - (N - 1) + 1);
    H = H = 36;
  } else {
    cin >> N >> P >> H;
  }

  vector<int> A(P), B(P);
  if (argc > 1) {
    set<pair<int, int>> edges;
    for (int i = 0; i < N - 1; i++) {
      int a = rng() % (i + 1), b = i + 1;
      edges.insert({a, b});

      if (rng() % 2 == 0) {
        swap(a, b);
      }
      A[i] = a;
      B[i] = b;
    }

    for (int i = N - 1; i < P; i++) {
      int a, b;
      do {
        a = rng() % N;
        b = rng() % N;
        if (a > b) {
          swap(a, b);
        }
      } while (a == b or edges.contains({a, b}));
      edges.insert({a, b});

      if (rng() % 2 == 0) {
        swap(a, b);
      }
      A[i] = a;
      B[i] = b;
    }
  } else {
    for (int i = 0; i < P; i++) {
      cin >> A[i] >> B[i];
    }
  }

  vector<vector<int>> adj(N);
  for (int i = 0; i < P; i++) {
    int a = A[i], b = B[i];
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  $dist.resize(H);
  for (int i = 0; i < H; i++) {
    $dist[i].resize(N, $INF);
    queue<int> q;
    auto push = [&](int a, int d) -> void {
      if (d >= $dist[i][a]) return;
      $dist[i][a] = d;
      q.push(a);
    };
    push(i, 0);
    while (q.size() > 0) {
      int a = q.front();
      q.pop();
      for (auto b : adj[a]) {
        push(b, $dist[i][a] + 1);
      }
    }
  }

  encode(N, H, P, A.data(), B.data());

  assert($bits.size() <= 70000);

  decode(N, H);
}
