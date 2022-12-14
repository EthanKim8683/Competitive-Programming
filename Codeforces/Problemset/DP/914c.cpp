#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I M=1000;
const Lli MOD=1e9+7;
I dp1[M+1];
Lli dp2[M+1][M+1][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  dp1[1]=0;
  for(I i=2;i<=M;i++)dp1[i]=dp1[__builtin_popcount(i)]+1;
  S n;cin>>n;
  I k;cin>>k;
  if(k==0)printf("1\n"),exit(0);
  I m=n.size();
  dp2[0][0][0]=1;
  for(I i=0;i<m;i++)for(I j=0;j<=i;j++){
    if(n[i]=='1'){
      (dp2[i+1][j+0][1]+=dp2[i][j][0])%=MOD;
      (dp2[i+1][j+1][0]+=dp2[i][j][0])%=MOD;
    }else{
      (dp2[i+1][j+0][0]+=dp2[i][j][0])%=MOD;
    }
    (dp2[i+1][j+0][1]+=dp2[i][j][1])%=MOD;
    (dp2[i+1][j+1][1]+=dp2[i][j][1])%=MOD;
  }
  Lli res=0;
  for(I i=1;i<=m;i++)if(dp1[i]+1==k)
    (res+=dp2[m][i][0]+dp2[m][i][1]-(i==1))%=MOD;
  printf("%lli\n",res);
}