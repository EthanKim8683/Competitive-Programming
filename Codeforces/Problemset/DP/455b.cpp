#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1e5;
S strs[N];
I nods[N][26];
vector<I>adjs[26*N];
I dp[N][2];
I cur=0;
void add(S s){
  for(I i=0,j=0;i<s.size();i++){
    I c=s[i]-'a';
    if(nods[j][c]<0)nods[j][c]=++cur;
    j=nods[j][c];
  }
}
void dfs(I a,I t=0){
  dp[a][0]=-1;
  dp[a][1]=-1;
  for(auto b:adjs[a]){
    dfs(b,!t);
    if(dp[a][0]!=t)dp[a][0]=dp[b][0];
    if(dp[a][1]!=!t)dp[a][1]=dp[b][1];
  }
  if(dp[a][0]==-1)dp[a][0]=!t;
  if(dp[a][1]==-1)dp[a][1]=!t;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&nods[0][0],&nods[0][0]+N*26,-1);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>strs[i];
  for(I i=0;i<n;i++)add(strs[i]);
  for(I i=0;i<=cur;i++)for(I j=0;j<26;j++){
    I k=nods[i][j];
    if(k==-1)continue;
    adjs[i].push_back(k);
  }
  dfs(0);
  if(dp[0][0]==0&&dp[0][1]==0)printf("%s\n",k%2?"First":"Second");
  if(dp[0][0]==0&&dp[0][1]==1)printf("First\n");
  if(dp[0][0]==1&&dp[0][1]==0)printf("Second\n");
  if(dp[0][0]==1&&dp[0][1]==1)printf("Second\n");
}