#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // 1. if the convex hulls intersect
  // 2. if one convex hull contains the other
  //   2a. if the inner convex hull contains a point of the outer set
  //   2b. sort outer set points radially around centroid of inner convex hull;
  //       to see if line intersects convex hull, get radius orthogonal to line
  //       and compare to orthogonal distance; try all lines using binary search
}
