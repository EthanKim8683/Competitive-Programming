#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1000;
const I M=1000;
const I K=10;
const Lli MOD=1000000009;

I fj[N],fp[M];
Lli dp[N+1][K+1][M+1];

I main(){
#ifndef ETHANKIM8683
  freopen("team.in","r",stdin);
  freopen("team.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>fj[i];
  for(I i=0;i<m;i++)cin>>fp[i];
  sort(fj,fj+n,greater<I>());
  sort(fp,fp+m,greater<I>());
  dp[0][0][0]=1;
  for(I i=0;i<n;i++){
    for(I j=k;j>=0;j--){
      Lli acc=0;
      for(I l=0;l<=m;l++){
        (acc+=dp[i][j][l])%=MOD;
        (dp[i+1][j][l]+=dp[i][j][l])%=MOD;
        if(l<m&&fj[i]>fp[l]&&j+1<=k)
          (dp[i+1][j+1][l+1]+=acc)%=MOD;
      }
    }
  }
  Lli res=0;
  for(I i=0;i<=m;i++)
    (res+=dp[n][k][i])%=MOD;
  printf("%lli\n",res);
  return 0;
}