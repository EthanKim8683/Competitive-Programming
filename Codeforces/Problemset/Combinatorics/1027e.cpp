#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=500;
const Lli MOD=998244353;
Lli dp1[N+1][N+1];
Lli dp2[N+1][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  dp1[0][0]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=i;j++)for(I l=1;i+l<=n;l++)(dp1[i+l][max(j,l)]+=dp1[i][j])%=MOD;
  Lli res=0;
  for(I i=1;i<=n;i++){
    fill(&dp2[0][0],&dp2[0][0]+(N+1)*(N+1),0);
    if(i*1<k)dp2[1][1]=1;
    for(I j=1;j<n;j++)for(I l=1;l<=j;l++){
      if(i*(l+1)<k)(dp2[j+1][l+1]+=dp2[j][l])%=MOD;
      (dp2[j+1][1]+=dp2[j][l])%=MOD;
    }
    for(I j=1;j<=n;j++)(res+=dp2[n][j]*dp1[n][i])%=MOD;
  }
  printf("%lli\n",2*res%MOD);
}
/*
all beautiful colorings look like checkerboards but with not necessarily even
tiles

however, since the pattern in the first row is preserved throughout the
checkerboard, we can first count the number of first-row colorings such that
the maximum tile width is a value w

then, we can use dynamic programming to count, for each checkerboard with
first row colorings of maximum tile width w, the number of suitable row
colorings
*/