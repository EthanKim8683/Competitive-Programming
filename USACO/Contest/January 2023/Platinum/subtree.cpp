#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
I p_arr[N];
vector<I>adjs[N];
I sizs[N];
I deps[N];
B viss[N];
I dp[N][2];
vector<pair<I,I>>tmps[N];
I n;
I dfs1(I a,I p){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p){
  for(auto b:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
I dfs3(I a,I p){
  deps[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])deps[a]=max(deps[a],dfs3(b,a)+1);
  return deps[a];
}
Lli dfs5(I,I);
Lli dfs4(I a,I p){
  viss[a]=1;
  pair<I,I>tar={0,-1};
  for(auto b:adjs[a])if(b!=p&&!viss[b])tar=max(tar,{deps[b],b});
  auto[dep,c]=tar;
  Lli res=0;
  if(c!=-1){
    res+=dfs4(c,a)+sizs[a]-sizs[c];
    for(auto b:adjs[a])if(b!=p&&b!=c&&!viss[b])res+=dfs5(b,a);
  }
  if(c==-1){
    res=1;
  }
  return res;
}
Lli dfs5(I a,I p){
  a=dfs2(a,dfs1(a,p),p);
  viss[a]=1;
  dfs3(a,p);
  for(auto b:adjs[a])if(b!=p&&!viss[b])tmps[a].push_back({-deps[b],b});
  sort(tmps[a].begin(),tmps[a].end());
  Lli res=0;
  if(tmps[a].size()>=2){
    auto[dep1,x]=tmps[a][0];auto[dep2,y]=tmps[a][1];
    res+=dfs4(x,a)+sizs[a]-sizs[x],res+=dfs4(y,a)+sizs[a]-sizs[y];
    for(auto b:adjs[a])if(b!=p&&b!=x&&b!=y&&!viss[b])res+=dfs5(b,a);
  }
  if(tmps[a].size()<2){
    res=deps[a]*2;
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=1;i<n;i++){I p;cin>>p,p_arr[i]=p-1;}
  for(I i=1;i<n;i++){
    I j=p_arr[i];
    adjs[j].push_back(i);
    adjs[i].push_back(j);
  }
  printf("%lli\n",dfs5(0,-1));
  /*
  centroid decomposition?
  */
}