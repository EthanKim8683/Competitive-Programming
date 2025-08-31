#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		vector<int> L(N), R(N);
		for (int i = 0; i < N; i++) {
			cin >> L[i] >> R[i];
		}

		vector<vector<int>> adj(N);
		for (int i = 0; i < N - 1; i++) {
			int u, v;
			cin >> u >> v;
			u--, v--;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		auto dfs = [&](auto self, int a, int p = -1) -> tuple<i64, i64, i64> {
			i64 La = L[a], Ra = R[a], ga = 0;
			for (auto b : adj[a]) {
				if (b == p) continue;
				auto [Lb, Rb, gb] = self(self, b, a);
				gb += max(Lb - (R[a] + gb), 0ll);
				ga += gb;
				La = max(La, Lb - gb);
				Ra = min(Ra, Rb - gb);
			}
			La += ga;
			Ra += ga;
			Ra = max(Ra, La);
			return {La, Ra, ga};
		};
		cout << get<0>(dfs(dfs, 0)) << '\n';
	}
}
/*

*/
