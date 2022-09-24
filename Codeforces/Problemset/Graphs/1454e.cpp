#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=2e5;

vector<I>adjs[N];
vector<I>stks;
vector<I>cycs;
B viss[N];
B ntrs[N];
I dp1[N];
Lli dp2[N];

B dfs1(I a,I p=-1){
  if(viss[a]){
    cycs.push_back(a),ntrs[a]=1;
    while(stks.size()&&stks.back()!=a){
      I b=stks.back();stks.pop_back();
      cycs.push_back(b),ntrs[b]=1;
    }
    return 1;
  }
  viss[a]=1;
  stks.push_back(a);
  for(auto b:adjs[a])if(b!=p)
    if(dfs1(b,a))return 1;
  stks.pop_back();
  return 0;
}

void dfs2(I a,I p){
  for(auto b:adjs[a])if(b!=p){
    dfs2(b,a);
    dp2[a]+=dp2[b]+(Lli)dp1[b]*dp1[a];
    dp1[a]+=dp1[b];
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    stks.clear(),cycs.clear();
    fill_n(viss,n,0),fill_n(ntrs,n,0);
    fill_n(dp1,n,1),fill_n(dp2,n,0);
    for(I i=0;i<n;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    dfs1(0);
    Lli res=0;
    I tot=n;
    for(auto i:cycs){
      for(auto j:adjs[i])if(!ntrs[j]){
        dfs2(j,i);
        dp2[i]+=dp2[j]+(Lli)dp1[j]*dp1[i];
        dp1[i]+=dp1[j];
      }
      tot-=dp1[i];
      res+=dp2[i];
      res+=(Lli)dp1[i]*tot*2;
    }
    printf("%lli\n",res);
  }
  return 0;
}