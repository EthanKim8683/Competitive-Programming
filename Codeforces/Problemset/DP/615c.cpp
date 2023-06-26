#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=2100;
const I M=2100;
const I MAX=1e9;
pair<I,I>dp[N][2*M];
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*(2*M),pair<I,I>{MAX,-1});
  S s;cin>>s;
  S t;cin>>t;
  I n=t.size(),m=s.size();
  for(I i=0;i<m;i++)if(t[0]==s[i])dp[0][i]=dp[0][m+i]=min(dp[0][i],{1,-1});
  for(I i=0;i+1<n;i++){
    I k=min_element(dp[i],dp[i]+2*m)-dp[i];
    for(I j=0;j<m;j++)if(t[i+1]==s[j]){
      if(j-1>=0)dp[i+1][j]=min(dp[i+1][j],{dp[i][j-1].first,j-1});
      dp[i+1][j]=min(dp[i+1][j],{dp[i][k].first+1,k});
    }
    for(I j=m-1;j>=0;j--)if(t[i+1]==s[j]){
      if(j+1<m)dp[i+1][m+j]=min(dp[i+1][m+j],{dp[i][m+j+1].first,m+j+1});
      dp[i+1][m+j]=min(dp[i+1][m+j],{dp[i][k].first+1,k});
    }
  }
  I j1=min_element(dp[n-1],dp[n-1]+2*m)-dp[n-1],cnt1=dp[n-1][j1].first;
  if(cnt1==MAX)printf("-1\n"),exit(0);
  ress.push_back(j1);
  for(I i=n-1;i>0;i--){
    auto[cnt2,j2]=dp[i][j1];
    if(cnt2!=dp[i-1][j2].first)ress.push_back(j1),ress.push_back(j2);
    cnt1=cnt2,j1=j2;
  }
  ress.push_back(j1);
  reverse(ress.begin(),ress.end());
  printf("%i\n",ress.size()/2);
  for(I i=0;i<ress.size();i+=2)printf("%i %i\n",ress[i]%m+1,ress[i+1]%m+1);
}