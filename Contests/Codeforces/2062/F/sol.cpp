#include <bits/stdc++.h>
#include "atcoder/dsu"
using namespace std;
using namespace atcoder;

using i64 = long long;

const i64 INF = 1e18;

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		vector<pair<int, int>> cities(N);
		for (auto &[a, b] : cities) {
			cin >> a >> b;
		}

		vector<tuple<int, int, int>> edges;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				auto [ai, bi] = cities[i];
				auto [aj, bj] = cities[j];
				edges.push_back({max(ai + bj, aj + bi), i, j});
			}
		}
		sort(edges.begin(), edges.end());

		dsu d(N);
		vector<vector<pair<int, int>>> adj(N);
		for (auto [w, a, b] : edges) {
			if (d.same(a, b)) continue;

			d.merge(a, b);
			adj[a].push_back({b, w});
			adj[b].push_back({a, w});
		}

		vector<i64> ans(N + 1, INF);
		for (int i = 0; i < N; i++) {
			auto dfs = [&](auto self, int a, int p = -1, int d = 1, i64 wtot = 0) -> void {
				ans[d] = min(ans[d], wtot);
				for (auto [b, w] : adj[a]) {
					if (b == p) continue;
					self(self, b, a, d + 1, wtot + w);
				}
			};
			dfs(dfs, i);
		}
		for (int i = 2; i <= N; i++) {
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}
}
/*

*/
