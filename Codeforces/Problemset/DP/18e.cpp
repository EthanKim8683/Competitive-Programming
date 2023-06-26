#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=500;
const I M=500;
const I MAX=1e9;
C flgs[N][M+1];
I cnts[N][2][26];
I csts[N][26][26];
tuple<I,I,I>dp[N][26][26];
pair<I,I>upps1[N-1][26],upps2[N-1][26];
pair<I,I>ress[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&csts[0][0][0],&csts[0][0][0]+N*26*26,MAX);
  fill(&dp[0][0][0],&dp[0][0][0]+N*26*26,tuple<I,I,I>{MAX,-1,-1});
  fill(&upps1[0][0],&upps1[0][0]+(N-1)*26,pair<I,I>{MAX,-1});
  fill(&upps2[0][0],&upps2[0][0]+(N-1)*26,pair<I,I>{MAX,-1});
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>flgs[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cnts[i][j%2][flgs[i][j]-'a']++;
  for(I i=0;i<n;i++)for(I j=0;j<26;j++)for(I k=0;k<26;k++)if(j!=k)csts[i][j][k]=m-cnts[i][1][j]-cnts[i][0][k];
  for(I i=0;i<26;i++)for(I j=0;j<26;j++)if(i!=j)dp[0][i][j]={csts[0][i][j],-1,-1};
  for(I i=0;i+1<n;i++){
    for(I j=0;j<26;j++)for(I k=0;k<26;k++)if(j!=k){
      if(get<0>(dp[i][j][k])<upps1[i][j].first){
        upps2[i][j]=upps1[i][j];
        upps1[i][j]={get<0>(dp[i][j][k]),k};
        continue;
      }
      if(get<0>(dp[i][j][k])<upps2[i][j].first){
        upps2[i][j]={get<0>(dp[i][j][k]),k};
        continue;
      }
    }
    for(I j=0;j<26;j++)for(I k=0;k<26;k++)if(j!=k)for(I l=0;l<26;l++)if(l!=j){
      if(upps1[i][l].second!=k){dp[i+1][j][k]=min(dp[i+1][j][k],{upps1[i][l].first+csts[i+1][j][k],l,upps1[i][l].second});continue;}
      if(upps2[i][l].second!=k){dp[i+1][j][k]=min(dp[i+1][j][k],{upps2[i][l].first+csts[i+1][j][k],l,upps2[i][l].second});continue;}
    }
  }
  tuple<I,I,I>res={MAX,-1,-1};
  for(I i=0;i<26;i++)for(I j=0;j<26;j++)if(i!=j)res=min(res,{get<0>(dp[n-1][i][j]),i,j});
  auto[tot,j,k]=res;
  printf("%i\n",tot);
  for(I i=n-1;i>=0;i--)ress[i]={j,k},tie(tot,j,k)=dp[i][j][k];
  for(I i=0;i<n;i++){
    auto[a,b]=ress[i];
    for(I j=0;j<m;j++)printf("%c",(j%2?a:b)+'a');
    printf("\n");
  }
}