#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using C=char;
const I N=1e5;
vector<I>adjs[N];
I sizs[N];
B viss[N];
C ress[N];
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs3(I a,I d=0){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  ress[a]=d+'A';
  for(auto b:adjs[a])if(!viss[b])dfs3(b,d+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs3(0);
  for(I i=0;i<n;i++)printf("%c ",ress[i]);
}