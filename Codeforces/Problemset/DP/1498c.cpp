#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1000;
const I K=1000;
const Lli MOD=1e9+7;

Lli dp[K-1][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<k-1;i++)for(I j=0;j<n;j++)dp[i][j]=0;
    fill_n(dp[0],n,1);
    for(I i=0;i+1<k-1;i++){
      if(i%2==0){
        for(I j=0;j+1<n;j++)dp[i+1][j+1]=dp[i][j];
        for(I j=0;j+1<n;j++)(dp[i+1][j+1]+=dp[i+1][j])%=MOD;
      }else{
        for(I j=n-1;j>0;j--)dp[i+1][j-1]=dp[i][j];
        for(I j=n-1;j>0;j--)(dp[i+1][j-1]+=dp[i+1][j])%=MOD;
      }
    }
    Lli res=1;
    for(I i=0;i<k-1;i++)for(I j=0;j<n;j++)(res+=dp[i][j])%=MOD;
    printf("%lli\n",res);
  }
}