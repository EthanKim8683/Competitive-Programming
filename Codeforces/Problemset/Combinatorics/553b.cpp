#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50;
Lli dp[N+1];
vector<I>swps;
I ress[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  dp[0]=1;
  Lli acc=0;
  for(I i=2;i<=N;i++)dp[i]=dp[i-1]+dp[i-2];
  for(I i=0;i+1<=N;i++)dp[i+1]+=dp[i];
  I n;Lli k;cin>>n>>k,k--;
  Lli cur=0;
  for(I i=0;i+2<=n;i++)if(cur+dp[n-1-i]<=k)cur+=dp[n-1-i],swps.push_back(i),i++;
  iota(ress,ress+n,0);
  for(auto i:swps)swap(ress[i],ress[i+1]);
  for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
}
/*
it is impossible to produce a permutation identical to its standard cyclic
representation with cycles of length greater than 2

at the beginning of a cycle in the representation, p[i] must be the largest
value in the cycle

then, p[p[i]] must point to some other value in the cycle

however, since p[i] is the largest value in the cycle (and thus, the largest
index), p[p[i]] will always be strictly smaller than p[i]

and since p[p[i]] will always be strictly smaller than p[i], unless
p[p[i]] = i, the standard cyclic representation will be incorrect as it
expects p[p[i]] to come before p[i]

the index of a permutation p in a lexicographically sorted list of valid
permutations is determined by the position of its cycles, as the presence of
a cycle makes a permutation lexicographically larger than if one was not
present

this means we can greedily build the kth permutation, cycling at the current
index if doing so does not cause the number of permutations less than one
being generated to exceed k
*/