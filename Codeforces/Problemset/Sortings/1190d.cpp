#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
const I MIN=-1e9;
pair<I,I>pnts[N];
vector<I>cpss[2];
vector<I>flts[N];
B viss[N+1];
I fens[N+1];
void upd(I i){
  if(viss[i])return;
  viss[i]=1;
  for(i++;i<=cpss[0].size();i+=i&-i)fens[i]++;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
    cpss[0].push_back(x);
    cpss[1].push_back(y);
  }
  sort(cpss[0].begin(),cpss[0].end());
  sort(cpss[1].begin(),cpss[1].end());
  cpss[0].erase(unique(cpss[0].begin(),cpss[0].end()),cpss[0].end());
  cpss[1].erase(unique(cpss[1].begin(),cpss[1].end()),cpss[1].end());
  for(I i=0;i<n;i++){
    auto[x,y]=pnts[i];
    x=lower_bound(cpss[0].begin(),cpss[0].end(),x)-cpss[0].begin();
    y=lower_bound(cpss[1].begin(),cpss[1].end(),y)-cpss[1].begin();
    flts[y].push_back(x);
  }
  Lli res=0;
  for(I i=cpss[1].size()-1;i>=0;i--){
    sort(flts[i].begin(),flts[i].end());
    I pre=MIN;
    for(auto j:flts[i])upd(j);
    for(auto j:flts[i]){
      Lli low=qry(j)-qry(pre+1),upp=qry(cpss[0].size())-qry(j+1);
      res+=(low+1)*(upp+1),pre=j;
    }
  }
  printf("%lli\n",res);
}