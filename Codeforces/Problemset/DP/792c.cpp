#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
const I L=1e5;
const I MAX=1e9;
tuple<I,I,I>dp[L+1][2][3];
vector<C>ress;
void cmb(tuple<I,I,I>&a,tuple<I,I,I>b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(L+1)*2*3,tuple<I,I,I>{MAX,-1,-1});
  S n;cin>>n;
  I l=n.size();
  dp[0][0][0]={0,-1,-1};
  for(I i=0;i<l;i++)for(I j=0;j<2;j++)for(I k=0;k<3;k++){
    I d=n[i]-'0';
    if(d){
      cmb(dp[i+1][1][(k+d)%3],{get<0>(dp[i][j][k]),j,k});
      cmb(dp[i+1][j][k],{get<0>(dp[i][j][k])+1,j,k});
    }else{
      cmb(dp[i+1][1][k],{get<0>(dp[i][1][k]),1,k});
      cmb(dp[i+1][j][k],{get<0>(dp[i][j][k])+1,j,k});
    }
  }
  if(get<0>(dp[l][1][0])==MAX){
    for(auto d:n)if(d=='0')printf("0"),exit(0);
    printf("-1"),exit(0);
  }
  I j1=1,k1=0;
  for(I i=l;i>0;i--){
    auto[cur,j2,k2]=dp[i][j1][k1];
    if(cur==get<0>(dp[i-1][j2][k2]))ress.push_back(n[i-1]);
    j1=j2,k1=k2;
  }
  reverse(ress.begin(),ress.end());
  for(auto d:ress)printf("%c",d);
}