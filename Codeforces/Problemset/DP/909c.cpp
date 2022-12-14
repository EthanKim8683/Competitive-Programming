#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
const I N=5000;
const Lli MOD=1e9+7;
Lli dp[N][N+1];
Lli ps[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  dp[0][0]=1;
  for(I i=0;i+1<n;i++){
    C c;cin>>c;
    if(c=='f'){
      for(I j=0;j<=i;j++)(dp[i+1][j+1]+=dp[i][j])%=MOD;
    }else{
      copy_n(dp[i],i+1,ps);
      for(I j=i;j-1>=0;j--)(ps[j-1]+=ps[j])%=MOD;
      for(I j=0;j<=i;j++)(dp[i+1][j]+=ps[j])%=MOD;
    }
  }
  Lli res=0;
  for(I i=0;i<=n;i++)(res+=dp[n-1][i])%=MOD;
  printf("%lli\n",res);
}