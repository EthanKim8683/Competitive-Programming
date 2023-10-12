#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5000;
const Lli MOD=998244353;
I a_arr[N];
I cnts[N];
Lli facs[N+1];
Lli dp[N+1][N/2+1];
I ps[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(cnts,n,0);
    for(I i=0;i<n;i++)cnts[a_arr[i]-1]++;
    for(I i=0;i<=n;i++)for(I j=0;j<=n/2;j++)dp[i][j]=0;
    if(cnts[a_arr[n-1]-1]>1){printf("0\n");continue;}
    reverse(cnts,cnts+n);
    for(I i=0;i<n;i++)ps[i+1]=ps[i]+cnts[i];
    dp[n-1-(a_arr[n-2]-1)][1]=1;
    for(I i=1;i<n;i++)for(I j=0;j<=n/2;j++)if(dp[i][j]){
      I cnt=cnts[i];
      if(ps[i]+j==n){
        if(j>=cnt)(dp[i+1][j-cnt]+=dp[i][j]*bin(j,cnt))%=MOD;
      }else{
        if(cnt>=1&&j-1>=cnt-1)(dp[i+1][j-(cnt-1)+1]+=dp[i][j]*bin(j-1,cnt-1))%=MOD;
        if(j-1>=cnt)(dp[i+1][j-cnt]+=dp[i][j]*bin(j-1,cnt))%=MOD;
      }
    }
    printf("%lli\n",dp[n][0]);
  }
}
/*
process in decreasing order of value

we can either "distribute" or "add" for each individual block

if we distribute, we cannot distribute to the top of the stack, since it
dissatisfies the first condition once other (smaller) blocks are stacked

if we add, we must add to the top of the stack (leaving a gap for other
blocks)

however, once all n / 2 even positions have been occupied, this gap
restriction no longer applies, as no future blocks need to be considered
*/