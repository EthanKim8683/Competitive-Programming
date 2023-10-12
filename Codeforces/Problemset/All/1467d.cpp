#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5000;
const I K=5000;
const Lli MOD=1e9+7;
I a_arr[N];
Lli cnts[N+1];
Lli dp[K+1][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k,q;cin>>n>>k>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)dp[0][i]=1;
  for(I i=0;i<k;i++)for(I j=0;j<n;j++){
    if(j-1>=0)(dp[i+1][j-1]+=dp[i][j])%=MOD;
    if(j+1<n)(dp[i+1][j+1]+=dp[i][j])%=MOD;
  }
  for(I i=0;i<=k;i++)for(I j=0;j<n;j++)(cnts[j]+=dp[i][j]*dp[k-i][j]%MOD)%=MOD;
  Lli cur=0;
  for(I i=0;i<n;i++)(cur+=cnts[i]*a_arr[i]%MOD)%=MOD;
  while(q--){
    I i,x;cin>>i>>x,i--;
    (cur-=cnts[i]*a_arr[i]%MOD)%=MOD,a_arr[i]=x,(cur+=cnts[i]*a_arr[i]%MOD)%=MOD;
    printf("%lli\n",(cur+MOD)%MOD);
  }
}