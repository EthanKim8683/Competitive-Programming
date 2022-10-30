#include <bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I L=19;
const I K=18;

// 1. current index
// 2. trg count
// 3. low<x<upp, low=x<upp, low<x=upp, low=x=upp
Lli dp[L+1][K+1][4];
vector<I>lows;
vector<I>upps;

void tod(Lli low,Lli upp){
  lows.clear(),upps.clear();
  for(;low||upp;low/=10,upp/=10)lows.push_back(low%10),upps.push_back(upp%10);
  reverse(lows.begin(),lows.end()),reverse(upps.begin(),upps.end());
}

Lli slv(Lli low,Lli upp,I trg,I cnt){
  fill(&dp[0][0][0],&dp[0][0][0]+(L+1)*(K+1)*4,0);
  tod(low,upp);
  I len=lows.size();
  dp[0][0][3]=1;
  for(I i=0;i<len;i++)for(I j=0;j<=cnt;j++)for(I k=0;k<4;k++){
    I beg=k>>1&1?lows[i]:0,end=k>>0&1?upps[i]:9;
    for(I l=beg;l<=end;l++)dp[i+1][j+(l==trg)][(k>>1&1?l==lows[i]:0)<<1|(k>>0&1?l==upps[i]:0)<<0]+=dp[i][j][k];
  }
  return accumulate(dp[len][cnt],dp[len][cnt]+4,(Lli)0);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli a,b;I d,k;cin>>a>>b>>d>>k;
  printf("%lli\n",slv(a,b,d,k));
}