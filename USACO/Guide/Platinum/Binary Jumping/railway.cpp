#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I LOGN=17;
vector<pair<I,I>>adjs[N];
set<I>incs[N];
vector<I>rems[N];
I ancs[N][LOGN];
I tbgs[N],teds[N];
vector<I>ress;
I t=0;
I k;
void dfs1(I a,I p){
  tbgs[a]=t++;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto[b,i]:adjs[a])if(b!=p)dfs1(b,a);
  teds[a]=t;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}
void dfs2(I a,I p=-1){
  for(auto[b,i]:adjs[a])if(b!=p){
    dfs2(b,a);
    if(incs[b].size()>=k)ress.push_back(i);
    if(incs[a].size()<incs[b].size())swap(incs[a],incs[b]);
    for(auto x:incs[b])incs[a].insert(x);
  }
  for(auto x:rems[a])incs[a].erase(x);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>k;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back({b,i});
    adjs[b].push_back({a,i});
  }
  dfs1(0,0);
  for(I i=0;i<m;i++){
    I s;cin>>s;
    I y=-1;
    for(I j=0;j<s;j++){
      I x;cin>>x,x--;
      y=y==-1?x:lca(y,x);
      incs[x].insert(i);
    }
    rems[y].push_back(i);
  }
  dfs2(0);
  sort(ress.begin(),ress.end());
  printf("%i\n",ress.size());
  for(auto x:ress)printf("%i ",x+1);
}