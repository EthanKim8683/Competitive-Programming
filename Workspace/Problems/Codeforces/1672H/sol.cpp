#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  string A;
  cin >> A;

  vector<int> psz(N), pso(N);
  psz[0] = pso[0] = 0;
  for (int i = 0; i + 1 < N; i++) {
    if (A[i] == A[i + 1]) {
      (A[i] == '0' ? psz : pso)[i + 1] += 1;
    }
    psz[i + 1] += psz[i];
    pso[i + 1] += pso[i];
  }

  while (Q--) {
    int l, r;
    cin >> l >> r;
    l--;

    int z = psz[r - 1] - psz[l], o = pso[r - 1] - pso[l];
    cout << 1 + min(z, o) + abs(z - o) << '\n';
  }
}
