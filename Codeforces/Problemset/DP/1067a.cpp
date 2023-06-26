#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I A=200;
const Lli MOD=998244353;
I a_arr[N];
Lli dp[2][A+1][4];
Lli ps[A+2][4];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I a=a_arr[0];
  if(a==-1)for(I i=1;i<=A;i++)dp[0][i][0]=dp[0][i][1]=1;
  if(a!=-1)dp[0][a][0]=dp[0][a][1]=1;
  for(I i=1;i<n;i++){
    for(I j=1;j<=A;j++)for(I k=0;k<4;k++)ps[j+1][k]=(ps[j][k]+dp[(i-1)%2][j][k])%MOD;
    I a=a_arr[i];
    if(a==-1){
      for(I j=1;j<=A;j++){
        for(I k=0;k<4;k++)dp[i%2][j][k]=0;
        (dp[i%2][j][0]+=ps[j][3]-ps[1][3])%=MOD;
        (dp[i%2][j][0]+=ps[j+1][0]-ps[1][0])%=MOD;
        (dp[i%2][j][1]+=ps[j][3]-ps[1][3])%=MOD;
        (dp[i%2][j][1]+=ps[j][0]-ps[1][0])%=MOD;
        (dp[i%2][j][2]+=dp[(i-1)%2][j][1])%=MOD;
        (dp[i%2][j][2]+=dp[(i-1)%2][j][2])%=MOD;
        (dp[i%2][j][3]+=ps[A+1][2]-ps[j+1][2])%=MOD;
        (dp[i%2][j][3]+=ps[A+1][3]-ps[j][3])%=MOD;
      }
    }
    if(a!=-1){
      for(I j=1;j<=A;j++)for(I k=0;k<4;k++)dp[i%2][j][k]=0;
      (dp[i%2][a][0]+=ps[a][3]-ps[1][3])%=MOD;
      (dp[i%2][a][0]+=ps[a+1][0]-ps[1][0])%=MOD;
      (dp[i%2][a][1]+=ps[a][3]-ps[1][3])%=MOD;
      (dp[i%2][a][1]+=ps[a][0]-ps[1][0])%=MOD;
      (dp[i%2][a][2]+=dp[(i-1)%2][a][1])%=MOD;
      (dp[i%2][a][2]+=dp[(i-1)%2][a][2])%=MOD;
      (dp[i%2][a][3]+=ps[A+1][2]-ps[a+1][2])%=MOD;
      (dp[i%2][a][3]+=ps[A+1][3]-ps[a][3])%=MOD;
    }
  }
  Lli res=0;
  for(I i=1;i<=A;i++)for(I j=2;j<4;j++)(res+=dp[(n-1)%2][i][j])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}