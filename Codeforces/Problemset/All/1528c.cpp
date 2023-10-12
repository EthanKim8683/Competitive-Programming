#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
vector<I>adjs1[N],adjs2[N];
I tbgs[N],teds[N];
I segs[2*N],fens[N+1];
I rems[N];
I tim,res;
I n;
void upd1(I l,I r,I val){
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)segs[l++]+=val;
    if(r&1)segs[--r]+=val;
  }
}
I qry1(I i){
  I res=0;
  for(i+=n;i>0;i>>=1)res+=segs[i];
  return res;
}
void upd2(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry2(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
void dfs1(I a){
  tbgs[a]=tim++;
  for(auto b:adjs2[a])dfs1(b);
  teds[a]=tim;
}
void dfs2(I a,I cnt=0){
  if(qry2(teds[a])-qry2(tbgs[a])){
    rems[a]=a;
  }else{
    I b=rems[a]=qry1(tbgs[a])-1;
    if(b!=-1){
      upd1(tbgs[b],teds[b],-(b+1));
      upd2(tbgs[b]+1,-1);
      cnt--;
    }
    upd1(tbgs[a],teds[a],a+1);
    upd2(tbgs[a]+1,1);
    cnt++;
  }
  res=max(res,cnt);
  for(auto b:adjs1[a])dfs2(b,cnt);
  I b=rems[a];
  if(b!=a){
    if(b!=-1){
      upd1(tbgs[b],teds[b],b+1);
      upd2(tbgs[b]+1,1);
      cnt++;
    }
    upd1(tbgs[a],teds[a],-(a+1));
    upd2(tbgs[a]+1,-1);
    cnt--;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)adjs1[i].clear(),adjs2[i].clear();
    for(I i=1;i<n;i++){
      I a;cin>>a,a--;
      adjs1[a].push_back(i);
    }
    for(I i=1;i<n;i++){
      I b;cin>>b,b--;
      adjs2[b].push_back(i);
    }
    tim=0,dfs1(0);
    res=0,dfs2(0);
    printf("%i\n",res);
  }
}
/*
if a vertex is an ancestor in Keshi's tree of at least one of its ancestors
or descendants in Soroush's tree, it can be excluded from the maximum clique

looking at this as a cost problem, the cost of replacing the ancestors and/or
descendants is at least 1, while the cost of replacing the vertex is exactly 1
*/