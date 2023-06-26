#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I L=10;
const I K=7;
const Lli MOD=1e9+7;
vector<I>dgts;
I dp1[L+1][1<<L][2];
I cnts[L+1];
Lli dp2[K][L+1];
Lli facs[K],bins[K],invs[K];
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
  facs[0]=1;
  for(I i=1;i<K;i++)facs[i]=facs[i-1]*(i+1)%MOD;
  for(I i=0;i<K;i++)invs[i]=inv(facs[i]);
  I m;cin>>m;
  for(I i=m;i;i/=10)dgts.push_back(i%10);
  while(dgts.size()<L)dgts.push_back(0);
  reverse(dgts.begin(),dgts.end());
  dp1[0][0][1]=1;
  for(I i=0;i<L;i++)for(I j=0;j<(1<<L);j++){
    I d=dgts[i];
    dp1[i+1][j][0]+=8*dp1[i][j][0];
    dp1[i+1][j][0]+=(d-(d>4)-(d>7))*dp1[i][j][1];
    dp1[i+1][j][1]+=(d!=4&&d!=7)*dp1[i][j][1];
    dp1[i+1][j|1<<i][0]+=2*dp1[i][j][0];
    dp1[i+1][j|1<<i][0]+=((d>4)+(d>7))*dp1[i][j][1];
    dp1[i+1][j|1<<i][1]+=(d==4||d==7)*dp1[i][j][1];
  }
  for(I i=0;i<(1<<L);i++)for(I j=0;j<2;j++)cnts[__builtin_popcount(i)]+=dp1[L][i][j];
  cnts[0]--;
  Lli res=0;
  dp2[0][0]=1;
  for(I i=0;i<=L;i++){
    I cnt=cnts[i];
    bins[0]=cnt;
    for(I j=1;j<K;j++)bins[j]=bins[j-1]*(cnt-j)%MOD;
    for(I j=0;j<K;j++)(bins[j]*=invs[j])%=MOD;
    for(I j=0;j<i;j++)(res+=dp2[K-1][j]*cnt)%=MOD;
    for(I j=K-1;j>=0;j--)for(I k=L;k>=0;k--)for(I l=1;l<=min(K,cnt);l++){
      if(j+l<K&&k+i*l<=L)(dp2[j+l][k+i*l]+=dp2[j][k]*bins[l-1])%=MOD;
    }
  }
  (res*=facs[K-2])%=MOD;
  printf("%lli\n",res);
}