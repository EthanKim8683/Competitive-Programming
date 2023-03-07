#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100000;
vector<pair<I,I>>adjs[N];
I sizs[N];
B viss[N];
I pres[2*N+1];
map<I,I>cnts1,cnts2;
Lli res=0;
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto[b,t]:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto[b,t]:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs3(I a,I p,I x){
  if(x==0){
    res+=cnts1[0]+cnts2[0];
    if(pres[N+x])res+=1;
  }else{
    res+=cnts1[-x];
    if(pres[N+x])res+=cnts2[-x];
  }
  pres[N+x]++;
  for(auto[b,t]:adjs[a])if(b!=p&&!viss[b])dfs3(b,a,x+t);
  pres[N+x]--;
}
void dfs4(I a,I p,I x){
  pres[N+x]?cnts1[x]++:cnts2[x]++;
  pres[N+x]++;
  for(auto[b,t]:adjs[a])if(b!=p&&!viss[b])dfs4(b,a,x+t);
  pres[N+x]--;
}
void dfs5(I a){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  cnts1.clear(),cnts2.clear();
  for(auto[b,t]:adjs[a])if(!viss[b])dfs3(b,a,t),dfs4(b,a,t);
  for(auto[b,t]:adjs[a])if(!viss[b])dfs5(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("yinyang.in","r",stdin);
  freopen("yinyang.out","w",stdout);
#endif
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b,t;cin>>a>>b>>t,a--,b--,t=2*t-1;
    adjs[a].push_back({b,t});
    adjs[b].push_back({a,t});
  }
  dfs5(0);
  printf("%lli\n",res);
}