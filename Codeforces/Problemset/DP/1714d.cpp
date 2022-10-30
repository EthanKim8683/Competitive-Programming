#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I M=100;
const I N=10;
const I MAX=1e9;

S s_arr[N];
vector<I>lfts[M],rgts[M];
I dp[M][M];
pair<I,I>pars[M][M];
B viss[M][M];
vector<pair<I,I>>ress;

I dfs(I l,I r){
  if(r<l)return MAX;
  if(viss[l][r])return dp[l][r];
  viss[l][r]=1;
  for(auto i:lfts[l])for(I j=0;j<s_arr[i].size();j++){
    I cur=dfs(l+j+1,r)+1;
    if(cur>dp[l][r])continue;
    dp[l][r]=cur,pars[l][r]={+j+1,i};
  }
  for(auto i:rgts[r])for(I j=0;j<s_arr[i].size();j++){
    I cur=dfs(l,r-j-1)+1;
    if(cur>dp[l][r])continue;
    dp[l][r]=cur,pars[l][r]={-j-1,i};
  }
  return dp[l][r];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    S t;cin>>t;
    I m=t.size();
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>s_arr[i];
    for(I i=0;i<m;i++)for(I j=i;j<m;j++)viss[i][j]=0,dp[i][j]=MAX;
    for(I i=0;i<m;i++)lfts[i].clear(),rgts[i].clear();
    for(I i=0;i<n;i++){
      S s=s_arr[i];
      I k=s.size();
      for(I j=0;j+k<=m;j++){
        if(t.substr(j,k)!=s)continue;
        lfts[j].push_back(i);
        rgts[j+k-1].push_back(i);
        viss[j][j+k-1]=1,dp[j][j+k-1]=1,pars[j][j+k-1]={-1,i};
      }
    }
    I res=dfs(0,m-1);
    if(res==MAX){printf("-1\n");continue;}
    I l=0,r=m-1;
    ress.clear();
    for(I i=0;i<res;i++){
      auto[m,j]=pars[l][r];
      I k=s_arr[j].size();
      if(m>0)ress.push_back({j,l}),l+=m;
      if(m<0)ress.push_back({j,r-k+1}),r+=m;
    }
    printf("%i\n",res);
    for(auto[w,p]:ress)printf("%i %i\n",w+1,p+1);
  }
}