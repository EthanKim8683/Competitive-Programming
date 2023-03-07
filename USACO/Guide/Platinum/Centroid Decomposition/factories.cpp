#ifndef ETHANKIM8683
#include"factories.h"
#endif
#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=500000;
const Lli MAX=1e18;
vector<pair<I,I>>adjs[N];
I sizs[N];
B viss[N];
vector<pair<I,Lli>>rels[N];
Lli vals[N];
I tim=0;
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto[b,d]:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto[b,d]:adjs[a])if(b!=p&&!viss[b]&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
void dfs4(I a,I r,I p=-1,Lli l=0){
  rels[a].push_back({r,l});
  for(auto[b,d]:adjs[a])if(b!=p&&!viss[b])dfs4(b,r,a,l+d);
}
void dfs3(I a,I p=-1){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  dfs4(a,a);
  for(auto[b,d]:adjs[a])if(!viss[b])dfs3(b,a);
}
void Init(I n,I a_arr[],I b_arr[],I d_arr[]){
  for(I i=0;i<n-1;i++){
    I a=a_arr[i],b=b_arr[i],d=d_arr[i];
    adjs[a].push_back({b,d});
    adjs[b].push_back({a,d});
  }
  dfs3(0);
  fill_n(vals,n,MAX);
}
Lli Query(I s,I x_arr[],I t,I y_arr[]){
  for(I i=0;i<s;i++)for(auto[j,val]:rels[x_arr[i]])vals[j]=min(vals[j],val);
  Lli res=MAX;
  for(I i=0;i<t;i++)for(auto[j,val]:rels[y_arr[i]])res=min(res,val+vals[j]);
  for(I i=0;i<s;i++)for(auto[j,val]:rels[x_arr[i]])vals[j]=MAX;
  return res;
}
#ifdef ETHANKIM8683
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  I a_arr[n-1],b_arr[n-1],d_arr[n-1];
  for(I i=0;i<n-1;i++)cin>>a_arr[i]>>b_arr[i]>>d_arr[i];
  Init(n,a_arr,b_arr,d_arr);
  while(q--){
    I s,t;cin>>s>>t;
    I x_arr[s],y_arr[t];
    for(I i=0;i<s;i++)cin>>x_arr[i];
    for(I i=0;i<t;i++)cin>>y_arr[i];
    printf("%lli\n",Query(s,x_arr,t,y_arr));
  }
}
#endif