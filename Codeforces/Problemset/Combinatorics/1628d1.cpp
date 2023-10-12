#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2000;
const Lli MOD=1e9+7;
Lli dp[N+1][N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli hlf=inv(2);
  dp[0][0]=0;
  for(I i=1;i<=N;i++)dp[i][0]=(dp[i-1][0]+1)%MOD;
  for(I i=1;i<=N;i++)for(I j=1;j<=N;j++)dp[i][j]=(dp[i-1][j]+dp[i][j-1])*hlf%MOD;
  I t;cin>>t;
  while(t--){
    I n,m,k;cin>>n>>m>>k;
    printf("%lli\n",dp[m][n-m]*k%MOD);
  }
}
/*
if we work backwards, the final score for a state (x, y) with x remaining add
turns and y remaining subtract turns is the average of the states (x, y - 1)
and (x - 1, y) since, if Alice picks a k larger than half their difference,
Bob can choose to subtract, getting less than the average and if Alice picks
a k smaller than half their difference, Alice would be getting less than she
could have
*/