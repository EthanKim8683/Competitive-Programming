#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I K=6;
const Lli MOD=1e9+7;
I a_arr[N];
Lli dp[1<<K][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill(&dp[0][0],&dp[0][0]+(1<<K)*2,0);
    dp[(1<<K)-1][0]=1;
    for(I i=0;i<n;i++)for(I j=0;j<(1<<K);j++)for(I l=1;l>=0;l--)(dp[j&a_arr[i]][1]+=dp[j][l])%=MOD;
    Lli res=0;
    for(I i=0;i<(1<<K);i++)if(__builtin_popcount(i)==k)(res+=dp[i][1])%=MOD;
    printf("%lli\n",res);
  }
}
/*
dynamic programming
*/