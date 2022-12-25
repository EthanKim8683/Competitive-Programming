#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2000;
const I M=2000;
const I C=50;
const Lli MIN=-1e18;
vector<tuple<Lli,I,Lli>>trns;
Lli dp[2][N*C+1];
void cmb(Lli&a,Lli b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+2*(N*C+1),MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I c;Lli f,v;cin>>c>>f>>v;
    trns.push_back({f,c,-v});
  }
  I m;cin>>m;
  for(I i=0;i<m;i++){
    I c;Lli f,v;cin>>c>>f>>v;
    trns.push_back({f,-c,v});
  }
  sort(trns.begin(),trns.end());
  reverse(trns.begin(),trns.end());
  Lli res=MIN;
  dp[0][0]=0;
  for(I i=0;i<trns.size();i++){
    auto[f,c,v]=trns[i];
    for(I j=0;j<=n*C;j++){
      if(j+c>=0)cmb(dp[(i+1)%2][j+c],dp[i%2][j]+v);
      cmb(dp[(i+1)%2][j],dp[i%2][j]);
      cmb(res,dp[i%2][j]);
    }
    for(I j=0;j<=n*C;j++)dp[i%2][j]=MIN;
  }
  for(I i=0;i<=n*C;i++)cmb(res,dp[trns.size()%2][i]);
  printf("%lli\n",res);
}