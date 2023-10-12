#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I K=N;
const I M=1<<10;
const Lli MOD=1e9+7;
I a_arr[N];
I cnts[M+1];
Lli dp[K+1];
Lli facs[K+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  if(n<0||n-k<0||k<0)return 0;
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=K;i++)facs[i]=facs[i-1]*i%MOD;
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I rem=n;
  for(I i=0;i<n;i++){
    I bin=1;
    for(I a=a_arr[i];a;a/=10){
      if(a%10==4){
        bin=bin<<1|0;
      }else if(a%10==7){
        bin=bin<<1|1;
      }else{
        bin=-1;
        break;
      }
    }
    if(bin!=-1)cnts[bin]++,rem--;
  }
  dp[0]=1;
  for(I i=1;i<M;i++)for(I j=k-1;j>=0;j--)(dp[j+1]+=dp[j]*cnts[i])%=MOD;
  Lli res=0;
  for(I i=0;i<=k;i++)(res+=dp[i]*bin(rem,k-i))%=MOD;
  printf("%lli\n",res);
}
/*
we can use dynamic programming to choose, among each lucky number (all 1022 of
them), which occurrence, if any, to be part of the subsequence

if there's still space, we can choose from any unlucky number the requisite
number of remaining elements
*/