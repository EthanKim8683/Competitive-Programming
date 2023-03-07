#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
vector<I>adjs[N];
I sizs[N];
B viss[N];
map<I,I>cnts;
I k;
Lli res=0;
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs3(I a,I p,I d){
  res+=cnts[k-d];
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs3(b,a,d+1);
}
void dfs4(I a,I p,I d){
  cnts[d]++;
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs4(b,a,d+1);
}
void dfs5(I a){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  cnts.clear();
  cnts[0]++;
  for(auto b:adjs[a])if(!viss[b])dfs3(b,a,1),dfs4(b,a,1);
  for(auto b:adjs[a])if(!viss[b])dfs5(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs5(0);
  printf("%lli\n",res);
}