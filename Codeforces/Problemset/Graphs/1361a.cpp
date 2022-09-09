#include<iostream>
#include<cstdio>
#include<vector>
#include<numeric>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=5e5;

I t_arr[N];
vector<I>adjs[N];
I inds[N];
I invs[N];
vector<I>viss;

B cmp(I a,I b){
  return t_arr[a]<t_arr[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)adjs[i].clear();
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<n;i++)cin>>t_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++)invs[inds[i]]=i;
  B res=1;
  for(I i=0;i<n;i++){
    I a=inds[i];
    viss.clear();
    for(auto b:adjs[a])
      if(invs[b]<i)viss.push_back(t_arr[b]);
    sort(viss.begin(),viss.end());
    I t=1;
    for(auto j:viss)t+=j==t;
    res&=t==t_arr[a];
  }
  if(!res)printf("-1\n");
  else for(I i=0;i<n;i++)printf("%i ",inds[i]+1);
  return 0;
}