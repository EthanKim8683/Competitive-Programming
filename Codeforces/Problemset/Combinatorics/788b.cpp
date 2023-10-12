#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e6;
vector<I>adjs[N];
B slfs[N];
B viss[N];
I dfs(I a){
  if(viss[a])return 0;
  viss[a]=1;
  I siz=1;
  for(auto b:adjs[a])siz+=dfs(b);
  return siz;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  Lli cnt=0;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    if(u!=v){
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }else{
      slfs[u]=1,cnt++;
    }
  }
  B trv=0;
  for(I i=0;i<n;i++){
    if(adjs[i].empty()&&!slfs[i])continue;
    if(viss[i])continue;
    if(trv){
      printf("0"),exit(0);
    }else{
      dfs(i),trv=1;
    }
  }
  Lli res=cnt*(cnt-1)/2+cnt*(m-cnt);
  for(I i=0;i<n;i++){
    Lli cur=adjs[i].size();
    res+=cur*(cur-1)/2;
  }
  printf("%lli\n",res);
}
/*
any path that traverses each road twice will always end where it first started,
meaning, if both singly-traversed edges are not self-loops, they must be
adjacent

in addition, any edgewise-connected graph can be fully traversed such that each
edge is traversed twice

this stupid fucking problem has like a million edge cases
*/