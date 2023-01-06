#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2000;
I h_arr[N];
map<I,pair<Lli,Lli>>stks[N];
I n;
B cmp(pair<Lli,Lli>a,pair<Lli,Lli>b){
  return a.first*b.second>b.first*a.second;
}
void bld(I i){
  I a=h_arr[i];
  stks[i].clear();
  for(I j=0;j<i;j++){
    I b=h_arr[j];
    pair<Lli,Lli>lin={a-b,i-j};
    while(stks[i].size()){
      auto it=prev(stks[i].end());
      if(!cmp(it->second,lin))break;
      stks[i].erase(it);
    }
    stks[i][j]=lin;
  }
}
void upd(I i,I v){
  I a=(h_arr[i]+=v);
  stks[i].clear();
  for(I j=0;j<i;j++){
    I b=h_arr[j];
    pair<Lli,Lli>lin={a-b,i-j};
    while(stks[i].size()){
      auto it=prev(stks[i].end());
      if(!cmp(it->second,lin))break;
      stks[i].erase(it);
    }
    stks[i][j]=lin;
  }
  for(I j=i+1;j<n;j++){
    I b=h_arr[j];
    pair<Lli,Lli>lin={b-a,j-i};
    auto it=stks[j].upper_bound(i);
    if(it!=stks[j].end()&&cmp(lin,it->second))continue;
    stks[j].erase(i);
    while(stks[j].size()){
      auto it=stks[j].upper_bound(i);
      if(it--==stks[j].begin())break;
      if(!cmp(it->second,lin))break;
      stks[j].erase(it);
    }
    stks[j][i]=lin;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  for(I i=0;i<n;i++)bld(i);
  I q;cin>>q;
  while(q--){
    I x,y;cin>>x>>y;
    upd(x-1,y);
    Lli res=0;
    for(I i=0;i<n;i++)res+=stks[i].size();
    printf("%lli\n",res);
  }
}