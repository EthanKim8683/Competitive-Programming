#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e3;
const Lli MOD=1e9+7;

I p_arr[N];
Lli dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){I p;cin>>p,p_arr[i]=p-1;}
  for(I i=0;i<n;i++){
    dp[i]=2;
    for(I j=p_arr[i];j<i;j++)(dp[i]+=dp[j])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<n;i++)(res+=dp[i])%=MOD;
  printf("%lli\n",res);
}