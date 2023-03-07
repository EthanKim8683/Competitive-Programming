#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I MAX=1e9;
vector<I>adjs1[N],adjs2[2*N],adjs3[2*N];
I dp1[N][2];
vector<pair<I,I>>rems,adds;
void dfs1(I a,I p=-1){
  I tot=0;
  for(auto b:adjs1[a])if(b!=p)dfs1(b,a),tot+=min(dp1[b][0],dp1[b][1])+1;
  static tuple<I,I,I>dp2[3];
  fill_n(dp2,3,tuple<I,I,I>{tot,-1,-1});
  for(auto b:adjs1[a])if(b!=p){
    I cur=dp1[b][0]-min(dp1[b][0],dp1[b][1])-1;
    dp2[2]=min(dp2[2],{get<0>(dp2[1])+cur,b,get<1>(dp2[1])});
    dp2[1]=min(dp2[1],{get<0>(dp2[0])+cur,b,get<1>(dp2[0])});
  }
  auto[tot1,x,y]=dp2[1];auto[tot2,z,w]=dp2[2];
  dp1[a][0]=tot1,dp1[a][1]=tot2;
  if(x!=-1)adjs2[2*a].push_back(2*x);
  if(y!=-1)adjs2[2*a].push_back(2*y);
  if(z!=-1)adjs2[2*a+1].push_back(2*z);
  if(w!=-1)adjs2[2*a+1].push_back(2*w);
  for(auto b:adjs1[a])if(b!=p){
    I c=min(pair<I,I>{dp1[b][0],2*b},{dp1[b][1],2*b+1}).second;
    if(b!=x&&b!=y)adjs3[2*a].push_back(c);
    if(b!=z&&b!=w)adjs3[2*a+1].push_back(c);
  }
}
void dfs2(I a){
  for(auto b:adjs2[a])dfs2(b);
  for(auto b:adjs3[a])dfs2(b),rems.push_back({a,b});
}
I dfs3(I a){
  for(auto b:adjs2[a])return dfs3(b);
  return a;
}
pair<I,I>fnd(I a){
  static I ress[2];
  fill_n(ress,2,a);
  for(I i=0;i<adjs2[a].size();i++)ress[i]=dfs3(adjs2[a][i]);
  return{ress[0],ress[1]};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)adjs1[i].clear();
    for(I i=0;i<2*n;i++)adjs2[i].clear(),adjs3[i].clear();
    for(I i=0;i<n-1;i++){
      I a,b;cin>>a>>b,a--,b--;
      adjs1[a].push_back(b);
      adjs1[b].push_back(a);
    }
    dfs1(0);
    auto[res,r]=min(pair<I,I>{dp1[0][0],0},{dp1[0][1],1});
    rems.clear(),adds.clear(),dfs2(r);
    I a=fnd(r).first;
    for(auto[p,b]:rems){
      auto[c,d]=fnd(b);
      adds.push_back({a,c}),a=d;
    }
    printf("%i\n",res);
    for(I i=0;i<rems.size();i++){
      auto[x,y]=rems[i];auto[z,w]=adds[i];
      printf("%i %i %i %i\n",x/2+1,y/2+1,z/2+1,w/2+1);
    }
  }
}