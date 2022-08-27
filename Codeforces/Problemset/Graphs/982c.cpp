#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];
I subs[N];
I res=0;

void dfs(I a,I p=-1){
  subs[a]+=1;
  for(auto b:adjs[a]){
    if(b==p)continue;
    dfs(b,a);
    if(subs[b]%2==0)res++;
    subs[a]+=subs[b];
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  if(n%2){printf("-1\n");return 0;}
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs(0);
  printf("%i\n",res);
  return 0;
}