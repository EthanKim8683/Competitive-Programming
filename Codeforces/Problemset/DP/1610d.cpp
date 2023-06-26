#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I LOGA=60;
const Lli MOD=1e9+7;
I a_arr[N];
Lli dp[N+1][LOGA+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)a_arr[i]=__builtin_ctz(a_arr[i]);
  sort(a_arr,a_arr+n);
  reverse(a_arr,a_arr+n);
  Lli res=0;
  for(I i=0;i<n;i++){
    I x=a_arr[i],y=max(x-1,0);
    for(I j=0;j<=LOGA;j++){
      I z=y<j?y:y>j?j:j+1;
      if(z>=x)(res+=dp[i][j])%=MOD;
      (dp[i+1][z]+=dp[i][j])%=MOD;
      (dp[i+1][j]+=dp[i][j])%=MOD;
    }
    if(y>=x)(res+=1)%=MOD;
    (dp[i+1][y]+=1)%=MOD;
  }
  printf("%lli\n",res);
}