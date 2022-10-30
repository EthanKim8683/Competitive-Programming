#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=100000;
const I M=100000;
const Lli MOD=1e9+7;

Lli dp1[N+1][2];
Lli dp2[M+1][2];

I main(){
  I n,m;cin>>n>>m;
  dp1[0][0]=dp1[0][1]=dp2[0][0]=dp2[0][1]=1;
  for(I i=0;i<n;i++){
    if(i+1<=n){
      (dp1[i+1][0]+=dp1[i][1])%=MOD;
      (dp1[i+1][1]+=dp1[i][0])%=MOD;
    }
    if(i+2<=n){
      (dp1[i+2][0]+=dp1[i][1])%=MOD;
      (dp1[i+2][1]+=dp1[i][0])%=MOD;
    }
  }
  for(I i=0;i<m;i++){
    if(i+1<=m){
      (dp2[i+1][0]+=dp2[i][1])%=MOD;
      (dp2[i+1][1]+=dp2[i][0])%=MOD;
    }
    if(i+2<=m){
      (dp2[i+2][0]+=dp2[i][1])%=MOD;
      (dp2[i+2][1]+=dp2[i][0])%=MOD;
    }
  }
  Lli res=MOD-2;
  (res+=dp1[n][0]+dp1[n][1])%=MOD;
  (res+=dp2[m][0]+dp2[m][1])%=MOD;
  printf("%lli\n",res);
}