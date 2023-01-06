#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
const I LOGN=17;
vector<pair<I,I>>adjs[N];
Lli mins[N-1],maxs[N-1];
set<Lli>vals1,vals2;
I cur=0;
I lea=0;
void dfs1(I a,I p=-1){
  if(adjs[a].size()<=1)lea=a;
  for(auto[b,i]:adjs[a])if(b!=p)dfs1(b,a);
}
void dfs2(I a,I p=-1){
  if(adjs[a].size()>1){
    cur++;
    B col=0;
    for(auto[b,i]:adjs[a])col|=mins[i];
    for(auto[b,i]:adjs[a]){
      maxs[i]<<=LOGN;
      maxs[i]|=cur;
      if(!col)mins[i]|=1;
    }
  }
  for(auto[b,i]:adjs[a])if(b!=p)dfs2(b,a);
}
void dfs3(I a,I p=-1){
  if(adjs[a].size()>1){
    cur++;
    B col=1;
    for(auto[b,i]:adjs[a])col&=mins[i];
    for(auto[b,i]:adjs[a])if(!col)mins[i]|=2;
  }
  for(auto[b,i]:adjs[a])if(b!=p)dfs3(b,a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back({b,i});
    adjs[b].push_back({a,i});
  }
  dfs1(0),dfs2(lea),dfs3(lea);
  for(I i=0;i<n-1;i++){
    vals1.insert(mins[i]);
    vals2.insert(maxs[i]);
  }
  printf("%i %i\n",vals1.size(),vals2.size());
}