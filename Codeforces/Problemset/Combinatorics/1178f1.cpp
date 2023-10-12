#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=500;
const I M=N;
const I LOGM=9;
const Lli MOD=998244353;
I c_arr[M];
I spas[M][LOGM];
Lli dp1[M+1][M+1],dp2[M+1][M+1];
I inds[N+1];
I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return min(spas[l][d],spas[r-(1<<d)][d]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++)cin>>c_arr[i];
  for(I i=0;i<m;i++)inds[c_arr[i]]=i;
  for(I i=0;i<m;i++)spas[i][0]=c_arr[i];
  for(I i=1;i<LOGM;i++)for(I j=0;j+(1<<i)<=m;j++)spas[j][i]=min(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
  for(I i=0;i<=m;i++)dp1[i][i]=dp2[i][i]=1;
  for(I i=0;i<m;i++)dp1[i][i+1]=1,dp2[i][i+1]=2;
  for(I i=2;i<=m;i++)for(I j=0;j+i<=m;j++){
    I t=inds[qry(j,j+i)];
    (dp1[j][j+i]+=dp2[j][t]*dp2[t+1][j+i])%=MOD;
    for(I k=0;k<=i;k++)(dp2[j][j+i]+=dp1[j][j+k]*dp1[j+k][j+i])%=MOD;
  }
  printf("%lli\n",dp1[0][m]);
}
/*
since n = m and all colors are present, c must be a permutation and each
segment painting should paint exactly one color in c

we can use range dynamic programming to count the number of ways satisfying
the above property
*/