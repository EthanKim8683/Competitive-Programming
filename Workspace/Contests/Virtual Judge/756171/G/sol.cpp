#include <bits/stdc++.h>

using namespace std;

const int MOD = 37;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector M(N, vector<int>(N));
  for (auto &r : M) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  cin.ignore(1);
  string S;
  getline(cin, S);

  while (S.size() % N != 0) {
    S.push_back(' ');
  }

  auto char_to_num = [&](char c) -> int {
    if ('A' <= c and c <= 'Z') {
      return c - 'A';
    } else if ('0' <= c and c <= '9') {
      return c - '0' + 26;
    } else {
      return 36;
    }
  };

  auto num_to_char = [&](int x) -> char {
    if (0 <= x and x < 26) {
      return x + 'A';
    } else if (26 + 0 <= x and x < 26 + 10) {
      return x - 26 + '0';
    } else {
      return ' ';
    }
  };

  auto vector_to_matrix = [&](vector<int> v) -> vector<vector<int>> {
    vector rv(v.size(), vector<int>(1));
    for (int i = 0; i < v.size(); i++) {
      rv[i][0] = v[i];
    }
    return rv;
  };

  auto matrix_to_vector = [&](vector<vector<int>> M) -> vector<int> {
    vector<int> rv(M.size());
    for (int i = 0; i < M.size(); i++) {
      rv[i] = M[i][0];
    }
    return rv;
  };

  auto matmul = [&](vector<vector<int>> A,
                    vector<vector<int>> B) -> vector<vector<int>> {
    vector rv(A.size(), vector<int>(B[0].size(), 0));
    for (int i = 0; i < A.size(); i++) {
      for (int j = 0; j < A[0].size(); j++) {
        for (int k = 0; k < B[0].size(); k++) {
          (rv[i][k] += A[i][j] * B[j][k]) %= MOD;
        }
      }
    }
    return rv;
  };

  vector vectors(S.size() / N, vector<int>(N));
  for (int i = 0; i < S.size(); i++) {
    vectors[i / N][i % N] = char_to_num(S[i]);
  }

  for (auto &e : vectors) {
    e = matrix_to_vector(matmul(M, vector_to_matrix(e)));
  }

  string T(S.size(), ' ');
  for (int i = 0; i < vectors.size(); i++) {
    for (int j = 0; j < N; j++) {
      T[i * N + j] = num_to_char(vectors[i][j]);
    }
  }
  cout << T;
}