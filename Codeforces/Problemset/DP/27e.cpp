#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I P=7;
const I N=1000;
const Lli MAX=1e18;
I prms[]{2,3,5,7,11,13,17};
Lli dp[P+1][N+1];
void cmb(Lli&a,Lli b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(P+1)*(N+1),MAX);
  I n;cin>>n;
  dp[0][1]=1;
  for(I i=0;i<P;i++)for(I j=1;j<=n;j++){
    Lli fac=1;
    for(I k=0;(k+1)*j<=n;k++){
      cmb(dp[i+1][(k+1)*j],dp[i][j]*fac);
      if(MAX/(fac*dp[i][j])<prms[i])break;
      fac*=prms[i];
    }
  }
  printf("%lli\n",dp[P][n]);
}