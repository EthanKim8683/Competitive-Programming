#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I MAX=1e9;
vector<I>adjs1[N],adjs2[2*N],adjs3[2*N];
I dp[N][2];
I ress[N];
void dfs1(I a,I p=-1){
  B lea=1;I tot=0;
  for(auto b:adjs1[a])if(b!=p){
    dfs1(b,a),lea=0;
    tot+=min(dp[b][0]+2,dp[b][1]);
  }
  if(lea){dp[a][1]=MAX;return;}
  pair<I,I>sel={MAX,-1};
  for(auto b:adjs1[a])if(b!=p){
    I cur=tot;
    cur-=min(dp[b][0]+2,dp[b][1]);
    cur+=dp[b][0]+2;
    sel=min(sel,{cur,b});
  }
  auto[cst,c]=sel;
  adjs2[2*a+1].push_back(2*c);
  dp[a][1]=dp[c][0]+2;
  for(auto b:adjs1[a])if(b!=p){
    if(dp[b][0]+2<dp[b][1]){
      adjs2[2*a].push_back(2*b);
      dp[a][0]+=dp[b][0]+2;
    }else{
      adjs3[2*a].push_back(2*b+1);
      dp[a][0]+=dp[b][1];
    }
    if(b==c)continue;
    if(dp[b][0]+2<dp[b][1]){
      adjs2[2*a+1].push_back(2*b);
      dp[a][1]+=dp[b][0]+2;
    }else{
      adjs3[2*a+1].push_back(2*b+1);
      dp[a][1]+=dp[b][1];
    }
  }
}
I dfs2(I a,I c){
  ress[a/2]=c/2,c=a;
  for(auto b:adjs2[a])c=dfs2(b,c);
  for(auto b:adjs3[a])ress[b/2]=dfs2(b,b)/2;
  return c;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs1[a].push_back(b);
    adjs1[b].push_back(a);
  }
  dfs1(0),ress[0]=dfs2(1,1)/2;
  printf("%i\n",dp[0][1]);
  for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
}