#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3000;
const Lli MAX=1e18;
pair<I,I>mars[N];
Lli dp[N][N];
void cmb(Lli&a,Lli b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*N,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,c;cin>>x>>c;
    mars[i]={x,c};
  }
  sort(mars,mars+n);
  dp[0][0]=mars[0].second;
  for(I i=1;i<n;i++)for(I j=0;j<=i;j++){
    auto[xi,ci]=mars[i];
    auto[xj,cj]=mars[j];
    cmb(dp[i][j],dp[i-1][j]+xi-xj);
    cmb(dp[i][i],dp[i-1][j]+xi-xi+ci);
  }
  printf("%lli\n",*min_element(dp[n-1],dp[n-1]+n));
}