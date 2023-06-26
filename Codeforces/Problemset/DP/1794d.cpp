#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2022;
const I A=1e6;
const Lli MOD=998244353;
B eras[A+1];
I cnts[A+1];
Lli facs[2*N+1];
Lli invs[2*N+1];
vector<I>prms;
Lli dp[2*N+1][N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  eras[0]=eras[1]=1;
  for(I i=2;i*i<=A;i++)if(!eras[i])for(I j=i*i;j<=A;j+=i)eras[j]=1;
  I n;cin>>n;
  for(I i=0;i<2*n;i++){
    I a;cin>>a;
    cnts[a]++;
  }
  facs[0]=1;
  for(I i=1;i<=2*n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<=2*n;i++)invs[i]=inv(facs[i]);
  for(I i=1;i<=A;i++)if(cnts[i])prms.push_back(i);
  I m=prms.size();
  dp[0][0]=facs[n];
  for(I i=0;i<m;i++)for(I j=0;j<=n;j++){
    I a=prms[i];
    (dp[i+1][j]+=dp[i][j]*invs[cnts[a]])%=MOD;
    if(!eras[a]&&j+1<=n)(dp[i+1][j+1]+=dp[i][j]*invs[cnts[a]-1])%=MOD;
  }
  printf("%lli\n",dp[m][n]);
}