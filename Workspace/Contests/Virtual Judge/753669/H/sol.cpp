#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<string> bulletin;
  string line;
  while (getline(cin, line)) {
    bulletin.push_back(line);
  }

  vector<string> peeled;
  for (int i = 1; i < bulletin.size() - 1; i++) {
    peeled.push_back(bulletin[i].substr(1, bulletin[i].size() - 2));
  }

  int N = peeled.size(), M = peeled[0].size();

  vector filled(N, vector<bool>(M, false));
  for (int i = 0; i < N; i++) {
    bool fill = false;
    for (int j = 0; j < M; j++) {
      bool fill0 = fill, flip = peeled[i][j] == '|';
      if (fill0 and flip) {
        fill = !fill;
      }
      filled[i][j] = fill;
      if (!fill0 and flip) {
        fill = !fill;
      }
    }
  }

  vector id(N, vector<int>(M, -1));
  auto dfs = [&](auto self, int i, int j, int t) -> void {
    if (i < 0 or i >= N or j < 0 or j >= M) return;
    if (!filled[i][j]) return;
    if (id[i][j] != -1) return;
    id[i][j] = t;
    for (auto [di, dj] :
         (pair<int, int>[]) {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
      self(self, i + di, j + dj, t);
    }
  };
  int t = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (!filled[i][j]) continue;
      if (id[i][j] != -1) continue;
      dfs(dfs, i, j, t);
      t++;
    }
  }

  // for (int i = 0; i < N; i++) {
  //   for (int j = 0; j < M; j++) {
  //     if (id[i][j] == -1) {
  //       cerr << ' ';
  //     } else {
  //       cerr << id[i][j];
  //     }
  //   }
  //   cerr << '\n';
  // }

  vector<vector<pair<int, string>>> courses(t);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int t = id[i][j];
      if (t == -1) continue;
      char c = peeled[i][j];
      if ('A' <= c and c <= 'Z') {
        c += 'a' - 'A';
      }
      if (c != ' ') {
        if (courses[t].empty() or courses[t].back().first != i) {
          courses[t].push_back({i, ""});
        }
        courses[t].back().second += c;
      }
    }
  }

  int ans = INF;
  for (int i = 0; i < t; i++) {
    for (int j = i + 1; j < t; j++) {
      for (int k = j + 1; k < t; k++) {
        set<string> all_courses;
        for (auto [_, course] : courses[i]) {
          all_courses.insert(course);
        }
        for (auto [_, course] : courses[j]) {
          all_courses.insert(course);
        }
        for (auto [_, course] : courses[k]) {
          all_courses.insert(course);
        }
        ans = min(ans, (int) all_courses.size());
      }
    }
  }
  cout << ans;
}