#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Lf=long double;
const I N=1000;
const I L=18;
Lf prbs[N];
Lli pows[L+1];
Lf dp[N+1][N+1];
Lli cnt(Lli x){
  if(x==0)return 0;
  I msb,len=0;
  for(Lli t=x;t;t/=10)msb=t%10,len++;
  Lli res=0;
  res+=msb==1?x-pows[len-1]+1:pows[len-1];
  for(I i=0;i<len-1;i++)res+=pows[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=L;i++)pows[i]=pows[i-1]*10;
  I n;cin>>n;
  for(I i=0;i<n;i++){
    Lli l,r;cin>>l>>r;
    prbs[i]=(Lf)(cnt(r)-cnt(l-1))/(r-l+1);
  }
  I k;cin>>k;
  dp[0][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=i;j++){
    Lf prb=prbs[i];
    dp[i+1][j+1]+=dp[i][j]*prb;
    dp[i+1][j]+=dp[i][j]*(1-prb);
  }
  Lf res=0;
  for(I i=(n*k+99)/100;i<=n;i++)res+=dp[n][i];
  printf("%.15Lf\n",res);
}