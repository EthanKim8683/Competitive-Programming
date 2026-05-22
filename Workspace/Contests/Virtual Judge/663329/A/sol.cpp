#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string line;
  getline(cin, line);

  string line_ = "";
  for (auto e : line) {
    if ('a' <= e and e <= 'z') {
      line_ += e;
    } else if ('A' <= e and e <= 'Z') {
      line_ += e + 'a' - 'A';
    }
  }

  bool pal = false;
  for (int i = 0; i < line_.size(); i++) {
    for (int j = i + 1; j < line_.size(); j++) {
      bool pal_ = true;
      for (int l = i, r = j; l < r; l++, r--) {
        pal_ = pal_ and line_[l] == line_[r];
      }
      pal = pal or pal_;
    }
  }
  cout << (pal ? "Palindrome" : "Anti-palindrome");
}