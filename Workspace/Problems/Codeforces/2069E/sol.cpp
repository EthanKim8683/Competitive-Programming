#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  while (N--) {
    string S;
    cin >> S;

    int A, B, AB, BA;
    cin >> A >> B >> AB >> BA;

    // split strings into alternating parts
    //
    // ABABA -> AB A BA
    // ABABAB -> AB AB AB, A BA B AB
    //
    // greedy exchange

    vector<string> parts;
    string part = "";
    for (auto e : S) {
      if (part.empty() or part.back() == e) {
        parts.push_back(part);
        part = "";
      }
      part += e;
    }
    parts.push_back(part);

    map<string, vector<int>> sizes_by_pair;
    map<string, int> count_by_pair;
    int a = 0, b = 0;
    for (auto part : parts) {
      if (part.size() % 2 == 1) {
        (part[0] == 'A' ? a : b)++;
      } else {
        string pair = part.substr(0, 2);
        sizes_by_pair[pair].push_back(part.size());
        count_by_pair[pair] += part.size() / 2;
      }
    }
    for (auto &[pair, sizes] : sizes_by_pair) {
      sort(sizes.rbegin(), sizes.rend());
    }
  }
}