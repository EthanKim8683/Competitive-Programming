#include <bits/stdc++.h>

#include "transfer.h"

using namespace std;

vector<int> get_attachment(vector<int> source) {
  int k = source.size() == 63 ? 7 : 9;

  int sum = 0;
  for (int i = 0; i < source.size(); i++) {
    if (source[i] == 1) {
      sum ^= i + 1;
    }
  }

  vector<int> rv;
  for (int i = 0; i < k - 1; i++) {
    rv.push_back(sum >> i & 1);
  }
  rv.push_back(__builtin_popcount(sum) % 2);

  return rv;
}

vector<int> retrieve(vector<int> data) {
  int k = data.size() == 63 + 7 ? 7 : 9;

  vector<int> rv(data.begin(), data.end() - k);

  int sum = 0;
  for (int i = 0; i < k - 1; i++) {
    sum |= data[data.size() - k + i] << i;
  }
  if (__builtin_popcount(sum) % 2 != data.back()) return rv;

  for (int i = 0; i < data.size() - k; i++) {
    if (data[i] == 1) {
      sum ^= i + 1;
    }
  }
  if (sum == 0) return rv;

  rv[sum - 1] ^= 1;
  return rv;
}
