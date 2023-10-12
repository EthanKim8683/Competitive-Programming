#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const I A=1000000;
const Lli MOD=1e9+7;
I a_arr[N];
I cnts[A+1];
Lli coms[N+1],pows[N+1];
Lli dp[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  pows[0]=1;
  for(I i=1;i<=n;i++)pows[i]=pows[i-1]*2%MOD;
  coms[1]=1;
  for(I i=2;i<=n;i++)coms[i]=(coms[i-1]*2+pows[i-1])%MOD;
  for(I i=0;i<n;i++)cnts[a_arr[i]]++;
  Lli res=0;
  for(I i=A;i>=2;i--){
    I cnt=0;
    for(I j=i;j<=A;j+=i)cnt+=cnts[j];
    dp[i]=coms[cnt];
    for(I j=2*i;j<=A;j+=i)(dp[i]-=dp[j])%=MOD;
    (res+=i*dp[i])%=MOD;
  }
  printf("%lli\n",(res+MOD)%MOD);
}