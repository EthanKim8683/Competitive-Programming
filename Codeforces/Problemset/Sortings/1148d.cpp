#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
pair<I,I>vals[N];
vector<I>incs,decs,ress;
B cmp1(I a,I b){
  return vals[a].second>vals[b].second;
}
B cmp2(I a,I b){
  return vals[a].first<vals[b].first;
}
B equ1(I a,I b){
  return vals[a].second==vals[b].second;
}
B equ2(I a,I b){
  return vals[a].first==vals[b].first;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    vals[i]={a,b};
    if(b>a)decs.push_back(i);
    if(a>b)incs.push_back(i);
  }
  sort(decs.begin(),decs.end(),cmp1);
  sort(incs.begin(),incs.end(),cmp2);
  decs.erase(unique(decs.begin(),decs.end(),equ1),decs.end());
  incs.erase(unique(incs.begin(),incs.end(),equ2),incs.end());
  ress=decs.size()>incs.size()?decs:incs;
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i+1);
}