#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int A, B, C, K;
    cin >> A >> B >> C >> K;

    vector<int> D(K);
    for (auto &e : D) cin >> e;

    // Today I'm learning about Burnside's Lemma!
    //
    // For a long time, I was intimidated by the fancy math terms and algebra,
    // but today I decided to bite the bullet and actually try to understand
    // what's going on.
    //
    // Firstly, a group action is a group of actions, so functions that map from
    // X to X, including the identity function and inverses.
    //
    // An orbit of an element of X is all the elements it can become after any
    // group action is applied onto it. Notably (at least to me), it can become
    // itself since the group of actions contains an identity.
    //
    // To understand what Burnside's Lemma is even saying, we can use these two
    // facts to observe that if two elements can become eachother after some
    // transformations, they'll be in eachother's orbits. So, the left hand term
    // of Burnside's Lemma is basically counting the number of connected
    // components of thingies (keyed by their orbits) that can become each
    // other.
    //
    // The rest of the formula doesn't need as much interpretation, since
    // formulas just are what they are, but I remember being confused about the
    // fixed points, as in, "Is it equal to itself, like actually exactly equal,
    // or is it equal after some transformations?" And the answer turns out to
    // be the former: the element after the group action is literally itself.
    //
    // Lastly, the group action needs to contain all transformations. Remember,
    // combining two actions needs to produce another action in the group, since
    // it's a group.
  }
}
