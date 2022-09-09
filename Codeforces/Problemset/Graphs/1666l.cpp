#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

vector<I>adjs[N];
vector<I>stks;
I viss1[N];
B viss2[N];
I t=-1,x,y;
I s;

void dfs1(I a,I r){
  if(a==s)return;
  if(viss1[a]!=-1){
    if(viss1[a]!=r){t=a,x=viss1[a],y=r;return;}
    if(viss1[a]==r)return;
  }
  viss1[a]=r;
  for(auto b:adjs[a])dfs1(b,r);
}

B dfs2(I a){
  if(a==s)return 0;
  if(a==t)return 1;
  if(viss2[a])return 0;
  viss2[a]=1;
  stks.push_back(a);
  for(auto b:adjs[a])if(dfs2(b))return 1;
  stks.pop_back();
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>s,s--;
  fill_n(viss1,n,-1);
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
  }
  for(auto b:adjs[s]){
    dfs1(b,b);
    if(t!=-1)break;
  }
  if(t==-1){printf("Impossible\n");return 0;}
  printf("Possible\n");
  dfs2(x);
  printf("%i\n",stks.size()+2);
  printf("%i ",s+1);
  for(auto i:stks)printf("%i ",i+1);
  printf("%i\n",t+1);
  stks.clear();
  dfs2(y);
  printf("%i\n",stks.size()+2);
  printf("%i ",s+1);
  for(auto i:stks)printf("%i ",i+1);
  printf("%i\n",t+1);
  return 0;
}