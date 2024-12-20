#include <bits/stdc++.h>
using namespace std;
 
// Mint {{{
template<int MOD=998244353>
struct Mint {
	static constexpr int EXP_MOD = MOD - 1;
	
	int v;
 
	Mint(int _v) : v(_v % MOD + (_v < 0) * MOD) {}
	Mint(long long _v) : v(_v % MOD + (_v < 0) * MOD) {}
	Mint(unsigned _v=0) : v(_v % MOD) {}
	Mint(unsigned long _v) : v(_v % MOD) {}
	Mint(unsigned long long _v) : v(_v % MOD) {}
 
	explicit operator int() const { return v; }
	
	bool operator==(const Mint &rhs) const { return v == rhs.v; }
	bool operator!=(const Mint &rhs) const { return v != rhs.v; }
 
	Mint &operator+=(const Mint &rhs) { v += rhs.v; v -= (v >= MOD) * MOD; return *this; }
	Mint &operator-=(const Mint &rhs) { v += (rhs.v > v) * MOD - rhs.v; return *this; }
	Mint &operator*=(const Mint &rhs) { v = (long long) v * rhs.v % MOD; return *this; }
	Mint &operator/=(const Mint &rhs) { return *this *= inv(rhs); }
	
	friend Mint operator+(Mint lhs, const Mint &rhs) { return lhs += rhs; }
	friend Mint operator-(Mint lhs, const Mint &rhs) { return lhs -= rhs; }
	friend Mint operator*(Mint lhs, const Mint &rhs) { return lhs *= rhs; }
	friend Mint operator/(Mint lhs, const Mint &rhs) { return lhs /= rhs; }
 
	Mint operator-() { return Mint(-v); }
	
	friend Mint pow(Mint b, long long e) {
		Mint rv = 1;
		for (; e; e >>= 1, b *= b) if (e & 1) rv *= b;
		return rv;
	}
 
	friend Mint pow(Mint b, Mint<EXP_MOD> e) {
		return pow(b, (int) e);
	}
 
	friend Mint inv(Mint m) {
		auto gcd = [](int a, int b) -> tuple<int, int, int> {
			int x = 1, y = 0, z = 0, w = 1;
			while (b != 0) {
				int q = a / b;
				tie(x, z) = make_pair(z, x - q * z);
				tie(y, w) = make_pair(w, y - q * w);
				tie(a, b) = make_pair(b, a - q * b);
			}
			return {a, x, y};
		};
 
		auto [g, x, y] = gcd(m.v, MOD);
		if (g != 1) throw runtime_error("inverse does not exist");
		return Mint(x);
	}
 
	friend Mint log(Mint b, Mint p) {
		constexpr int n = sqrt(MOD) + 1;
 
		unordered_map<int, int> small;
		Mint P = p;
		for (int e = 0; e <= n; e++, P *= b) {
			small[(int) P] = e;
		}
 
		Mint B = pow(b, n);
		P = 1;
		for (int e = 1; e <= n; e++) {
			P *= B;
			if (small.find((int) P) != small.end()) {
				return n * e - small[(int) P];
			}
		}
		
		throw runtime_error("logarithm does not exist");
	}
 
	friend istream &operator>>(istream &in, Mint &m) {
		long long v; in >> v;
		m.v = v % MOD + (v < 0) % MOD;
		return in;
	}
 
	friend ostream &operator<<(ostream &out, const Mint &m) {
		out << m.v;
		return out;
	}
};
 
template<int MOD=998244353>
Mint<MOD> fact(int n) {
	if (n < 0) return 0;
	static vector<Mint<MOD>> fact(1, 1);
	for (static int i = 1; i <= n; i++) {
		fact.push_back(fact.back() * i);
	}
	return fact[n];
}
 
template<int MOD=998244353>
Mint<MOD> binom(int n, int k) {
	if (n < 0 or k < 0 or n - k < 0) return 0;
	
	auto ifact = [](int m) -> Mint<MOD> {	
		static vector<Mint<MOD>> ifact(1, 1);
		for (static int i = 1; i <= m; i++) {
			ifact.push_back(ifact.back() / i);
		}
		return ifact[m];
	};
 
	return fact<MOD>(n) * ifact(k) * ifact(n - k);
}
// }}}
using mint = Mint<>;
 
int main() {
	cin.tie(0)->sync_with_stdio(0);
 
	vector<vector<int>> D(1e6 + 1);
	for (int i = 1; i <= 1e6; i++) {
		for (int j = i; j <= 1e6; j += i) {
			D[j].push_back(i);
		}
		reverse(D[i].begin(), D[i].end());
	}
 
	int T;
	cin >> T;
	
	while (T--) {
		int M;
		cin >> M;
 
		mint ans = 0;
		vector<mint> dp2(M + 1, 0), dp3(M + 1, 0), dp4(M + 1, 0);
		for (int i = M; i >= 1; i--) {
			for (auto d : D[i]) {
				dp3[d] += dp2[d];
			}
			for (auto d : D[i]) {
				// dp3[d] += dp2[d];
				// if (d == i) {
				// 	dp[i][d] += 1;
				// }
				for (auto d2 : D[d]) {
					if (d2 == d) continue;
					dp3[d2] -= dp3[d];
				}
				dp3[d] -= dp4[d];
				mint v = dp3[d] + (d == i);
				ans += v;
				for (auto d2 : D[d]) {
					if (d2 == d) {
						dp4[d2] += 2 * v;
					}
					dp2[d2] += 2 * v;
				}
				dp3[d] = 0;
				// ans += dp[i][d];
				// for (int k = 1; k <= i - 1; k++) {
				// 	if (k % d == 0) continue;
				// 	dp[k][gcd(k, d)] += 2 * dp[i][d];
				// }
			}
		}
		// for (int i = M; i >= 1; i--) {
		// 	for (int j = i; j <= M; j += i) {
		// 		ans += dp[i][j];
		// 		for (int k = 1; k <= j - 1; k++) {
		// 			if (k % i == 0) continue;
		// 			dp[gcd(k, i)][k] += 2 * dp[i][j];
		// 		}
		// 	}
		// }
		// mint ans = 0;
		// for (int i = M; i >= 1; i--) {
		// 	for (int j = 1; j <= i; j++) {
		// 		ans += dp[i][j];
		// 		for (int k = 1; k <= i - 1; k++) {
		// 			dp[k][gcd(k, j)] += 2 * dp[i][j];
		// 		}
		// 		for (int k = j; k <= i - 1; k += j) {
		// 			dp[k][j] -= 2 * dp[i][j];
		// 		}
		// 	}
		// }
		cout << ans << '\n';
	}
}
/*
1. Think big picture!
 
2. Don't waste time coding before thinking it through!
 
3. Think fast! Don't be afraid to churn through ideas!
 
4. Try modelling the problem with as few moving parts as possible!
	- What does the problem look like?
	- What might the solution look like?
 
5. Try listing properties of components of the problem!
	- All ____ have ____
	- All ____ can be represented as ____
	- There is at most ____ ____'s
 
6. Try solving an easier version of the problem!
	- What if the problem didn't have this constraint?
	- How would I solve a more general version of the problem?
	- Remember, what is presented to you isn't all you can use!
 
7. Ask questions!
	- What has similar behavior?
	- I've assumed this, what now?
 
Temporary tips:
- Casework can be easier by picking something to do casework on,
  then finding the cases (as opposed to prioritizing looking for
  what is relevant)
 
 
*/
