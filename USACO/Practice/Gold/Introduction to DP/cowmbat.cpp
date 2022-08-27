#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

using I=int;
using S=string;

const I N=1e5;
const I M=26;
const I MAX=1e9;

vector<pair<I,I>>adjs[M];
priority_queue<pair<I,I>>que;
I diss[M][M];
I ps[N+1][M];
I dp[N+1][M];

I main(){
#ifndef ETHANKIM8683
  freopen("cowmbat.in","r",stdin);
  freopen("cowmbat.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  S s;cin>>s;
  for(I i=0;i<m;i++)for(I j=0;j<m;j++){
    I a;cin>>a;
    adjs[i].push_back({j,a});
  }
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  for(I i=0;i<m;i++){
    while(que.size())que.pop();
    que.push({diss[i][i]=0,i});
    while(que.size()){
      auto[dis,a]=que.top();que.pop();
      if(dis!=diss[i][a])continue;
      for(auto[b,d]:adjs[a])
        if(dis+d<diss[i][b])
          que.push({diss[i][b]=dis+d,b});
    }
  }
  for(I i=0;i<m;i++){
    for(I j=0;j<n;j++)ps[j+1][i]+=diss[s[j]-'a'][i];
    for(I j=0;j<n;j++)ps[j+1][i]+=ps[j][i];
  }
  fill(&dp[0][0],&dp[0][0]+sizeof(dp)/sizeof(I),MAX);
  for(I i=0;i<m;i++)
    dp[k][i]=ps[k][i];
  for(I i=k;i<n;i++){
    if(i+k<=n){
      I cur=*min_element(dp[i],dp[i]+m);
      for(I j=0;j<26;j++)
        dp[i+k][j]=min(dp[i+k][j],cur+ps[i+k][j]-ps[i][j]);
    }
    for(I j=0;j<26;j++)
      dp[i+1][j]=min(dp[i+1][j],dp[i][j]+diss[s[i]-'a'][j]);
  }
  printf("%i\n",*min_element(dp[n],dp[n]+m));
  return 0;
}