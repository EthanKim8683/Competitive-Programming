#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

template<typename T, typename S>
pair<vector<T>, vector<vector<T>>> rrdp(const vector<vector<int>> &adj, S nil,
	function<S(T, int, int)> transition,
	function<S(S, S)> combine,
	function<T(S, int)> finalize) {
	int n = adj.size();
 
	vector<S> draft_dp(n);
	vector<vector<T>> adj_dp(n);
	auto up = [&](auto self, int a, int p=-1) -> T {
		adj_dp[a].resize(adj[a].size());
		draft_dp[a] = nil;
 
		for (int i = 0; i < adj[a].size(); i++) {
			int b = adj[a][i];
			if (b == p) continue;
 
			adj_dp[a][i] = self(self, b, a);
			draft_dp[a] = combine(draft_dp[a], transition(adj_dp[a][i], a, i));
		}
 
		return finalize(draft_dp[a], a);
	};
	up(up, 0);
	
	vector<T> dp(n);
	auto down = [&](auto self, int a, int p=-1) -> void {
		vector<S> prefix_dp(adj[a].size(), nil);
		for (int i = 0; i + 1 < adj[a].size(); i++) {
			prefix_dp[i + 1] = combine(prefix_dp[i], transition(adj_dp[a][i], a, i));
		}
		
		vector<S> suffix_dp(adj[a].size(), nil);
		for (int i = adj[a].size() - 1; i - 1 >= 0; i--) {
			suffix_dp[i - 1] = combine(transition(adj_dp[a][i], a, i), suffix_dp[i]);
		}
		
		for (int i = 0; i < adj[a].size(); i++) {
			int b = adj[a][i];
			if (b == p) continue;
 
			int j = find(adj[b].begin(), adj[b].end(), a) - adj[b].begin();
			adj_dp[b][j] = finalize(combine(prefix_dp[i], suffix_dp[i]), a);
			dp[b] = finalize(combine(draft_dp[b], transition(adj_dp[b][j], b, j)), b);
 
			self(self, b, a);
		}
	};
	down(down, 0);
	dp[0] = finalize(draft_dp[0], 0);
	
	return {dp, adj_dp};
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int T;
	cin >> T;

	while (T--) {
		int N;
		cin >> N;

		vector<int> W(N);
		for (auto &e : W) cin >> e;

		vector<vector<int>> adj(N);
		for (int i = 0; i < N - 1; i++) {
			int u, v;
			cin >> u >> v;
			u--, v--;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		auto [dp, adj_dp] = rrdp<pair<int, bool>, pair<int, bool>>(
      adj,
      {0, false},
      /* Transition */
      [&](pair<int, bool> dp, int a, int i) -> pair<int, bool> {
				return dp;
      },
      /* Combine */
      [&](pair<int, bool> dp1, pair<int, bool> dp2) -> pair<int, bool> {
				auto [mx1, has_root1] = dp1;
				auto [mx2, has_root2] = dp2;
				return {max(mx1, mx2), has_root1 or has_root2};
      },
      /* Finalize */
      [&](pair<int, bool> dp, int a) -> pair<int, bool> {
				auto [mx, has_root] = dp;
				return {max(mx, W[a]), has_root or a == 0};
      });
		vector<int> order(N);
		iota(order.begin(), order.end(), 0);
		sort(order.begin(), order.end(), [&](int a, int b) {
			return W[a] > W[b];
		});
		int ans = 0;
		for (auto i : order) {
			if (ans != 0) break;
			for (auto [mx, has_root] : adj_dp[i]) {
				if (has_root and mx > W[i]) {
					ans = i + 1;
				}
			}
		}
		cout << ans << '\n';
	}
}
/*

*/
