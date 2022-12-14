#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I R=5e6;
const Lli MOD=1e9+7;
Lli dp[R+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=1;i<=R;i++)dp[i]=((Lli)i*(i-1)/2)%MOD;
  for(I i=2;i<=R;i++)for(I j=2;j<=i&&i*j<=R;j++)dp[i*j]=(dp[i]+i*dp[j])%MOD;
  I t,l,r;cin>>t>>l>>r;
  Lli pow=1,res=0;
  for(I i=l;i<=r;i++){
    (res+=pow*dp[i])%=MOD;
    (pow*=t)%=MOD;
  }
  printf("%lli\n",res);
}