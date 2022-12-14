#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=5000;
const I MAX=1e9;
const I MIN=-MAX;
pair<I,I>dp[N][N];
pair<I,I>fix(I l,I r){
  l=max(l,0);
  if(l>r)return{MAX,MIN};
  return{l,r};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*N,pair<I,I>{MAX,MIN});
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i+1<n;i++){
    if(s[i]=='(')dp[i][i]=fix(1,1);
    if(s[i]=='?')dp[i][i]=fix(-1,1);
    for(I j=0;j<n;j++){
      auto[l,r]=dp[i][j];
      if(s[i+1]=='(')dp[i+1][j]=fix(l+1,r+1);
      if(s[i+1]==')')dp[i+1][j]=fix(l-1,r-1);
      if(s[i+1]=='?')dp[i+1][j]=fix(l-1,r+1);
    }
  }
  I res=0;
  for(I i=0;i<n;i++)for(I j=0;j<=i;j++){
    auto[l,r]=dp[i][j];
    res+=l<=0&&r>=0&&(i-j)%2;
  }
  printf("%i\n",res);
}