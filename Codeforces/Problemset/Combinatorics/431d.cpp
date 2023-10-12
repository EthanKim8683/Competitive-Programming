#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const Lli N=1e18;
const I LOGN=61;
const I K=64;
Lli dp[LOGN+1][K+1][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli m;I k;cin>>m>>k;
  auto cnt=[&](Lli t){
    fill(&dp[0][0][0],&dp[0][0][0]+(LOGN+1)*(K+1)*2,0);
    dp[0][0][1]=1;
    for(I i=0;i<LOGN;i++)for(I j=0;j<=k;j++){
      I upp=t>>(LOGN-1-i)&1;
      for(I l=0;l<=1;l++)dp[i+1][j+l][0]+=dp[i][j][0];
      for(I l=0;l<=upp;l++)dp[i+1][j+l][l==upp]+=dp[i][j][1];
    }
    return dp[LOGN][k][0]+dp[LOGN][k][1];
  };
  Lli l=1,r=N;
  while(l<r){
    Lli t=l+(r-l)/2;
    cnt(2*t)-cnt(t)>=m?r=t:l=t+1;
  }
  printf("%lli\n",l);
}
/*
if we increase n, the number of numbers with popcount k will not decrease
because, 2 * n (which is added) has the same popcount as n (which is removed)

therefore, we can binary search for the minimum n such that the number of
numbers in [n + 1, 2 * n] with popcount k is exactly m
*/