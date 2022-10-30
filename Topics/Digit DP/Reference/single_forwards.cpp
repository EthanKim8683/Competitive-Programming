#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I L=19;
const I K=18;

// 1. current index
// 2. trg count
// 3. x<upp, x=upp
Lli dp[L+1][K+1][2];
vector<I>dgts;

void tod(Lli val){
  dgts.clear();
  for(;val;val/=10)dgts.push_back(val%10);
  reverse(dgts.begin(),dgts.end());
}

Lli slv(Lli upp,I trg,I cnt) {
  fill(&dp[0][0][0],&dp[0][0][0]+(L+1)*(K+1)*2,0);
  tod(upp);
  I len=dgts.size();
  dp[0][0][1]=1;
  for(I i=0;i<len;i++)for(I j=0;j<=cnt;j++)for(I k=0;k<2;k++){
    I beg=0,end=k>>0&1?dgts[i]:9;
    for(I l=beg;l<=end;l++)dp[i+1][j+(l==trg)][(k>>0&1?l==dgts[i]:0)<<0]+=dp[i][j][k];
  }
  return accumulate(dp[len][cnt],dp[len][cnt]+2,(Lli)0);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli a,b;I d,k;cin>>a>>b>>d>>k;
  printf("%lli\n",slv(b,d,k)-slv(a-1,d,k));
}